/* @page rtos-do.c
 *       PLC411::RTE
 *       RTOS-task DO_T
 *       2022-2023, atgroup09@gmail.com
 */

#include "rtos-do.h"


#ifdef RTE_MOD_DO


/** @var Channels
 */
static PlcDO_t PLC_DO[PLC_DO_SZ];


/** @brief  Copy data into RTOS_DO_DATA_Q (confirmed data).
 *  @param  ChIn - channel number.
 *  @param  IDIn - queue ID.
 *  @return Result:
 *  @arg    = 0 - error
 *  @arg    = 1 - OK
 */
static uint8_t RTOS_DO_DATA_Q_Send(uint8_t ChIn, uint8_t IDIn)
{
	PlcDO_Q_t QueueData;

	if(ChIn < PLC_DO_SZ)
	{
		QueueData.Ch = ChIn;
		QueueData.ID = PLC_DO_Q_ID_NONE;

		switch(IDIn)
		{
			case PLC_DO_Q_ID_MODE:
				QueueData.ID  = IDIn;
				QueueData.Val = (float)PLC_DO[ChIn].Mode;
				break;

			case PLC_DO_Q_ID_NORM_VAL:
				QueueData.ID  = IDIn;
				QueueData.Val = (float)PLC_DO[ChIn].NormVal;
				break;

			case PLC_DO_Q_ID_FAST_VAL:
				QueueData.ID  = IDIn;
				QueueData.Val = (float)PLC_DO[ChIn].FastVal;
				break;

			case PLC_DO_Q_ID_PWM_T:
				QueueData.ID  = IDIn;
				QueueData.Val = PLC_DO[ChIn].PwmT;
				break;

			case PLC_DO_Q_ID_PWM_D:
				QueueData.ID  = IDIn;
				QueueData.Val = PLC_DO[ChIn].PwmD;
				break;

			case PLC_DO_Q_ID_PWM_ALLOW:
				QueueData.ID  = IDIn;
				QueueData.Val = (float)PLC_DO[ChIn].Pack.PwmAllow;
				break;

			case PLC_DO_Q_ID_SAFE_VAL:
				QueueData.ID  = IDIn;
				QueueData.Val = (float)PLC_DO[ChIn].SafeVal;
				break;

			case PLC_DO_Q_ID_SAFE_ALLOW:
				QueueData.ID  = IDIn;
				QueueData.Val = (float)PLC_DO[ChIn].Pack.SafeAllow;
				break;

			case PLC_DO_Q_ID_STATUS:
				QueueData.ID  = IDIn;
				QueueData.Val = (float)PLC_DO[ChIn].Status;
				break;
		}

		if(QueueData.ID != PLC_DO_Q_ID_NONE)
		{
			//Send data into RTOS_DO_DATA_Q (not-blocking)
			xQueueSendToBack(RTOS_DO_DATA_Q, &QueueData, 0);
			return (BIT_TRUE);
		}
	}
	return (BIT_FALSE);
}

/** @brief  Set Mode OFF.
 *  @param  ChIn - channel number.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_DO_SetModeOff(uint8_t ChIn)
{
	if(ChIn < PLC_DO_SZ)
	{
#ifdef DEBUG_LOG_DO_Q
	DebugLog("RTOS_AI_SetModeOff\n");
#endif // DEBUG_LOG_DO_Q

		PLC_DO[ChIn].Mode   = PLC_DO_MODE_OFF;
		PLC_DO[ChIn].Status = PLC_DO_STATUS_OFF;
		PlcDO_SetNormVal(&PLC_DO[ChIn], BIT_FALSE);

#ifdef DEBUG_LOG_DO_Q
	DebugLog("DO[%d].Mode=%d(OFF) .Stat=%d\n\n", ChIn, PLC_DO[ChIn].Mode, PLC_DO[ChIn].Status);
#endif // DEBUG_LOG_DO_Q
		return (BIT_TRUE);
	}
	return (BIT_FALSE);
}

/** @brief  Set Mode NORM.
 *  @param  ChIn - channel number.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_DO_SetModeNorm(uint8_t ChIn)
{
	if(ChIn < PLC_DO_SZ)
	{
#ifdef DEBUG_LOG_DO_Q
	DebugLog("RTOS_DO_SetModeNorm\n");
#endif // DEBUG_LOG_DO_Q

		PLC_DO[ChIn].Mode   = PLC_DO_MODE_NORM;
		PLC_DO[ChIn].Status = PLC_DO_STATUS_NORM;
		PlcDO_SetNormVal(&PLC_DO[ChIn], PLC_DO[ChIn].NormVal);

#ifdef DEBUG_LOG_DO_Q
	DebugLog("DO[%d].Mode=%d(NORM) .Stat=%d\n\n", ChIn, PLC_DO[ChIn].Mode, PLC_DO[ChIn].Status);
#endif // DEBUG_LOG_DO_Q
		return (BIT_TRUE);
	}
	return (BIT_FALSE);
}

/** @brief  Set Mode FAST.
 *  @param  ChIn - channel number.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_DO_SetModeFast(uint8_t ChIn)
{
	if(ChIn < PLC_DO_SZ)
	{
#ifdef DEBUG_LOG_DO_Q
	DebugLog("RTOS_DO_SetModeFast\n");
#endif // DEBUG_LOG_DO_Q

		PLC_DO[ChIn].Mode   = PLC_DO_MODE_FAST;
		PLC_DO[ChIn].Status = PLC_DO_STATUS_FAST;
		PlcDO_SetNormVal(&PLC_DO[ChIn], PLC_DO[ChIn].FastVal);

#ifdef DEBUG_LOG_DO_Q
	DebugLog("DO[%d].Mode=%d(FAST) .Stat=%d\n\n", ChIn, PLC_DO[ChIn].Mode, PLC_DO[ChIn].Status);
#endif // DEBUG_LOG_DO_Q
		return (BIT_TRUE);
	}
	return (BIT_FALSE);
}

/** @brief  Set Mode PWM.
 *  @param  ChIn - channel number.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_DO_SetModePwm(uint8_t ChIn)
{
	if(ChIn < PLC_DO_SZ)
	{
#ifdef DEBUG_LOG_DO_Q
	DebugLog("RTOS_DO_SetModePwm\n");
#endif // DEBUG_LOG_DO_Q

		PLC_DO[ChIn].Mode   = PLC_DO_MODE_PWM;
		PLC_DO[ChIn].Status = ((PLC_DO[ChIn].Pack.PwmAllow) ? PLC_DO_STATUS_PWM_ON : PLC_DO_STATUS_PWM_OFF);
		PlcDO_SetPulse(&PLC_DO[ChIn], PLC_DO[ChIn].PwmD);

#ifdef DEBUG_LOG_DO_Q
	DebugLog("DO[%d].Mode=%d(PWM) .Stat=%d\n\n", ChIn, PLC_DO[ChIn].Mode, PLC_DO[ChIn].Status);
#endif // DEBUG_LOG_DO_Q
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
static uint8_t RTOS_DO_SetMode(uint8_t ChIn, uint8_t ModeIn)
{
#ifdef DEBUG_LOG_DO_Q
	DebugLog("RTOS_DO_SetMode\n");
#endif // DEBUG_LOG_DO_Q

	if(ChIn < PLC_DO_SZ)
	{
		if(PLC_DO[ChIn].Mode != ModeIn)
		{
			switch(ModeIn)
			{
				case PLC_DO_MODE_OFF:
					RTOS_DO_SetModeOff(ChIn);
					break;

				case PLC_DO_MODE_NORM:
					RTOS_DO_SetModeNorm(ChIn);
					break;

				case PLC_DO_MODE_FAST:
					RTOS_DO_SetModeFast(ChIn);
					break;

				case PLC_DO_MODE_PWM:
					RTOS_DO_SetModePwm(ChIn);
					break;
			}

			RTOS_DO_DATA_Q_Send(ChIn, PLC_DO_Q_ID_MODE);
			RTOS_DO_DATA_Q_Send(ChIn, PLC_DO_Q_ID_STATUS);

			if(PLC_DO[ChIn].Status == PLC_DO_STATUS_NORM || PLC_DO[ChIn].Status == PLC_DO_STATUS_FAST || PLC_DO[ChIn].Status == PLC_DO_STATUS_PWM_ON)
			{
				PlcDO_Start(&PLC_DO[ChIn]);
			}
			else
			{
				PlcDO_Stop(&PLC_DO[ChIn]);
			}

			return (BIT_TRUE);
		}
	}
	return (BIT_FALSE);
}

/** @brief  Set NORM Value.
 *  @param  ChIn  - channel number.
 *  @param  ValIn - value.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_DO_SetNormVal(uint8_t ChIn, uint8_t ValIn)
{
#ifdef DEBUG_LOG_DO_Q_VAL
	DebugLog("RTOS_DO_SetNormVal\n");
#endif // DEBUG_LOG_DO_Q_VAL

	if(ChIn < PLC_DO_SZ)
	{
		if(PLC_DO[ChIn].NormVal != ValIn)
		{
			PLC_DO[ChIn].NormVal = ((ValIn) ? BIT_TRUE : BIT_FALSE);

			if(PLC_DO[ChIn].Mode == PLC_DO_MODE_NORM)
			{
				PlcDO_SetNormVal(&PLC_DO[ChIn], PLC_DO[ChIn].NormVal);
			}

			RTOS_DO_DATA_Q_Send(ChIn, PLC_DO_Q_ID_NORM_VAL);

#ifdef DEBUG_LOG_DO_Q_VAL
			DebugLog("DO[%d].NormVal=%d .Stat=%d\n\n", ChIn, PLC_DO[ChIn].NormVal, PLC_DO[ChIn].Status);
#endif // DEBUG_LOG_DO_Q_VAL
			return (BIT_TRUE);
		}
	}
	return (BIT_FALSE);
}

/** @brief  Set FAST Value.
 *  @param  ChIn  - channel number.
 *  @param  ValIn - value.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_DO_SetFastVal(uint8_t ChIn, uint8_t ValIn)
{
#ifdef DEBUG_LOG_DO_Q_VAL
	DebugLog("RTOS_DO_SetFastVal\n");
#endif // DEBUG_LOG_DO_Q_VAL

	if(ChIn < PLC_DO_SZ)
	{
		if(PLC_DO[ChIn].FastVal != ValIn)
		{
			PLC_DO[ChIn].FastVal = ((ValIn) ? BIT_TRUE : BIT_FALSE);

			if(PLC_DO[ChIn].Mode == PLC_DO_MODE_FAST)
			{
				PlcDO_SetNormVal(&PLC_DO[ChIn], PLC_DO[ChIn].FastVal);
			}

			RTOS_DO_DATA_Q_Send(ChIn, PLC_DO_Q_ID_FAST_VAL);

#ifdef DEBUG_LOG_DO_Q_VAL
			DebugLog("DO[%d].FastVal=%d .Stat=%d\n\n", ChIn, PLC_DO[ChIn].FastVal, PLC_DO[ChIn].Status);
#endif // DEBUG_LOG_DO_Q_VAL
			return (BIT_TRUE);
		}
	}
	return (BIT_FALSE);
}

/** @brief  Set PWM.Period.
 *  @param  ChIn  - channel number.
 *  @param  ValIn - value.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_DO_SetPwmPeriod(uint8_t ChIn, float ValIn)
{
#ifdef DEBUG_LOG_DO_Q_VAL
	DebugLog("RTOS_DO_SetPwmPeriod\n");
#endif // DEBUG_LOG_DO_Q_VAL

	if(ChIn < PLC_DO_SZ)
	{
		if(PLC_DO[ChIn].PwmT != ValIn)
		{
			PLC_DO[ChIn].PwmT = PlcDO_SetPeriod(&PLC_DO[ChIn], ValIn);
			//refresh pulse
			PlcDO_SetPulse(&PLC_DO[ChIn], PLC_DO[ChIn].PwmD);
			RTOS_DO_DATA_Q_Send(ChIn, PLC_DO_Q_ID_PWM_T);

#ifdef DEBUG_LOG_DO_Q_VAL
			DebugLog("DO[%d].PwmT=%f .Arr=%d .Ka=%f .Kb=%f .PwmD=%f .Ccr=%d .Stat=%d\n\n", ChIn, PLC_DO[ChIn].PwmT, PLC_DO[ChIn].Arr, PLC_DO[ChIn].Ka, PLC_DO[ChIn].Kb, PLC_DO[ChIn].PwmD, PLC_DO[ChIn].Ccr, PLC_DO[ChIn].Status);
#endif // DEBUG_LOG_DO_Q_VAL
			return (BIT_TRUE);
		}
	}
	return (BIT_FALSE);
}

/** @brief  Set PWM.Pulse.
 *  @param  ChIn  - channel number.
 *  @param  ValIn - value.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_DO_SetPwmPulse(uint8_t ChIn, float ValIn)
{
#ifdef DEBUG_LOG_DO_Q_VAL
	DebugLog("RTOS_DO_SetPwmPulse\n");
#endif // DEBUG_LOG_DO_Q_VAL

	if(ChIn < PLC_DO_SZ)
	{
		if(PLC_DO[ChIn].PwmD != ValIn)
		{
			PLC_DO[ChIn].PwmD = PlcDO_SetPulse(&PLC_DO[ChIn], ValIn);
			RTOS_DO_DATA_Q_Send(ChIn, PLC_DO_Q_ID_PWM_D);

#ifdef DEBUG_LOG_DO_Q_VAL
			DebugLog("DO[%d].PwmT=%f .Arr=%d .Ka=%f .Kb=%f .PwmD=%f .Ccr=%d .Stat=%d\n\n", ChIn, PLC_DO[ChIn].PwmT, PLC_DO[ChIn].Arr, PLC_DO[ChIn].Ka, PLC_DO[ChIn].Kb, PLC_DO[ChIn].PwmD, PLC_DO[ChIn].Ccr, PLC_DO[ChIn].Status);
#endif // DEBUG_LOG_DO_Q_VAL
			return (BIT_TRUE);
		}
	}
	return (BIT_FALSE);
}

/** @brief  Set PWM.Allow.
 *  @param  ChIn  - channel number.
 *  @param  ValIn - value.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_DO_SetPwmAllow(uint8_t ChIn, uint8_t ValIn)
{
#ifdef DEBUG_LOG_DO_Q_VAL
	DebugLog("RTOS_DO_SetPwmAllow\n");
#endif // DEBUG_LOG_DO_Q_VAL

	if(ChIn < PLC_DO_SZ)
	{
		if(PLC_DO[ChIn].Pack.PwmAllow != ValIn)
		{
			PLC_DO[ChIn].Pack.PwmAllow = ((ValIn) ? BIT_TRUE : BIT_FALSE);

			if(PLC_DO[ChIn].Mode == PLC_DO_MODE_PWM)
			{
				if(PLC_DO[ChIn].Pack.PwmAllow)
				{
					PLC_DO[ChIn].Status = PLC_DO_STATUS_PWM_ON;
					PlcDO_Start(&PLC_DO[ChIn]);
				}
				else
				{
					PLC_DO[ChIn].Status = PLC_DO_STATUS_PWM_OFF;
					PlcDO_Stop(&PLC_DO[ChIn]);
				}
			}

			RTOS_DO_DATA_Q_Send(ChIn, PLC_DO_Q_ID_PWM_ALLOW);
			RTOS_DO_DATA_Q_Send(ChIn, PLC_DO_Q_ID_STATUS);

#ifdef DEBUG_LOG_DO_Q_VAL
			DebugLog("DO[%d].Mode=%d .Pack.PwmAllow=%d .Stat=%d\n\n", ChIn, PLC_DO[ChIn].Mode, PLC_DO[ChIn].Pack.PwmAllow, PLC_DO[ChIn].Status);
#endif // DEBUG_LOG_DO_Q_VAL
			return (BIT_TRUE);
		}
	}
	return (BIT_FALSE);
}

/** @brief  Set SAFE.Value.
 *  @param  ChIn  - channel number.
 *  @param  ValIn - value.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_DO_SetSafeVal(uint8_t ChIn, uint8_t ValIn)
{
#ifdef DEBUG_LOG_DO_Q_VAL
	DebugLog("RTOS_DO_SetSafeVal\n");
#endif // DEBUG_LOG_DO_Q_VAL

	if(ChIn < PLC_DO_SZ)
	{
		if(PLC_DO[ChIn].SafeVal != ValIn)
		{
			PLC_DO[ChIn].SafeVal = ((ValIn) ? BIT_TRUE : BIT_FALSE);
			RTOS_DO_DATA_Q_Send(ChIn, PLC_DO_Q_ID_SAFE_VAL);

#ifdef DEBUG_LOG_DO_Q_VAL
			DebugLog("DO[%d].SafeVal=%d .Pack.SafeAllow=%d .Stat=%d\n\n", ChIn, PLC_DO[ChIn].SafeVal, PLC_DO[ChIn].Pack.SafeAllow, PLC_DO[ChIn].Status);
#endif // DEBUG_LOG_DO_Q_VAL
			return (BIT_TRUE);
		}
	}
	return (BIT_FALSE);
}

/** @brief  Set SAFE.Allow.
 *  @param  ChIn  - channel number.
 *  @param  ValIn - value.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_DO_SetSafeAllow(uint8_t ChIn, uint8_t ValIn)
{
#ifdef DEBUG_LOG_DO_Q_VAL
	DebugLog("RTOS_DO_SetSafeAllow\n");
#endif // DEBUG_LOG_DO_Q_VAL

	if(ChIn < PLC_DO_SZ)
	{
		if(PLC_DO[ChIn].Pack.SafeAllow != ValIn)
		{
			PLC_DO[ChIn].Pack.SafeAllow = ((ValIn) ? BIT_TRUE : BIT_FALSE);
			RTOS_DO_DATA_Q_Send(ChIn, PLC_DO_Q_ID_SAFE_ALLOW);

#ifdef DEBUG_LOG_DO_Q_VAL
			DebugLog("DO[%d].SafeVal=%d .Pack.SafeAllow=%d .Stat=%d\n\n", ChIn, PLC_DO[ChIn].SafeVal, PLC_DO[ChIn].Pack.SafeAllow, PLC_DO[ChIn].Status);
#endif // DEBUG_LOG_DO_Q_VAL
			return (BIT_TRUE);
		}
	}
	return (BIT_FALSE);
}

/** @brief  Set POSTPON.Value.
 *  @param  ChIn  - channel number.
 *  @param  ValIn - value.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_DO_SetPostponedVal(uint8_t ChIn, uint8_t ValIn)
{
#ifdef DEBUG_LOG_DO_Q_VAL
	DebugLog("RTOS_DO_SetPostponedVal\n");
#endif // DEBUG_LOG_DO_Q_VAL

	if(ChIn < PLC_DO_SZ)
	{
		if(PLC_DO[ChIn].PostponedVal != ValIn)
		{
			PLC_DO[ChIn].PostponedVal      = ((ValIn) ? BIT_TRUE : BIT_FALSE);
			PLC_DO[ChIn].Pack.PostponReady = BIT_TRUE;

#ifdef DEBUG_LOG_DO_Q_VAL
			DebugLog("DO[%d].PostponedVal=%d .Pack.Postponed=%d .Stat=%d\n\n", ChIn, PLC_DO[ChIn].PostponedVal, PLC_DO[ChIn].Pack.PostponReady, PLC_DO[ChIn].Status);
#endif // DEBUG_LOG_DO_Q_VAL
			return (BIT_TRUE);
		}
	}
	return (BIT_FALSE);
}

/** @brief  Set POSTPON.Apply (command to set all postponed valued).
 *  @param  ValIn - value.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_DO_SetPostponedApply(uint8_t ValIn)
{
#ifdef DEBUG_LOG_DO_Q_VAL
	DebugLog("RTOS_DO_SetPostponedApply\n");
#endif // DEBUG_LOG_DO_Q_VAL

	if(ValIn)
	{
		for(uint8_t i=0; i<PLC_DO_SZ; i++)
		{
			if(PLC_DO[i].Mode == PLC_DO_MODE_NORM && PLC_DO[i].Pack.PostponReady)
			{
				RTOS_DO_SetNormVal(i, PLC_DO[i].PostponedVal);
				PLC_DO[i].Pack.PostponReady = BIT_FALSE;
			}
		}
		return (BIT_TRUE);
	}
	return (BIT_FALSE);
}

/** @brief  Set settings.
 *  @param  DataIn - pointer to data.
 *  @return None.
 */
static void RTOS_DO_Set(const PlcDO_Q_t *DataIn)
{
    if(DataIn)
    {
        switch(DataIn->ID)
        {
            case PLC_DO_Q_ID_MODE:
            	RTOS_DO_SetMode(DataIn->Ch, (uint8_t)DataIn->Val);
                break;

            case PLC_DO_Q_ID_NORM_VAL:
            	RTOS_DO_SetNormVal(DataIn->Ch, (uint8_t)DataIn->Val);
            	break;

            case PLC_DO_Q_ID_FAST_VAL:
            	RTOS_DO_SetFastVal(DataIn->Ch, (uint8_t)DataIn->Val);
            	break;

            case PLC_DO_Q_ID_PWM_T:
            	RTOS_DO_SetPwmPeriod(DataIn->Ch, DataIn->Val);
            	break;

            case PLC_DO_Q_ID_PWM_D:
            	RTOS_DO_SetPwmPulse(DataIn->Ch, DataIn->Val);
            	break;

            case PLC_DO_Q_ID_PWM_ALLOW:
            	RTOS_DO_SetPwmAllow(DataIn->Ch, (uint8_t)DataIn->Val);
            	break;

            case PLC_DO_Q_ID_SAFE_VAL:
            	RTOS_DO_SetSafeVal(DataIn->Ch, (uint8_t)DataIn->Val);
            	break;

            case PLC_DO_Q_ID_SAFE_ALLOW:
            	RTOS_DO_SetSafeAllow(DataIn->Ch, (uint8_t)DataIn->Val);
            	break;

            case PLC_DO_Q_ID_POSTPONED_VAL:
            	RTOS_DO_SetPostponedVal(DataIn->Ch, (uint8_t)DataIn->Val);
            	break;

            case PLC_DO_Q_ID_POSTPONED_APPLY:
            	RTOS_DO_SetPostponedApply((uint8_t)DataIn->Val);
            	break;
        }
    }
}

/** @brief  Init DO_T
 *  @param  None.
 *  @return None.
 */
static void RTOS_DO_Init(void)
{
#ifdef DEBUG_LOG_MAIN
    DebugLog("RTOS_DO_Init\n");
#endif // DEBUG_LOG_MAIN

    uint8_t BuffBy;
    float   BuffFlo;

	for(uint8_t i=0; i<PLC_DO_SZ; i++)
	{
		PLC_DO[i].Ch = i;

		PlcDO_Init(&PLC_DO[i]);

		BuffBy = PLC_DO_MODE_DEF;
		REG_CopyRegByPos(REG_DO_MODE__POS+i, REG_COPY_MB_TO_VAR, &BuffBy);
		PLC_DO[i].Mode = BuffBy;

        BuffFlo = PLC_DO_PWM_T_DEF;
        REG_CopyRegByPos(REG_DO_PWM_PERIOD__POS+i, REG_COPY_MB_TO_VAR, &BuffFlo);
	    PLC_DO[i].PwmT = BuffFlo;

        BuffFlo = PLC_DO_PWM_D_DEF;
        REG_CopyRegByPos(REG_DO_PWM_VAL__POS+i, REG_COPY_MB_TO_VAR, &BuffFlo);
	    PLC_DO[i].PwmD = BuffFlo;

		BuffBy = PLC_DO_PWM_ALLOW_DEF;
		REG_CopyRegByPos(REG_DO_PWM_ALLOW__POS+i, REG_COPY_MB_TO_VAR, &BuffBy);
		PLC_DO[i].Pack.PwmAllow = BuffBy;

		PLC_DO[i].Pack.SafeAllow    = PLC_DO_SAFE_ALLOW_DEF;
		PLC_DO[i].Pack.PostponReady = BIT_FALSE;

		BuffBy = PLC_DO_NORM_VAL_DEF;
		REG_CopyRegByPos(REG_DO_NORM_VAL__POS+i, REG_COPY_MB_TO_VAR, &BuffBy);
		PLC_DO[i].NormVal = BuffBy;

		BuffBy = PLC_DO_FAST_VAL_DEF;
		REG_CopyRegByPos(REG_DO_FAST_VAL__POS+i, REG_COPY_MB_TO_VAR, &BuffBy);
		PLC_DO[i].FastVal = BuffBy;

		PLC_DO[i].SafeVal      = PLC_DO_SAFE_VAL_DEF;
		PLC_DO[i].PostponedVal = BIT_FALSE;

        PLC_DO[i].Status = PLC_DO[i].Mode;

        //set TIM.PWM.Period
        PlcDO_SetPeriod(&PLC_DO[i], PLC_DO[i].PwmT);

        //set TIM.PWM.CH.Pulse
        if(PLC_DO[i].Mode == PLC_DO_MODE_NORM)
        {
        	PlcDO_SetNormVal(&PLC_DO[i], PLC_DO[i].NormVal);
        }
        else if(PLC_DO[i].Mode == PLC_DO_MODE_FAST)
        {
        	PlcDO_SetNormVal(&PLC_DO[i], PLC_DO[i].FastVal);
        }
        else if(PLC_DO[i].Mode == PLC_DO_MODE_PWM)
        {
        	PlcDO_SetPulse(&PLC_DO[i], PLC_DO[i].PwmD);
        }

        if(PLC_DO[i].Mode == PLC_DO_MODE_NORM || PLC_DO[i].Mode == PLC_DO_MODE_FAST || PLC_DO[i].Mode == PLC_DO_MODE_PWM)
        {
        	PlcDO_Start(&PLC_DO[i]);
        }

#ifdef DEBUG_LOG_DO
        DebugLog("DO[%d].Mode=%d .NormVal=%d .FastVal=%d .PwmT=%f .PwmD=%f .Pack.PwmAllow=%d\n", i, PLC_DO[i].Mode, PLC_DO[i].NormVal, PLC_DO[i].FastVal, PLC_DO[i].PwmT, PLC_DO[i].PwmD, PLC_DO[i].Pack.PwmAllow);
#endif // DEBUG_LOG_DO
	}
}

/** @brief  DeInit DO_T
 *  @param  None.
 *  @return None.
 */
static void RTOS_DO_DeInit(void)
{
#ifdef DEBUG_LOG_MAIN
    DebugLog("RTOS_DO_DeInit\n");
#endif // DEBUG_LOG_MAIN

    for(uint8_t i=0; i<PLC_DO_SZ; i++)
    {
    	PlcDO_DeInit(&PLC_DO[i]);
    }
}


/** @brief  Task DO_T (blocked)
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return None.
 */
void RTOS_DO_Task(void *ParamsIn)
{
	//variables
	PlcDO_Q_t  QueueData;
	BaseType_t QueueStatus;

	(void)ParamsIn; //fix unused

	RTOS_DO_Init();

	//start
	for(;;)
	{
		//Read Queue (blocking)
		//get command ID
		QueueStatus = xQueueReceive(RTOS_DO_Q, &QueueData, portMAX_DELAY);
		if(QueueStatus == pdPASS)
		{
			RTOS_DO_Set(&QueueData);
		}

        //fast switch to other task
        taskYIELD();
	}

	RTOS_DO_DeInit();
}

#endif //RTE_MOD_DO
