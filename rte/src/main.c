/* @page main.c
 *       PLC411::RTE
 *       Entry point
 *       2022-2023, atgroup09@gmail.com
 */

#include "config.h"
#include "rtos.h"

#ifdef DEBUG
#include "debug-log.h"
#endif //DEBUG

#ifdef RTE_MOD_REG
#include "reg-init.h"
#endif //RTE_MOD_REG

#ifdef RTE_MOD_DI
#include "rtos-di.h"
#endif //RTE_MOD_DI

#ifdef RTE_MOD_DO
#include "rtos-do.h"
#endif //RTE_MOD_DO

#ifdef RTE_MOD_AI
#include "rtos-ai.h"
#endif //RTE_MOD_AI

#ifdef RTE_MOD_LED
#include "rtos-led.h"
#endif //RTE_MOD_LED

#ifdef RTE_MOD_DATA
#include "rtos-data.h"
#endif //RTE_MOD_DATA

#ifdef RTE_MOD_COM1
#include "rtos-com1.h"
#endif //RTE_MOD_COM1

#ifdef RTE_MOD_COM2
#include "rtos-com2.h"
#endif //RTE_MOD_COM2

#ifdef RTE_MOD_APP
#include "rtos-app.h"
#endif //RTE_MOD_APP


/** @brief  Main function.
 *  @param  None.
 *  @return None.
 */
int main(void)
{
	/** INIT
	 */

#ifdef DEBUG
	DebugLog_Init();
#endif //DEBUG


#ifdef DEBUG_LOG_MAIN
    DebugLog("===================\n");
    DebugLog("PLC%d.%d RTE.%d\n", PLC_HW_CODE, PLC_HW_VAR, PLC_RTE_VERSION);
#endif //DEBUG_LOG_MAIN


#ifdef RTE_MOD_APP
    PlcApp_Init();
    PlcApp_InitSysFunc();

    RTOS_APP_SEMA = xSemaphoreCreateBinary();
    if(!RTOS_APP_SEMA) _Error_Handler(__FILE__, __LINE__);

    RTOS_APP_TIM = xTimerCreate(RTOS_APP_TIM_NAME, RTOS_APP_TIM_TM, pdFALSE, 0, RTOS_APP_TIM_Handler);
    if(!RTOS_APP_TIM) _Error_Handler(__FILE__, __LINE__);

    if(xTaskCreate(RTOS_APP_Task, RTOS_APP_T_NAME, RTOS_APP_T_STACK_SZ, NULL, RTOS_APP_T_PRIORITY, NULL) != pdTRUE)
    {
    	_Error_Handler(__FILE__, __LINE__);
    }
#ifdef DEBUG_LOG_MAIN
    DebugLog("MOD_APP [OK]\n");
#endif //DEBUG_LOG_MAIN
#endif //RTE_MOD_APP


//!!! PlcApp_Init() must be run before it !!!
#ifdef RTE_MOD_REG
    REG_Init();
    REG_SetDef();
#ifdef DEBUG_LOG_MAIN
    DebugLog("REG [INITED]\n");
#endif //DEBUG_LOG_MAIN
#endif //RTE_MOD_REG


    RTOS_MBTABLES_MTX = xSemaphoreCreateMutex();
    if(!RTOS_MBTABLES_MTX) _Error_Handler(__FILE__, __LINE__);
#ifdef DEBUG_LOG_MAIN
    DebugLog("MBTABLES_MTX [OK]\n");
#endif //DEBUG_LOG_MAIN


#ifdef RTE_MOD_REG_MON
    RTOS_DATA_REG_MONITOR_Q = xQueueCreate(RTOS_DATA_REG_MONITOR_Q_SZ, RTOS_DATA_REG_MONITOR_Q_ISZ);
    if(!RTOS_DATA_REG_MONITOR_Q) _Error_Handler(__FILE__, __LINE__);
#ifdef DEBUG_LOG_MAIN
    DebugLog("DATA_REG_MONITOR_Q [OK]\n");
#endif //DEBUG_LOG_MAIN
#endif //RTE_MOD_REG_MON


#ifdef RTE_MOD_DI
    RTOS_DI_IRQ_Q = xQueueCreate(RTOS_DI_IRQ_Q_SZ, RTOS_DI_IRQ_Q_ISZ);
    if(!RTOS_DI_IRQ_Q) _Error_Handler(__FILE__, __LINE__);

    RTOS_DI_Q = xQueueCreate(RTOS_DI_Q_SZ, RTOS_DI_Q_ISZ);
    if(!RTOS_DI_Q) _Error_Handler(__FILE__, __LINE__);

    RTOS_DI_DATA_Q = xQueueCreate(RTOS_DI_DATA_Q_SZ, RTOS_DI_DATA_Q_ISZ);
    if(!RTOS_DI_DATA_Q) _Error_Handler(__FILE__, __LINE__);

    RTOS_DI_TACH_TIM = xTimerCreate(RTOS_DI_TACH_TIM_NAME, RTOS_DI_TACH_TIM_TM, pdFALSE, 0, RTOS_DI_TACH_TIM_Handler);
    if(!RTOS_DI_TACH_TIM) _Error_Handler(__FILE__, __LINE__);

    RTOS_DI_FLTR_TIM = xTimerCreate(RTOS_DI_FLTR_TIM_NAME, RTOS_DI_FLTR_TIM_TM, pdFALSE, 0, RTOS_DI_FLTR_TIM_Handler);
    if(!RTOS_DI_FLTR_TIM) _Error_Handler(__FILE__, __LINE__);

    if(xTaskCreate(RTOS_DI_IRQ_Task, RTOS_DI_IRQ_T_NAME, RTOS_DI_IRQ_T_STACK_SZ, NULL, RTOS_DI_IRQ_T_PRIORITY, NULL) != pdTRUE)
    {
    	_Error_Handler(__FILE__, __LINE__);
	}

    if(xTaskCreate(RTOS_DI_Task, RTOS_DI_T_NAME, RTOS_DI_T_STACK_SZ, NULL, RTOS_DI_T_PRIORITY, NULL) != pdTRUE)
	{
    	_Error_Handler(__FILE__, __LINE__);
	}
#ifdef DEBUG_LOG_MAIN
    DebugLog("MOD_DI [OK]\n");
#endif //DEBUG_LOG_MAIN
#endif //RTE_MOD_DI


#ifdef RTE_MOD_DO
    RTOS_DO_Q = xQueueCreate(RTOS_DO_Q_SZ, RTOS_DO_Q_ISZ);
    if(!RTOS_DO_Q) _Error_Handler(__FILE__, __LINE__);

    RTOS_DO_DATA_Q = xQueueCreate(RTOS_DO_DATA_Q_SZ, RTOS_DO_DATA_Q_ISZ);
    if(!RTOS_DO_DATA_Q) _Error_Handler(__FILE__, __LINE__);

    if(xTaskCreate(RTOS_DO_Task, RTOS_DO_T_NAME, RTOS_DO_T_STACK_SZ, NULL, RTOS_DO_T_PRIORITY, NULL) != pdTRUE)
	{
    	_Error_Handler(__FILE__, __LINE__);
	}
#ifdef DEBUG_LOG_MAIN
    DebugLog("MOD_DO [OK]\n");
#endif //DEBUG_LOG_MAIN
#endif //RTE_MOD_DO


#ifdef RTE_MOD_AI
    RTOS_AI_Q = xQueueCreate(RTOS_AI_Q_SZ, RTOS_AI_Q_ISZ);
    if(!RTOS_AI_Q) _Error_Handler(__FILE__, __LINE__);

    RTOS_AI_DATA_Q = xQueueCreate(RTOS_AI_DATA_Q_SZ, RTOS_AI_DATA_Q_ISZ);
    if(!RTOS_AI_DATA_Q) _Error_Handler(__FILE__, __LINE__);

    RTOS_AI_TIM = xTimerCreate(RTOS_AI_TIM_NAME, RTOS_AI_TIM_TM, pdFALSE, 0, RTOS_AI_TIM_Handler);
    if(!RTOS_AI_TIM) _Error_Handler(__FILE__, __LINE__);

    if(xTaskCreate(RTOS_AI_Task, RTOS_AI_T_NAME, RTOS_AI_T_STACK_SZ, NULL, RTOS_AI_T_PRIORITY, NULL) != pdTRUE)
    {
    	_Error_Handler(__FILE__, __LINE__);
    }
#ifdef DEBUG_LOG_MAIN
    DebugLog("MOD_AI [OK]\n");
#endif //DEBUG_LOG_MAIN
#endif //RTE_MOD_AI


#ifdef RTE_MOD_LED
    RTOS_LED_Q = xQueueCreate(RTOS_LED_Q_SZ, RTOS_LED_Q_ISZ);
    if(!RTOS_LED_Q) _Error_Handler(__FILE__, __LINE__);

	if(xTaskCreate(RTOS_LED_Task, RTOS_LED_T_NAME, RTOS_LED_T_STACK_SZ, NULL, RTOS_LED_T_PRIORITY, NULL) != pdTRUE)
	{
		_Error_Handler(__FILE__, __LINE__);
	}
#ifdef DEBUG_LOG_MAIN
    DebugLog("MOD_LED [OK]\n");
#endif //DEBUG_LOG_MAIN
#endif //RTE_MOD_LED


#ifdef RTE_MOD_DATA
    if(xTaskCreate(RTOS_DATA_Task, RTOS_DATA_T_NAME, RTOS_DATA_T_STACK_SZ, NULL, RTOS_DATA_T_PRIORITY, NULL) != pdTRUE)
    {
    	_Error_Handler(__FILE__, __LINE__);
    }
#ifdef DEBUG_LOG_MAIN
    DebugLog("MOD_DATA [OK]\n");
#endif //DEBUG_LOG_MAIN
#endif //RTE_MOD_DATA


#ifdef RTE_MOD_COM1
    RTOS_COM1_Q = xQueueCreate(RTOS_COM1_Q_SZ, RTOS_COM1_Q_ISZ);
    if(!RTOS_COM1_Q) _Error_Handler(__FILE__, __LINE__);

    if(xTaskCreate(RTOS_COM1_Task, RTOS_COM1_T_NAME, RTOS_COM1_T_STACK_SZ, NULL, RTOS_COM1_T_PRIORITY, NULL) != pdTRUE)
    {
    	_Error_Handler(__FILE__, __LINE__);
    }
#ifdef DEBUG_LOG_MAIN
    DebugLog("MOD_COM1 [OK]\n");
#endif //DEBUG_LOG_MAIN
#endif //RTE_MOD_COM1


#ifdef RTE_MOD_COM2
    RTOS_COM2_Q = xQueueCreate(RTOS_COM2_Q_SZ, RTOS_COM2_Q_ISZ);
    if(!RTOS_COM2_Q) _Error_Handler(__FILE__, __LINE__);

    if(xTaskCreate(RTOS_COM2_Task, RTOS_COM2_T_NAME, RTOS_COM2_T_STACK_SZ, NULL, RTOS_COM2_T_PRIORITY, NULL) != pdTRUE)
    {
    	_Error_Handler(__FILE__, __LINE__);
    }
#ifdef DEBUG_LOG_MAIN
    DebugLog("MOD_COM2 [OK]\n");
#endif //DEBUG_LOG_MAIN
#endif //RTE_MOD_COM2


    /** PRESTART
     */


    /** START RTOS SCHEDULER
     */

#ifdef DEBUG_LOG_MAIN
    DebugLog("RTOS [STARTED]\n\n");
#endif // DEBUG_LOG_MAIN

    vTaskStartScheduler();


    /** RTOS Scheduler doesn't start
     */

    _Error_Handler(__FILE__, __LINE__);

    return (0);
}
