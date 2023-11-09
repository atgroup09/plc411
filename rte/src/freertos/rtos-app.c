/* @page rtos-app.c
 *       PLC411::RTE
 *       RTOS-task APP_T
 *       2023, atgroup09@gmail.com
 */

#include "rtos-app.h"


/** @var Timer statuses
 */
static uint8_t PLC_APP_TIM_STATUS = BIT_FALSE;


/** @brief  Set APP_TIM Period.
 *  @param  None.
 *  @return None.
 */
static void RTOS_APP_TIM_Set(void)
{
	if(!PLC_APP_TIM_STATUS)
	{
	    if(PLC_APP_CURR)
	    {
	        if(PLC_APP_CURR->common_ticktime)
	        {
	            uint32_t TimerPeriod = (uint32_t)(*PLC_APP_CURR->common_ticktime/RTOS_TICK_NS);
	            if(!TimerPeriod) TimerPeriod = RTOS_APP_TIM_TM;

	            xTimerChangePeriod(RTOS_APP_TIM, (TickType_t)TimerPeriod, (TickType_t)0);

#ifdef DEBUG_LOG_MAIN
	            DebugLog("APP_TIM [SET] (%d ms)\n", TimerPeriod);
#endif //DEBUG_LOG_MAIN
	            return;
	        }
	    }
    }
#ifdef DEBUG_LOG_MAIN
	            DebugLog("APP_TIM [NOT SET]\n");
#endif //DEBUG_LOG_MAIN
}

/** @brief  Start APP_TIM.
 *  @param  None.
 *  @return None.
 */
static void RTOS_APP_TIM_Start(void)
{
	if(!PLC_APP_TIM_STATUS)
	{
		xTimerReset(RTOS_APP_TIM, 0);
		PLC_APP_TIM_STATUS = BIT_TRUE;

#ifdef DEBUG_LOG_APP_TIM
		DebugLog("APP_TIM [STARTED]\n\n");
#endif //DEBUG_LOG_APP_TIM
	}
}

/** @brief  Stop APP_TIM.
 *  @param  None.
 *  @return None.
 */
static void RTOS_APP_TIM_Stop(void)
{
	if(PLC_APP_TIM_STATUS)
	{
		xTimerStop(RTOS_APP_TIM, 0);
		PLC_APP_TIM_STATUS = BIT_FALSE;

#ifdef DEBUG_LOG_APP_TIM
		DebugLog("APP_TIM [STOPPED]\n\n");
#endif //DEBUG_LOG_APP_TIM
    }
}


/** @brief  Task APP_T (non-blocking)
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return none.
 */
void RTOS_APP_Task(void *ParamsIn)
{
    //VARIABLES
    BaseType_t APP_SEMA_Status;
    uint8_t    AppRun1 = BIT_FALSE;

#ifdef RTE_MOD_DO
    PlcDO_Q_t  DO_Q_Data;
#endif //RTE_MOD_DO

    //INIT
    (void)ParamsIn;

#ifdef RTE_MOD_APP_TIM
    RTOS_APP_TIM_Set();
#endif // RTE_MOD_APP_TIM

    xSemaphoreGive(RTOS_APP_SEMA);
    PlcApp_Start();

    if(PLC_APP_STATE == PLC_APP_STATE_STARTED)
    {
    	xSemaphoreTake(RTOS_MBTABLES_MTX, portMAX_DELAY);
        REG_SYS_STAT1_Set(PLC_SYS_STAT1_APP_INITED, BIT_TRUE);
        xSemaphoreGive(RTOS_MBTABLES_MTX);
#ifdef DEBUG_LOG_MAIN
        DebugLog("APP [STARTED] (%d)\n\n", PLC_APP_STATE);
#endif //DEBUG_LOG_MAIN
    }
    else
    {
    	xSemaphoreTake(RTOS_MBTABLES_MTX, portMAX_DELAY);
    	REG_SYS_STAT1_Set(PLC_SYS_STAT1_APP_INITED, BIT_FALSE);
    	xSemaphoreGive(RTOS_MBTABLES_MTX);
#ifdef DEBUG_LOG_MAIN
        DebugLog("APP [NOT STARTED] (%d)\n\n", PLC_APP_STATE);
#endif //DEBUG_LOG_MAIN
    }

    //START
    for(;;)
    {
#ifdef RTE_MOD_APP_DEBUG_HANDLER
        dbg_handler();
#endif //RTE_MOD_APP_DEBUG_HANDLER

        if(PLC_APP_STATE == PLC_APP_STATE_STARTED)
        {
            //Waiting for Application cycle (non-blocked)
        	APP_SEMA_Status = xSemaphoreTake(RTOS_APP_SEMA, (TickType_t)0);
            if(APP_SEMA_Status == pdPASS)
            {
                //Sync Relation Data (MODBUS.Data > APP.Data)
                xSemaphoreTake(RTOS_MBTABLES_MTX, portMAX_DELAY);
                REG_CopyMbToApp();
               	REG_SYS_STAT1_Set(PLC_SYS_STAT1_APP_RUN, BIT_TRUE);
               	RTOS_LED_Q_SendMode(PLC_LED_RUN, PLC_LED_MODE_ON);
                xSemaphoreGive(RTOS_MBTABLES_MTX);

                //APP.Run
                PlcApp_Run();

#ifdef DEBUG_LOG_APP_VAR
                PlcApp_DebugPrint();
#endif //DEBUG_LOG_APP_VAR

                //Sync Relation Data (APP.Data > MODBUS.Data)
                //LOCK
                xSemaphoreTake(RTOS_MBTABLES_MTX, portMAX_DELAY);
                REG_CopyAppToMb();
                REG_SYS_STAT1_Set(PLC_SYS_STAT1_APP_RUN, BIT_FALSE);
                RTOS_LED_Q_SendMode(PLC_LED_RUN, PLC_LED_MODE_OFF);
                if(!AppRun1)
                {
                	AppRun1 = BIT_TRUE;
                	REG_SYS_STAT1_Set(PLC_SYS_STAT1_APP_RUN1, AppRun1);
                }
                xSemaphoreGive(RTOS_MBTABLES_MTX);
                //UNLOCK

#ifdef RTE_MOD_DO
                //Update DO (apply postponed normal)
                if(PLC_DO_POSTPONED)
                {
                	DO_Q_Data.ID  = PLC_DO_Q_ID_POSTPONED_APPLY;
                	DO_Q_Data.Val = (float)BIT_TRUE;
                    xQueueSendToBack(RTOS_DO_Q, &DO_Q_Data, 0);
                    PLC_DO_POSTPONED = BIT_FALSE;
                }
#endif //RTE_MOD_DO

                //APP_TIM.Reset
                RTOS_APP_TIM_Start();

#ifdef DEBUG_LOG_APP_RUN
                DebugLog("APP [RUN]\n");
#endif //DEBUG_LOG_APP_RUN
            }
        }

        //fast switch to other task
        taskYIELD();
    }
}


/** @brief  APP_TIM Handler (one-shot)
 *  @param  TimerIn - timer.
 *  @return none.
 */
void RTOS_APP_TIM_Handler(TimerHandle_t TimerIn)
{
    (void)TimerIn; //fix unused

    RTOS_APP_TIM_Stop();
    xSemaphoreGive(RTOS_APP_SEMA);
}
