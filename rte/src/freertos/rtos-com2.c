/* @page rtos-com2.c
 *       PLC411::RTE
 *       RTOS-task T_COM2
 *       2020-2022, atgroup09@gmail.com
 */

#include "rtos-com2.h"


#ifdef RTE_MOD_COM2

/** @var COM2 Settings
 */
static MBRTU_t MBRTU_COM2;


/** @brief  Start transfer.
 *  @param  DirIn - transfer direction:
 *  @arg    = MBRTU_RX
 *  @arg    = MBRTU_TX
 *  @return None.
 */
static void PlcCom2_StartTransfer(uint8_t DirIn)
{
	if(DirIn == MBRTU_RX)
	{
		MBRTU_COM2.RxTx       = MBRTU_RX;
		MBRTU_COM2.RxExc      = MBRTU_EXC_OK;
		MBRTU_COM2.RxBuffOver = BIT_FALSE;
		MBRTU_COM2.RxCnt      = 0;
		//unknown response size, then used maximum buffer size
		//real response size will be return from IDLE-callback
        PlcUart_StartReceive(&PLC_UART2, MBRTU_COM2.RxBuff, MBRTU_BUFF_SZ);
	}
    else if(DirIn == MBRTU_TX)
    {
    	MBRTU_COM2.RxTx = MBRTU_TX;
        PlcUart_StartTransmit(&PLC_UART2, MBRTU_COM2.TxBuff, MBRTU_COM2.TxCnt);
	}
}

/** @brief  Set Response.
 *  @param  None.
 *  @return None.
 */
static void PlcCom2_Response(void)
{
	if(MBRTU_COM2.RxExc < MBRTU_EXC_SLAVE_ERR && MBRTU_COM2.TxCnt)
	{
		//send
		MBRTU_COM2.cRes++;
		PlcCom2_StartTransfer(MBRTU_TX);
	}
	else
	{
		//not send (waiting for new request)
		MBRTU_COM2.cNoRes++;
		PlcCom2_StartTransfer(MBRTU_RX);
	}
}


/** @brief  Transfer completed.
 *  @param  RxCntIn - the number of received data.
 *  @return None.
 */
static void PlcCom2_TransferCplt(void)
{
	portBASE_TYPE TaskWoken = pdTRUE;
	uint8_t QueueData = ((MBRTU_COM2.RxTx == MBRTU_RX) ? RTOS_COM2_Q_RX_CPLT : RTOS_COM2_Q_TX_CPLT);
	xQueueSendToBackFromISR(RTOS_COM2_Q, &QueueData, &TaskWoken);
}

/** @brief  Callback for COM2.IRQ.Tx.Completed.
 *  @param  None.
 *  @return None.
 */
static void PlcCom2_TxCplt(void)
{
#ifdef DEBUG_LOG_COM2
    DebugLog("PlcCom2_TxCplt\n");
#endif // DEBUG_LOG_COM2

	PlcCom2_TransferCplt();
}

/** @brief  Callback for IRQ COM2.IRQ.Rx.Completed.
 *  @param  None.
 *  @return None.
 */
static void PlcCom2_RxCplt(void)
{
#ifdef DEBUG_LOG_COM2
    DebugLog("PlcCom2_RxCplt\n");
#endif // DEBUG_LOG_COM2

	MBRTU_COM2.RxExc = MBRTU_EXC_OK;
	MBRTU_COM2.RxCnt = MBRTU_BUFF_SZ;
	PlcCom2_TransferCplt();
}

/** @brief  Callback for COM2.IRQ.Idle.
 *  @param  RxCntIn - quantity of Rx-data.
 *  @return None.
 */
static void PlcCom2_Idle(uint32_t RxCntIn)
{
#ifdef DEBUG_LOG_COM2
    DebugLog("PlcCom2_Idle\n");
#endif // DEBUG_LOG_COM2

	MBRTU_COM2.RxExc = MBRTU_EXC_OK;
	MBRTU_COM2.RxCnt = (MBRTU_BUFF_SZ-((uint8_t)RxCntIn));
	PlcCom2_TransferCplt();
}


/** @brief  Init COM2_T
 *  @param  None.
 *  @return None.
 */
static void RTOS_COM2_Init(void)
{
#ifdef DEBUG_LOG_MAIN
    DebugLog("RTOS_COM2_Init\n");
#endif // DEBUG_LOG_MAIN

	MBRTU_InitDef(&MBRTU_COM2, PLC_COM2_SLAVE_ADDR);

	PLC_UART2_USER_FUNC.TxCplt = PlcCom2_TxCplt;
	PLC_UART2_USER_FUNC.RxCplt = PlcCom2_RxCplt;
	PLC_UART2_USER_FUNC.Idle   = PlcCom2_Idle;

	PlcUart2_Init();
	PlcCom2_StartTransfer(MBRTU_RX);
}

/** @brief  DeInit COM2_T
 *  @param  None.
 *  @return None.
 */
static void RTOS_COM2_DeInit(void)
{
#ifdef DEBUG_LOG_MAIN
    DebugLog("RTOS_COM2_DeInit\n");
#endif // DEBUG_LOG_MAIN

	PlcUart2_DeInit();
}


/** @brief  COM2_T (blocked)
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return None.
 */
void RTOS_COM2_Task(void *ParamsIn)
{
	//variables
	uint8_t    COM2_Q_Data;
	BaseType_t COM2_Q_Status;

	(void)ParamsIn; //fix unused

	RTOS_COM2_Init();

	//start
	for(;;)
    {
		//Read Queue (blocking)
		//get command ID
		COM2_Q_Status = xQueueReceive(RTOS_COM2_Q, &COM2_Q_Data, portMAX_DELAY);
		if(COM2_Q_Status == pdPASS)
		{
			switch(COM2_Q_Data)
			{
				case RTOS_COM2_Q_RX_CPLT:
					//parse request
					MBRTU_COM2.RxExc = MBRTU_ParseReq(&MBRTU_COM2);

					//create answer
					if(MBRTU_COM2.RxExc == MBRTU_EXC_OK)
	                {
						//waiting until the access to the memory of ModBus-tables is released
	                    if(xSemaphoreTake(RTOS_MBTABLES_MTX, RTOS_COM2_DELAY_BUSY) == pdPASS)
	                    {
	                        //ModBus-tables LOCK
	                    	//create answer
	                    	MBRTU_COM2.RxExc = MBRTU_CreateRes(&MBRTU_COM2);
	                    	xSemaphoreGive(RTOS_MBTABLES_MTX);
	                    	//ModBus-tables UNLOCK
	                    }
	                    else
	                    {
	                        //exception: Device is busy
	                        MBRTU_COM2.RxExc = MBRTU_EXC_PROCESS;
	                    }
	                }

					//create exc-answer
	                if(MBRTU_COM2.RxExc != MBRTU_EXC_OK)
	                {
	                    if(MBRTU_COM2.RxExc < MBRTU_EXC_SLAVE_ERR)
	                    {
	                        MBRTU_CreateResExc(&MBRTU_COM2, MBRTU_COM2.RxExc);
	                    }
	                }

	                //update diagnostic counters
                    if(MBRTU_COM2.RxExc)
                    {
                    	//cBusExcErr
                    	if(MBRTU_COM2.cBusExcErr < MBRTU_DIAG_COUNTER_MAX) MBRTU_COM2.cBusExcErr++;
                    	//cBusComErr
                    	if(MBRTU_COM2.RxExc == MBRTU_EXC_CRC_ERR && MBRTU_COM2.cBusComErr < MBRTU_DIAG_COUNTER_MAX) MBRTU_COM2.cBusComErr++;
                    	//cNoRes
                    	if(MBRTU_COM2.RxExc >= MBRTU_EXC_SLAVE_ERR && MBRTU_COM2.cNoRes < MBRTU_DIAG_COUNTER_MAX) MBRTU_COM2.cNoRes++;
                    }

                    //send response
                    RTOS_LED_Q_SendMode(PLC_LED_NET, PLC_LED_MODE_ON);
                    PlcCom2_Response();
					break;

				case RTOS_COM2_Q_TX_CPLT:
					PlcCom2_StartTransfer(MBRTU_RX);
					RTOS_LED_Q_SendMode(PLC_LED_NET, PLC_LED_MODE_OFF);
					break;
			}
		}

        //fast switch to other task
        taskYIELD();
    }

	RTOS_COM2_DeInit();
}

#endif // RTE_MOD_COM2
