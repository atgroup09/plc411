/* @page rtos-com1.c
 *       PLC411::RTE
 *       RTOS-task COM1_T
 *       2023, atgroup09@gmail.com
 */

#include "rtos-com1.h"


#ifdef RTE_MOD_COM1

/** @brief  Callback for COM1.IRQ.Tx.Completed.
 *  @param  None.
 *  @return None.
 */
static void PlcCom1_TxCplt(void)
{
#ifdef DEBUG_LOG_COM1
    DebugLog("PlcCom1_TxCplt\n");
#endif // DEBUG_LOG_COM1

    portBASE_TYPE TaskWoken = pdTRUE;
    uint8_t QueueData = RTOS_COM1_Q_TX_CPLT;
	xQueueSendToBackFromISR(RTOS_COM1_Q, &QueueData, &TaskWoken);
}

/** @brief  Callback for IRQ COM1.IRQ.Rx.Completed.
 *  @param  None.
 *  @return None.
 */
static void PlcCom1_RxCplt(void)
{
#ifdef DEBUG_LOG_COM1
    DebugLog("PlcCom1_RxCplt\n");
#endif // DEBUG_LOG_COM1

    dbg.RxCnt = DBG_SERIAL_BUFF_SIZE;

    portBASE_TYPE TaskWoken = pdTRUE;
    uint8_t QueueData = RTOS_COM1_Q_RX_CPLT;
	xQueueSendToBackFromISR(RTOS_COM1_Q, &QueueData, &TaskWoken);
}

/** @brief  Callback for COM1.IRQ.Idle.
 *  @param  RxCntIn - quantity of Rx-data.
 *  @return None.
 */
static void PlcCom1_Idle(uint32_t RxCntIn)
{
#ifdef DEBUG_LOG_COM1
    DebugLog("PlcCom1_Idle\n");
#endif // DEBUG_LOG_COM1

    dbg.RxCnt = (DBG_SERIAL_BUFF_SIZE-((uint8_t)RxCntIn));

    portBASE_TYPE TaskWoken = pdTRUE;
    uint8_t QueueData = RTOS_COM1_Q_RX_CPLT;
	xQueueSendToBackFromISR(RTOS_COM1_Q, &QueueData, &TaskWoken);
}


/** @brief  Init COM1_T
 *  @param  None.
 *  @return None.
 */
static void RTOS_COM1_Init(void)
{
#ifdef DEBUG_LOG_MAIN
    DebugLog("RTOS_COM1_Init\n");
#endif // DEBUG_LOG_MAIN

	PLC_UART1_USER_FUNC.TxCplt = PlcCom1_TxCplt;
	PLC_UART1_USER_FUNC.RxCplt = PlcCom1_RxCplt;
	PLC_UART1_USER_FUNC.Idle   = PlcCom1_Idle;

	PlcUart1_Init();

    dbg_init();
#ifdef DEBUG_LOG_MAIN
    DebugLog("APP_DEBUG [INITED]\n");
#endif //DEBUG_LOG_MAIN
}

/** @brief  DeInit COM1_T
 *  @param  None.
 *  @return None.
 */
static void RTOS_COM1_DeInit(void)
{
#ifdef DEBUG_LOG_MAIN
    DebugLog("RTOS_COM1_DeInit\n");
#endif // DEBUG_LOG_MAIN

	PlcUart1_DeInit();
}


/** @brief  COM1_T (blocked)
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return None.
 */
void RTOS_COM1_Task(void *ParamsIn)
{
	//variables
	uint8_t    COM1_Q_Data;
	BaseType_t COM1_Q_Status;

	(void)ParamsIn; //fix unused

	RTOS_COM1_Init();

	//start
	for(;;)
    {
		//Read Queue (blocking)
		//get command ID
		COM1_Q_Status = xQueueReceive(RTOS_COM1_Q, &COM1_Q_Data, portMAX_DELAY);
		if(COM1_Q_Status == pdPASS)
		{
			switch(COM1_Q_Data)
			{
				case RTOS_COM1_Q_RX_CPLT:

					dbg.RxState = DBG_SERIAL_FREE;
                    RTOS_LED_Q_SendMode(PLC_LED_NET, PLC_LED_MODE_ON);
					break;

				case RTOS_COM1_Q_TX_CPLT:

					dbg.TxState = DBG_SERIAL_FREE;
					RTOS_LED_Q_SendMode(PLC_LED_NET, PLC_LED_MODE_OFF);
					break;
			}
		}

        //fast switch to other task
        taskYIELD();
    }

	RTOS_COM1_DeInit();
}

#endif //RTE_MOD_COM1
