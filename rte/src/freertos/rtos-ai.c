/* @page rtos-ai.c
 *       PLC411::RTE
 *       RTOS-task AI_T
 *       2022-2023, atgroup09@gmail.com
 */

#include "rtos-ai.h"


#ifdef RTE_MOD_AI

/** @var Channels
 */
static PlcAI_t PLC_AI[PLC_AI_SZ];

/** @var Timer statuses
 */
static uint8_t PLC_AI_TIM_STATUS = BIT_FALSE;


/** @brief  Copy data into RTOS_AI_DATA_Q.
 *  @param  ChIn - channel number.
 *  @param  IDIn - queue ID.
 *  @return Result:
 *  @arg    = 0 - error
 *  @arg    = 1 - OK
 */
static uint8_t RTOS_AI_DATA_Q_Send(uint8_t ChIn, uint8_t IDIn)
{
	PlcAI_Q_t QueueData;

	if(ChIn < PLC_AI_SZ)
	{
		QueueData.Ch = ChIn;
		QueueData.ID = PLC_AI_Q_ID_NONE;

		switch(IDIn)
		{
			case PLC_AI_Q_ID_MODE:
				QueueData.ID  = IDIn;
				QueueData.Val = (float)PLC_AI[ChIn].Mode;
				break;

			case PLC_AI_Q_ID_VAL:
				QueueData.ID  = IDIn;
				QueueData.Val = PLC_AI[ChIn].Val;
				break;

			case PLC_AI_Q_ID_KA:
				QueueData.ID  = IDIn;
				QueueData.Val = PLC_AI[ChIn].Ka;
				break;

			case PLC_AI_Q_ID_KB:
				QueueData.ID  = IDIn;
				QueueData.Val = PLC_AI[ChIn].Kb;
				break;

			case PLC_AI_Q_ID_STATUS:
				QueueData.ID  = IDIn;
				QueueData.Val = (float)PLC_AI[ChIn].Status;
				break;
		}

		if(QueueData.ID != PLC_AI_Q_ID_NONE)
		{
			//Send data into RTOS_AI_DATA_Q (not-blocking)
			xQueueSendToBack(RTOS_AI_DATA_Q, &QueueData, 0);
			return (BIT_TRUE);
		}
	}
	return (BIT_FALSE);
}


/** @brief  Start TIM_AI.
 *  @param  FromIsrIn:
 *  @arg    = 0 - normal API
 *  @arg    = 1 - FromISR API
 *  @return None.
 */
static void RTOS_AI_TIM_Start(uint8_t FromIsrIn)
{
	if(!PLC_AI_TIM_STATUS)
	{
#ifdef DEBUG_LOG_AI_TIM
		DebugLog("RTOS_AI_TimStart\n");
#endif // DEBUG_LOG_AI_TIM

		if(!FromIsrIn)
		{
			xTimerReset(RTOS_AI_TIM, 0);
		}
		else
		{
			xTimerResetFromISR(RTOS_AI_TIM, 0);
		}

		PLC_AI_TIM_STATUS = BIT_TRUE;
    }
}

/** @brief  Stop TIM_AI.
 *  @param  None.
 *  @return None.
 */
static void RTOS_AI_TIM_Stop(void)
{
	if(PLC_AI_TIM_STATUS)
	{
#ifdef DEBUG_LOG_AI_TIM
		DebugLog("RTOS_AI_TimStop\n");
#endif // DEBUG_LOG_AI_TIM

		xTimerStop(RTOS_AI_TIM, 0);
		PLC_AI_TIM_STATUS = BIT_FALSE;
    }
}


/** @brief  Set Mode OFF.
 *  @param  ChIn - channel number.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_AI_SetModeOff(uint8_t ChIn)
{
	if(ChIn < PLC_AI_SZ)
	{
#ifdef DEBUG_LOG_AI_Q
	DebugLog("RTOS_AI_SetModeOff\n");
#endif // DEBUG_LOG_AI_Q

		PLC_AI[ChIn].Mode   = PLC_AI_MODE_OFF;
		PLC_AI[ChIn].Status = PLC_AI_STATUS_OFF;

#ifdef DEBUG_LOG_AI_Q
	DebugLog("AI[%d].Mode=%d(OFF) .Stat=%d\n\n", ChIn, PLC_AI[ChIn].Mode, PLC_AI[ChIn].Status);
#endif // DEBUG_LOG_AI_Q
		return (BIT_TRUE);
	}
	return (BIT_FALSE);
}

/** @brief  Set Mode SURVEY.
 *  @param  ChIn - channel number.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_AI_SetModeSurvey(uint8_t ChIn)
{
	if(ChIn < PLC_AI_SZ)
	{
#ifdef DEBUG_LOG_AI_Q
	DebugLog("RTOS_AI_SetModeSurvey\n");
#endif // DEBUG_LOG_AI_Q

		PLC_AI[ChIn].Mode   = PLC_AI_MODE_SURVEY;
		PLC_AI[ChIn].Status = PLC_AI_STATUS_SURVEY;

#ifdef DEBUG_LOG_AI_Q
	DebugLog("AI[%d].Mode=%d(SURV) .Stat=%d\n\n", ChIn, PLC_AI[ChIn].Mode, PLC_AI[ChIn].Status);
#endif // DEBUG_LOG_AI_Q
		return (BIT_TRUE);
	}
	return (BIT_FALSE);
}

/** @brief  Set Mode SURVEY_TMP_MCU.
 *  @param  ChIn - channel number.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_AI_SetModeTmpMcu(uint8_t ChIn)
{
	if(ChIn < PLC_AI_SZ)
	{
#ifdef DEBUG_LOG_AI_Q
	DebugLog("RTOS_AI_SetModeTmpMcu\n");
#endif // DEBUG_LOG_AI_Q

		PLC_AI[ChIn].Mode   = PLC_AI_MODE_SURVEY_TMP_MCU;
		PLC_AI[ChIn].Status = PLC_AI_STATUS_SURVEY_TMP_MCU;

#ifdef DEBUG_LOG_AI_Q
	DebugLog("AI[%d].Mode=%d(TMP_MCU) .Stat=%d\n\n", ChIn, PLC_AI[ChIn].Mode, PLC_AI[ChIn].Status);
#endif // DEBUG_LOG_AI_Q
		return (BIT_TRUE);
	}
	return (BIT_FALSE);
}

/** @brief  Set Mode SURVEY_TMP36.
 *  @param  ChIn - channel number.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_AI_SetModeTmp36(uint8_t ChIn)
{
	if(ChIn < PLC_AI_SZ)
	{
#ifdef DEBUG_LOG_AI_Q
	DebugLog("RTOS_AI_SetModeTmp36\n");
#endif // DEBUG_LOG_AI_Q

		PLC_AI[ChIn].Mode   = PLC_AI_MODE_SURVEY_TMP36;
		PLC_AI[ChIn].Status = PLC_AI_STATUS_SURVEY_TMP36;

#ifdef DEBUG_LOG_AI_Q
	DebugLog("AI[%d].Mode=%d(TMP36) .Stat=%d\n\n", ChIn, PLC_AI[ChIn].Mode, PLC_AI[ChIn].Status);
#endif // DEBUG_LOG_AI_Q
		return (BIT_TRUE);
	}
	return (BIT_FALSE);
}

/** @brief  Set Mode.
 *  @param  ChIn   - channel number.
 *  @param  ModeIn - mode.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_AI_SetMode(uint8_t ChIn, uint8_t ModeIn)
{
#ifdef DEBUG_LOG_AI_Q
	DebugLog("RTOS_AI_SetMode\n");
#endif // DEBUG_LOG_AI_Q

	if(ChIn < PLC_AI_SZ)
	{
		if(PLC_AI[ChIn].Mode != ModeIn)
		{
			switch(ModeIn)
			{
				case PLC_AI_MODE_OFF:
					RTOS_AI_SetModeOff(ChIn);
					break;

				case PLC_AI_MODE_SURVEY:
					RTOS_AI_SetModeSurvey(ChIn);
					break;

				case PLC_AI_MODE_SURVEY_TMP_MCU:
					RTOS_AI_SetModeTmpMcu(ChIn);
					break;

				case PLC_AI_MODE_SURVEY_TMP36:
					RTOS_AI_SetModeTmp36(ChIn);
					break;
			}

			RTOS_AI_DATA_Q_Send(ChIn, PLC_AI_Q_ID_MODE);
			RTOS_AI_DATA_Q_Send(ChIn, PLC_AI_Q_ID_STATUS);

			if(PLC_AI[ChIn].Mode == PLC_AI_MODE_SURVEY || PLC_AI[ChIn].Mode == PLC_AI_MODE_SURVEY_TMP36 || PLC_AI[ChIn].Mode == PLC_AI_MODE_SURVEY_TMP_MCU)
			{
				PlcAI_Start();
			}

			return (BIT_TRUE);
		}
	}
	return (BIT_FALSE);
}

/** @brief  Set Value.
 *  @param  ChIn  - channel number.
 *  @param  ValIn - value.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_AI_SetVal(uint8_t ChIn, float ValIn)
{
#ifdef DEBUG_LOG_AI_Q_VAL
	DebugLog("RTOS_AI_SetVal\n");
#endif // DEBUG_LOG_AI_Q_VAL

	if(ChIn < PLC_AI_SZ)
	{
		if(PLC_AI[ChIn].Val != ValIn)
		{
			PLC_AI[ChIn].Val = ValIn;
			RTOS_AI_DATA_Q_Send(ChIn, PLC_AI_Q_ID_VAL);

#ifdef DEBUG_LOG_AI_Q_VAL
			DebugLog("AI[%d].Val=%f\n\n", ChIn, PLC_AI[ChIn].Val);
#endif // DEBUG_LOG_AI_Q_VAL
			return (BIT_TRUE);
		}
	}
	return (BIT_FALSE);
}

/** @brief  Set Ka.
 *  @param  ChIn  - channel number.
 *  @param  KaIn  - Ka.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_AI_SetKa(uint8_t ChIn, float KaIn)
{
#ifdef DEBUG_LOG_AI_Q
	DebugLog("RTOS_AI_SetKa\n");
#endif //DEBUG_LOG_AI_Q

	if(ChIn < PLC_AI_SZ)
	{
		if(PLC_AI[ChIn].Ka != KaIn)
		{
			PLC_AI[ChIn].Ka = KaIn;
			RTOS_AI_DATA_Q_Send(ChIn, PLC_AI_Q_ID_KA);

#ifdef DEBUG_LOG_AI_Q
			DebugLog("AI[%d].Ka=%f\n\n", ChIn, PLC_AI[ChIn].Ka);
#endif // DEBUG_LOG_AI_Q
			return (BIT_TRUE);
		}
	}
	return (BIT_FALSE);
}

/** @brief  Set Kb.
 *  @param  ChIn  - channel number.
 *  @param  KbIn  - Kb.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_AI_SetKb(uint8_t ChIn, float KbIn)
{
#ifdef DEBUG_LOG_AI_Q
	DebugLog("RTOS_AI_SetKb\n");
#endif // DEBUG_LOG_AI_Q

	if(ChIn < PLC_AI_SZ)
	{
		if(PLC_AI[ChIn].Kb != KbIn)
		{
			PLC_AI[ChIn].Kb = KbIn;
			RTOS_AI_DATA_Q_Send(ChIn, PLC_AI_Q_ID_KB);

#ifdef DEBUG_LOG_AI_Q
			DebugLog("AI[%d].Kb=%f\n\n", ChIn, PLC_AI[ChIn].Kb);
#endif // DEBUG_LOG_AI_Q
			return (BIT_TRUE);
		}
	}
	return (BIT_FALSE);
}

/** @brief  Set settings.
 *  @param  DataIn - pointer to data.
 *  @return None.
 */
static void RTOS_AI_Set(const PlcAI_Q_t *DataIn)
{
    if(DataIn)
    {
        switch(DataIn->ID)
        {
            case PLC_AI_Q_ID_MODE:
            	RTOS_AI_SetMode(DataIn->Ch, (uint8_t)DataIn->Val);
                break;

            case PLC_AI_Q_ID_VAL:
            	RTOS_AI_SetVal(DataIn->Ch, DataIn->Val);
            	break;

            case PLC_AI_Q_ID_KA:
            	RTOS_AI_SetKa(DataIn->Ch, DataIn->Val);
            	break;

            case PLC_AI_Q_ID_KB:
            	RTOS_AI_SetKb(DataIn->Ch, DataIn->Val);
            	break;
        }
    }
}


/** @brief  Callback for IRQ.AI.ConvCplt.
 *  @param  None.
 *  @return None.
 */
static void PlcAI_ConvCplt(void)
{
#ifdef DEBUG_LOG_ADC
    DebugLog("PlcAI_ConvCplt\n");
#endif // DEBUG_LOG_ADC

    PlcAI_Stop();
    RTOS_AI_TIM_Start(BIT_TRUE);
}


/** @brief  Init AI_T
 *  @param  None.
 *  @return None.
 */
static void RTOS_AI_Init(void)
{
#ifdef DEBUG_LOG_MAIN
    DebugLog("RTOS_AI_Init\n");
#endif // DEBUG_LOG_MAIN

    uint8_t cSurv = 0;
	uint8_t BuffBy;
	float   BuffFlo;

	for(uint8_t i=0; i<PLC_AI_SZ; i++)
	{
		PLC_AI[i].Ch = i;

		BuffBy = PLC_AI_MODE_DEF;
		REG_CopyRegByPos(REG_AI_MODE__POS+i, REG_COPY_MB_TO_VAR, &BuffBy);
		PLC_AI[i].Mode = BuffBy;

        PLC_AI[i].Status = PLC_AI[i].Mode;
        PLC_AI[i].Val    = PLC_AI_ANA_DEF;

        BuffFlo = PLC_AI_KA_DEF;
        REG_CopyRegByPos(REG_AI_KA__POS+i, REG_COPY_MB_TO_VAR, &BuffFlo);
	    PLC_AI[i].Ka = BuffFlo;

	    BuffFlo = PLC_AI_KB_DEF;
	    REG_CopyRegByPos(REG_AI_KB__POS+i, REG_COPY_MB_TO_VAR, &BuffFlo);
	    PLC_AI[i].Kb = BuffFlo;

		if(PLC_AI[i].Mode == PLC_AI_MODE_SURVEY || PLC_AI[i].Mode == PLC_AI_MODE_SURVEY_TMP36 || PLC_AI[i].Mode == PLC_AI_MODE_SURVEY_TMP_MCU)
		{
			cSurv++;
		}

#ifdef DEBUG_LOG_AI
        DebugLog("AI[%d].Mode=%d .Val=%f .Ka=%f .Kb=%f\n", i, PLC_AI[i].Mode, PLC_AI[i].Val, PLC_AI[i].Ka, PLC_AI[i].Kb);
#endif // DEBUG_LOG_AI
	}

	PLC_ADC1_USER_FUNC.ConvCplt = PlcAI_ConvCplt;

	PlcAI_Init();
	if(cSurv) PlcAI_Start();
}

/** @brief  DeInit AI_T
 *  @param  None.
 *  @return None.
 */
static void RTOS_AI_DeInit(void)
{
#ifdef DEBUG_LOG_MAIN
    DebugLog("RtosAI_Task_DeInit\n");
#endif // DEBUG_LOG_MAIN

	PlcAI_Stop();
	PlcAI_DeInit();
}


/** @brief  Task AI_T (blocked)
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return None.
 */
void RTOS_AI_Task(void *ParamsIn)
{
	//variables
	PlcAI_Q_t  QueueData;
	BaseType_t QueueStatus;

	(void)ParamsIn; //fix unused

	RTOS_AI_Init();

	//start
	for(;;)
	{
		//Read Queue (blocking)
		//get command ID
		QueueStatus = xQueueReceive(RTOS_AI_Q, &QueueData, portMAX_DELAY);
		if(QueueStatus == pdPASS)
		{
			RTOS_AI_Set(&QueueData);
		}

        //fast switch to other task
        taskYIELD();
	}

	RTOS_AI_DeInit();
}


/** @brief  TIM_AI Handler (one-shot).
 *  @param  TimerIn - timer.
 *  @return None.
 *  @note   Delay of ADC conversion.
 */
void RTOS_AI_TIM_Handler(TimerHandle_t TimerIn)
{
#ifdef DEBUG_LOG_AI_TIM
	DebugLog("RTOS_AI_TimHandler\n");
#endif // DEBUG_LOG_AI_TIM

	uint8_t cSurv = 0;
	PlcAI_Q_t QueueData;

	//fix unused
	(void)TimerIn;

	RTOS_AI_TIM_Stop();

	for(uint8_t i=0; i<PLC_AI_SZ; i++)
    {
        if(PLC_AI[i].Mode == PLC_AI_MODE_SURVEY || PLC_AI[i].Mode == PLC_AI_MODE_SURVEY_TMP36 || PLC_AI[i].Mode == PLC_AI_MODE_SURVEY_TMP_MCU)
        {
        	QueueData.Val = PlcAI_GetAna(i);
        	cSurv++;

        	if(PLC_AI[i].Mode == PLC_AI_MODE_SURVEY)
        	{
        		//auto scale by custom Ka and Kb
        		QueueData.Val = ScaleA(QueueData.Val, PLC_AI[i].Ka, PLC_AI[i].Kb);
        	}
            else if(PLC_AI[i].Mode == PLC_AI_MODE_SURVEY_TMP36)
            {
            	//auto scale by algorithm TMP36 (Analog Devices)
            	QueueData.Val = Tmp36_GetTemp(QueueData.Val);
            }
            else if(PLC_AI[i].Mode == PLC_AI_MODE_SURVEY_TMP_MCU)
            {
            	//auto scale by algorithm MCU_TEMP (STM32F411)
            	QueueData.Val = TmpMcu_GetTemp(QueueData.Val);
            }

        	if(PLC_AI[i].Val != QueueData.Val)
        	{
        		QueueData.Ch = i;
        		QueueData.ID = PLC_AI_Q_ID_VAL;
        		//Send data into RTOS_AI_Q (not-blocking)
        		xQueueSendToBack(RTOS_AI_Q, &QueueData, 0);
        	}
        }
    }

	//If a AI-channel is configured to survey-mode, then restart ADC conversion
	if(cSurv) PlcAI_Start();
}

#endif //RTE_MOD_AI
