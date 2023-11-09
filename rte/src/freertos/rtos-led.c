/* @page rtos-led.c
 *       PLC411::RTE
 *       RTOS-task LED_T
 *       2022-2023, atgroup09@gmail.com
 */

#include "rtos-led.h"


/** @var Channels
 */
static PlcLED_t PLC_LED[PLC_LED_SZ];


/** @brief  Send mode into RTOS_LED_Q
 *  @param  ChIn - channel
 *  @param  ModeIn - mode
 *  @return None.
 */
void RTOS_LED_Q_SendMode(uint8_t ChIn, uint8_t ModeIn)
{
#ifdef RTE_MOD_LED
	if(ChIn <= PLC_LED_RUN)
	{
		PlcLED_Q_t LED_Q_Data;

		//pack data
		LED_Q_Data.Ch  = ChIn;
		LED_Q_Data.ID  = PLC_LED_Q_ID_MODE;
		LED_Q_Data.Val = ((ModeIn == PLC_LED_MODE_ON) ? PLC_LED_MODE_ON : PLC_LED_MODE_OFF);

		//send data (not-blocking)
		xQueueSendToBack(RTOS_LED_Q, &LED_Q_Data, 0);
	}
#else
	(void)ChIn;
	(void)ModeIn;
#endif //RTE_MOD_LED
}


/** @brief  Set Mode.
 *  @param  ChIn   - channel number.
 *  @param  ModeIn - mode.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_LED_SetMode(uint8_t ChIn, uint8_t ModeIn)
{
#ifdef DEBUG_LOG_LED
	DebugLog("RTOS_LED_SetMode\n");
#endif // DEBUG_LOG_LED

	if(ChIn < PLC_LED_SZ)
	{
        if(PLC_LED[ChIn].Mode != ModeIn)
        {
        	PLC_LED[ChIn].Mode = ModeIn;
        	PlcGpio_DO_Set(PLC_LED[ChIn].Port, PLC_LED[ChIn].Pin, PLC_LED[ChIn].DOMode, PLC_LED[ChIn].Mode);

#ifdef DEBUG_LOG_LED
           	DebugLog("LED[%d].Mode=%d\n\n", ChIn, PLC_LED[ChIn].Mode);
#endif // DEBUG_LOG_LED

           	return (BIT_TRUE);
        }
	}
	return (BIT_FALSE);
}

/** @brief  Set settings.
 *  @param  DataIn - pointer to data.
 *  @return None.
 */
static void RTOS_LED_Set(const PlcLED_Q_t *DataIn)
{
    if(DataIn)
    {
        switch(DataIn->ID)
        {
            case PLC_LED_Q_ID_MODE:
            	RTOS_LED_SetMode(DataIn->Ch, DataIn->Val);
                break;
        }
    }
}

/** @brief  Init LED_T
 *  @param  None.
 *  @return None.
 */
static void RTOS_LED_Init(void)
{
#ifdef DEBUG_LOG_MAIN
    DebugLog("RTOS_LED_Init\n");
#endif // DEBUG_LOG_MAIN

    for(uint8_t i=0; i<PLC_LED_SZ; i++)
    {
    	PLC_LED[i].Ch   = i;
    	PLC_LED[i].Mode = PLC_LED_MODE_OFF;
    	PlcLed_Init(&PLC_LED[i]);
    }
}

/** @brief  DeInit LED_T
 *  @param  None.
 *  @return None.
 */
static void RTOS_LED_DeInit(void)
{
#ifdef DEBUG_LOG_MAIN
    DebugLog("RTOS_LED_DeInit\n");
#endif // DEBUG_LOG_MAIN

    for(uint8_t i=0; i<PLC_LED_SZ; i++)
    {
    	PlcLed_DeInit(&PLC_LED[i]);
    }
}


/** @brief  Task LED_T (blocked)
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return None.
 */
void RTOS_LED_Task(void *ParamsIn)
{
	//variables
	PlcLED_Q_t  LED_Q_Data;
    BaseType_t  LED_Q_Status;

    (void)ParamsIn; //fix unused

    RTOS_LED_Init();

    //start
    for(;;)
    {
    	//Read RTOS_LED_Q (blocking)
    	LED_Q_Status = xQueueReceive(RTOS_LED_Q, &LED_Q_Data, portMAX_DELAY);
		if(LED_Q_Status == pdPASS)
		{
			RTOS_LED_Set(&LED_Q_Data);
		}

        //fast switch to other task
        taskYIELD();
    }

    RTOS_LED_DeInit();
}
