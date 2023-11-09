/* @page rtos-di.c
 *       PLC411::RTE
 *       RTOS-task DI_T
 *       2022-2023, atgroup09@gmail.com
 */

#include "rtos-di.h"


#ifdef RTE_MOD_DI

/** @var Channels
 */
static PlcDI_t PLC_DI[PLC_DI_SZ];
volatile PlcDI_Fltr_t PLC_DI_FLTR[PLC_DI_SZ];

/** @var Timer statuses
 */
static uint8_t PLC_DI_TACH_TIM_STATUS = BIT_FALSE;
static uint8_t PLC_DI_FLTR_TIM_STATUS = BIT_FALSE;


/** @brief  Set Channel-data into Queue-package.
 *  @param  ChIn - channel number.
 *  @param  IDIn - queue ID.
 *  @return Result:
 *  @arg    = 0 - error
 *  @arg    = 1 - OK
 */
static uint8_t RTOS_DI_DATA_Q_Send(uint8_t ChIn, uint8_t IDIn)
{
	PlcDI_Q_t QueueData;

	if(ChIn < PLC_DI_SZ)
	{
		QueueData.Ch = ChIn;
		QueueData.ID = PLC_DI_Q_ID_NONE;

		switch(IDIn)
		{
			case PLC_DI_Q_ID_MODE:
				QueueData.ID  = IDIn;
				QueueData.Val = (uint32_t)PLC_DI[ChIn].Mode;
				break;

			case PLC_DI_Q_ID_NORM_VAL:
				QueueData.ID  = IDIn;
				QueueData.Val = (uint32_t)PLC_DI[ChIn].NormVal;
				break;

			case PLC_DI_Q_ID_CNTR_VAL:
				QueueData.ID  = IDIn;
				QueueData.Val = PLC_DI[ChIn].CntrVal;
				break;

			case PLC_DI_Q_ID_CNTR_SETPOINT:
				QueueData.ID  = IDIn;
				QueueData.Val = PLC_DI[ChIn].CntrSetpoint;
				break;

			case PLC_DI_Q_ID_CNTR_SETPOINT_ALLOW:
				QueueData.ID  = IDIn;
				QueueData.Val = (uint32_t)PLC_DI[ChIn].Pack.CntrSetpointAllow;
				break;

			case PLC_DI_Q_ID_CNTR_SETPOINT_REACHED:
				QueueData.ID  = IDIn;
				QueueData.Val = (uint32_t)PLC_DI[ChIn].Pack.CntrSetpointReached;
				break;

			case PLC_DI_Q_ID_TACH_VAL:
				QueueData.ID  = IDIn;
				QueueData.Val = (uint32_t)PLC_DI[ChIn].TachVal;
				break;

			case PLC_DI_Q_ID_TACH_SETPOINT:
				QueueData.ID  = IDIn;
				QueueData.Val = (uint32_t)PLC_DI[ChIn].TachSetpoint;
				break;

			case PLC_DI_Q_ID_TACH_SETPOINT_ALLOW:
				QueueData.ID  = IDIn;
				QueueData.Val = (uint32_t)PLC_DI[ChIn].Pack.TachSetpointAllow;
				break;

			case PLC_DI_Q_ID_TACH_SETPOINT_REACHED:
				QueueData.ID  = IDIn;
				QueueData.Val = (uint32_t)PLC_DI[ChIn].Pack.TachSetpointReached;
				break;

			case PLC_DI_Q_ID_RESET:
				QueueData.ID  = IDIn;
				QueueData.Val = (uint32_t)PLC_DI[ChIn].Pack.Reset;
				break;

			case PLC_DI_Q_ID_STATUS:
				QueueData.ID  = IDIn;
				QueueData.Val = (uint32_t)PLC_DI[ChIn].Status;
				break;

			case PLC_DI_Q_ID_FILTER_DELAY:
				QueueData.ID  = IDIn;
				QueueData.Val = PLC_DI_FLTR[ChIn].FltrDelay;
				break;
		}

		if(QueueData.ID != PLC_DI_Q_ID_NONE)
		{
			//Send data into RTOS_DI_DATA_Q (not-blocking)
			xQueueSendToBack(RTOS_DI_DATA_Q, &QueueData, 0);
			return (BIT_TRUE);
		}
	}
	return (BIT_FALSE);
}


/** @brief  Start DI_TACH_TIM.
 *  @param  FromIsrIn:
 *  @arg    = 0 - normal API
 *  @arg    = 1 - FromISR API
 *  @return None.
 */
static void RTOS_DI_TACH_TIM_Start(uint8_t FromIsrIn)
{
	if(!PLC_DI_TACH_TIM_STATUS)
	{
		if(!FromIsrIn)
		{
			xTimerReset(RTOS_DI_TACH_TIM, 0);
		}
		else
		{
			xTimerResetFromISR(RTOS_DI_TACH_TIM, 0);
		}

		PLC_DI_TACH_TIM_STATUS = BIT_TRUE;
    }
}

/** @brief  Stop DI_TACH_TIM.
 *  @param  None.
 *  @return None.
 */
static void RTOS_DI_TACH_TIM_Stop(void)
{
	if(PLC_DI_TACH_TIM_STATUS)
	{
		xTimerStop(RTOS_DI_TACH_TIM, 0);
		PLC_DI_TACH_TIM_STATUS = BIT_FALSE;
    }
}


/** @brief  Start DI_FLTR_TIM.
 *  @param  FromIsrIn:
 *  @arg    = 0 - normal API
 *  @arg    = 1 - FromISR API
 *  @return None.
 */
static void RTOS_DI_FLTR_TIM_Start(uint8_t FromIsrIn)
{
	if(!PLC_DI_FLTR_TIM_STATUS)
	{
		if(!FromIsrIn)
		{
			xTimerReset(RTOS_DI_FLTR_TIM, 0);
		}
		else
		{
			xTimerResetFromISR(RTOS_DI_FLTR_TIM, 0);
		}

		PLC_DI_FLTR_TIM_STATUS = BIT_TRUE;
    }
}

/** @brief  Stop DI_FLTR_TIM.
 *  @param  None.
 *  @return None.
 */
static void RTOS_DI_FLTR_TIM_Stop(void)
{
	if(PLC_DI_FLTR_TIM_STATUS)
	{
		xTimerStop(RTOS_DI_FLTR_TIM, 0);
		PLC_DI_FLTR_TIM_STATUS = BIT_FALSE;
    }
}


/** @brief  Set Normal value.
 *  @param  ChIn  - channel number.
 *  @param  ValIn - channel value.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_DI_SetNorm(uint8_t ChIn, uint8_t ValIn)
{
#ifdef DEBUG_LOG_DI_IRQ_Q
	DebugLog("RTOS_DI_SetNorm\n");
#endif // DEBUG_LOG_DI_IRQ_Q

    if(ChIn < PLC_DI_SZ)
    {
        if(ValIn != PLC_DI[ChIn].NormVal)
        {
            PLC_DI[ChIn].NormVal = ValIn;

#ifdef DEBUG_LOG_DI_IRQ_Q
            DebugLog("DI[%d].NormVal=%d\n", ChIn, PLC_DI[ChIn].NormVal);
#endif // DEBUG_LOG_DI_IRQ_Q

            RTOS_DI_DATA_Q_Send(ChIn, PLC_DI_Q_ID_NORM_VAL);
            return (BIT_TRUE);
        }
    }
    return (BIT_FALSE);
}


/** @brief  Test Counter setpoint.
 *  @param  ChmIn - channel number.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_DI_TestCntrSetpoint(uint8_t ChIn)
{
    if(ChIn< PLC_DI_SZ)
    {
        PLC_DI[ChIn].Pack.CntrSetpointReached = BIT_FALSE;

        if(PLC_DI[ChIn].Pack.CntrSetpointAllow)
        {
            if(PLC_DI[ChIn].CntrVal >= PLC_DI[ChIn].CntrSetpoint)
            {
                PLC_DI[ChIn].Pack.CntrSetpointReached = BIT_TRUE;
            }
        }
        return (BIT_TRUE);
    }
    return (BIT_FALSE);
}

/** @brief  Reset Counter.
 *  @param  ChIn  - channel number.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_DI_ResetCntr(uint8_t ChIn)
{
#ifdef DEBUG_LOG_DI
	DebugLog("RTOS_DI_ResetCntr\n");
#endif // DEBUG_LOG_DI

    if(ChIn < PLC_DI_SZ)
    {
    	PLC_DI[ChIn].CntrVal = 0;
    	RTOS_DI_TestCntrSetpoint(ChIn);

#ifdef DEBUG_LOG_DI
		DebugLog("DI[%d].CntrVal=%d .Sp=%d .SpA=%d .SpR=%d\n", ChIn, PLC_DI[ChIn].CntrVal, PLC_DI[ChIn].CntrSetpoint, PLC_DI[ChIn].Pack.CntrSetpointAllow, PLC_DI[ChIn].Pack.CntrSetpointReached);
#endif // DEBUG_LOG_DI

        RTOS_DI_DATA_Q_Send(ChIn, PLC_DI_Q_ID_CNTR_VAL);
        RTOS_DI_DATA_Q_Send(ChIn, PLC_DI_Q_ID_CNTR_SETPOINT_REACHED);
        return (BIT_TRUE);
    }
    return (BIT_FALSE);
}

/** @brief  Set Counter.
 *  @param  ChIn  - channel number.
 *  @param  ValIn - channel value.
 *  @param  ValPrevIn - channel previous value.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_DI_SetCntr(uint8_t ChIn, uint8_t ValIn, uint8_t ValPrevIn)
{
#ifdef DEBUG_LOG_DI_IRQ_Q
	DebugLog("RTOS_DI_SetCntr\n");
#endif // DEBUG_LOG_DI_IRQ_Q

    if(ChIn < PLC_DI_SZ)
    {
        //by Front
        if(ValIn && !ValPrevIn)
        {
            PLC_DI[ChIn].CntrVal++;
            RTOS_DI_TestCntrSetpoint(ChIn);

#ifdef DEBUG_LOG_DI_IRQ_Q
            DebugLog("DI[%d].CntrVal=%d .Sp=%d .SpA=%d .SpR=%d\n", ChIn, PLC_DI[ChIn].CntrVal, PLC_DI[ChIn].CntrSetpoint, PLC_DI[ChIn].Pack.CntrSetpointAllow, PLC_DI[ChIn].Pack.CntrSetpointReached);
#endif // DEBUG_LOG_DI_IRQ_Q

            RTOS_DI_DATA_Q_Send(ChIn, PLC_DI_Q_ID_CNTR_VAL);
            RTOS_DI_DATA_Q_Send(ChIn, PLC_DI_Q_ID_CNTR_SETPOINT_REACHED);
            return (BIT_TRUE);
        }
    }
    return (BIT_FALSE);
}


/** @brief  Test Tachometer setpoint.
 *  @param  ChmIn - channel number.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_DI_TestTachSetpoint(uint8_t ChIn)
{
    if(ChIn< PLC_DI_SZ)
    {
        PLC_DI[ChIn].Pack.TachSetpointReached = BIT_FALSE;

        if(PLC_DI[ChIn].Pack.TachSetpointAllow)
        {
            if(PLC_DI[ChIn].TachVal >= PLC_DI[ChIn].TachSetpoint)
            {
                PLC_DI[ChIn].Pack.TachSetpointReached = BIT_TRUE;
            }
        }
        return (BIT_TRUE);
    }
    return (BIT_FALSE);
}

/** @brief  Reset Tachometer Counter.
 *  @param  ChIn  - channel number.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_DI_ResetTachCntr(uint8_t ChIn)
{
#ifdef DEBUG_LOG_DI_IRQ_Q
	DebugLog("RTOS_DI_ResetTachCntr\n");
#endif // DEBUG_LOG_DI_IRQ_Q

    if(ChIn < PLC_DI_SZ)
    {
    	PLC_DI[ChIn].TachVal     = 0;
    	PLC_DI[ChIn].TachCntrVal = 0;
    	RTOS_DI_TestTachSetpoint(ChIn);

#ifdef DEBUG_LOG_DI_IRQ_Q
    	DebugLog("DI[%d].TachVal=%d .Sp=%d .SpA=%d .SpR=%d .Tach.CntrVal=%d\n", ChIn, PLC_DI[ChIn].TachVal, PLC_DI[ChIn].TachSetpoint, PLC_DI[ChIn].Pack.TachSetpointAllow, PLC_DI[ChIn].Pack.TachSetpointReached, PLC_DI[ChIn].TachCntrVal);
#endif // DEBUG_LOG_DI_IRQ_Q

        RTOS_DI_DATA_Q_Send(ChIn, PLC_DI_Q_ID_TACH_VAL);
        RTOS_DI_DATA_Q_Send(ChIn, PLC_DI_Q_ID_TACH_SETPOINT_REACHED);
        return (BIT_TRUE);
    }
    return (BIT_FALSE);
}

/** @brief  Set Tachometer Counter.
 *  @param  ChIn      - channel number.
 *  @param  ValIn     - channel value.
 *  @param  ValPrevIn - channel previous value.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_DI_SetTachCntr(uint8_t ChIn, uint8_t ValIn, uint8_t ValPrevIn)
{
#ifdef DEBUG_LOG_DI_IRQ_Q
	DebugLog("RTOS_DI_SetTachCntr\n");
#endif // DEBUG_LOG_DI_IRQ_Q

    if(ChIn < PLC_DI_SZ)
    {
        //by Front
        if(ValIn && !ValPrevIn)
        {
            PLC_DI[ChIn].TachCntrVal++;
            RTOS_DI_TestTachSetpoint(ChIn);

#ifdef DEBUG_LOG_DI_IRQ_Q
            DebugLog("DI[%d].TachVal=%d .Sp=%d .SpA=%d .SpR=%d .Tach.CntrVal=%d\n", ChIn, PLC_DI[ChIn].TachVal, PLC_DI[ChIn].TachSetpoint, PLC_DI[ChIn].Pack.TachSetpointAllow, PLC_DI[ChIn].Pack.TachSetpointReached, PLC_DI[ChIn].TachCntrVal);
#endif // DEBUG_LOG_DI_IRQ_Q

            RTOS_DI_DATA_Q_Send(ChIn, PLC_DI_Q_ID_TACH_VAL);
            RTOS_DI_DATA_Q_Send(ChIn, PLC_DI_Q_ID_TACH_SETPOINT_REACHED);
            return (BIT_TRUE);
        }
    }
    return (BIT_FALSE);
}

/** @brief  Set Incremental encoder (Channel Counter).
 *  @param  ChIn  - channel number.
 *  @param  ValIn - channel value.
 *  @param  ValPrevIn - channel previous value.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_DI_SetInc1(uint8_t ChIn, uint8_t ValIn, uint8_t ValPrevIn)
{
#ifdef DEBUG_LOG_DI_IRQ_Q
	DebugLog("RTOS_DI_SetInc1\n");
#endif // DEBUG_LOG_DI_IRQ_Q

    if(ChIn < PLC_DI_SZ)
    {
    	uint8_t ChPair = PLC_DI[ChIn].ChPair;

    	//test value of pair channel
        if(!PLC_DI[ChPair].NormVal)
        {
        	return (RTOS_DI_SetCntr(ChIn, ValIn, ValPrevIn));
        }
    }
    return (BIT_FALSE);
}

/** @brief  Set Incremental encoder (Channel Counter + Tachometer).
 *  @param  ChIn  - channel number.
 *  @param  ValIn - channel value.
 *  @param  ValPrevIn - channel previous value.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_DI_SetInc2(uint8_t ChIn, uint8_t ValIn, uint8_t ValPrevIn)
{
#ifdef DEBUG_LOG_DI_IRQ_Q
	DebugLog("RTOS_DI_SetInc2\n");
#endif // DEBUG_LOG_DI_IRQ_Q

	//used tachometer counter value of phase B to store tachometer counts of phase A
    uint8_t TachChNum = ((PLC_DI_IS_PHASE_A(ChIn)) ? PLC_DI[ChIn].ChPair : ChIn);
    RTOS_DI_SetTachCntr(TachChNum, ValIn, ValPrevIn);
    return (RTOS_DI_SetInc1(ChIn, ValIn, ValPrevIn));
}

/** @brief  Set values.
 *  @param  DataIn - pointer to data.
 *  @return None.
 */
static void RTOS_DI_IRQ_Set(PlcDI_IRQ_Q_t DataIn)
{
#ifdef DEBUG_LOG_DI_IRQ_Q
	DebugLog("RTOS_DI_IRQ_Set\n");
	DebugLog("Ch=%d .Val=%d\n", DataIn.Ch, DataIn.Val);
#endif //DEBUG_LOG_DI_IRQ_Q

	if(DataIn.Ch < PLC_DI_SZ)
	{
		switch(PLC_DI[DataIn.Ch].Mode)
		{
			//counter
			case PLC_DI_MODE_CNTR:
				RTOS_DI_SetCntr(DataIn.Ch, DataIn.Val, PLC_DI[DataIn.Ch].NormVal);
				break;

			//tachometer
			case PLC_DI_MODE_TACH:
				RTOS_DI_SetTachCntr(DataIn.Ch, DataIn.Val, PLC_DI[DataIn.Ch].NormVal);
				break;

			//incremental encoder (counter)
			case PLC_DI_MODE_INC1:
				RTOS_DI_SetInc1(DataIn.Ch, DataIn.Val, PLC_DI[DataIn.Ch].NormVal);
				break;

			//incremental encoder (counter + tachometer)
			case PLC_DI_MODE_INC2:
				RTOS_DI_SetInc2(DataIn.Ch, DataIn.Val, PLC_DI[DataIn.Ch].NormVal);
				break;
		}

		if(PLC_DI[DataIn.Ch].Mode == PLC_DI_MODE_NORM || PLC_DI[DataIn.Ch].Mode == PLC_DI_MODE_CNTR || PLC_DI[DataIn.Ch].Mode == PLC_DI_MODE_TACH || PLC_DI[DataIn.Ch].Mode == PLC_DI_MODE_INC1 || PLC_DI[DataIn.Ch].Mode == PLC_DI_MODE_INC2)
		{
			//update nomal value
			RTOS_DI_SetNorm(DataIn.Ch, DataIn.Val);
		}
    }
}

/** @brief  Task DI_IRQ_T (blocked)
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return None.
 */
void RTOS_DI_IRQ_Task(void *ParamsIn)
{
	//variables
	PlcDI_IRQ_Q_t QueueData;
    BaseType_t    QueueStatus;

    (void)ParamsIn; //fix unused

    //start
    for(;;)
    {
    	//Read RTOS_DI_IRQ_Q (blocking)
		QueueStatus = xQueueReceive(RTOS_DI_IRQ_Q, &QueueData, portMAX_DELAY);
		if(QueueStatus == pdPASS)
		{
			RTOS_DI_IRQ_Set(QueueData);
		}

        //fast switch to other task
        taskYIELD();
    }
}


/** @brief  Reset counters.
 *  @param  ChIn  - channel number.
 *  @return Result:
 *  @arg    = 0 - not reset
 *  @arg    = 1 - reset
 */
static uint8_t RTOS_DI_Reset(uint8_t ChIn)
{
#ifdef DEBUG_LOG_DI_Q
	DebugLog("RTOS_DI_Reset\n");
#endif // DEBUG_LOG_DI_Q

	if(ChIn < PLC_DI_SZ)
	{
        RTOS_DI_ResetCntr(ChIn);
        RTOS_DI_ResetTachCntr(ChIn);

        if(PLC_DI[ChIn].Mode >= PLC_DI_MODE_INC1)
        {
            //reset channel of pair phase B
        	RTOS_DI_ResetCntr(PLC_DI[ChIn].ChPair);
        	RTOS_DI_ResetTachCntr(PLC_DI[ChIn].ChPair);
        }
	}
	return (BIT_FALSE);
}

/** @brief  Test pair dependent.
 *  @param  ChIn - channel number.
 *  @return Result:
 *  @arg    = 0 - the channel is not dependent
 *  @arg    = 1 - the channel is dependent
 */
static uint8_t RTOS_DI_TestPair(uint8_t ChIn)
{
    if(PLC_DI_IS_PHASE_B(ChIn))
    {
        //the channel is phase B of pair (slave)
        //test mode of phase A (main)
        if(PLC_DI[ChIn-1].Mode >= PLC_DI_MODE_INC1) return (BIT_TRUE);
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
static uint8_t RTOS_DI_SetMode(uint8_t ChIn, uint8_t ModeIn)
{
#ifdef DEBUG_LOG_DI_Q
	DebugLog("RTOS_DI_SetMode\n");
#endif // DEBUG_LOG_DI_Q

	uint8_t ChPair;

	if(ChIn < PLC_DI_SZ)
	{
        if(PLC_DI[ChIn].Mode != ModeIn)
        {
        	ChPair = PLC_DI[ChIn].ChPair;

            switch(ModeIn)
            {
            	case PLC_DI_MODE_OFF:
                case PLC_DI_MODE_NORM:
                case PLC_DI_MODE_CNTR:
                case PLC_DI_MODE_TACH:
                    //for channels of pair phase A
                    //or channels of pair phase B are not dependent by phase A
                    if(!RTOS_DI_TestPair(ChIn))
                    {
                        if(PLC_DI_IS_PHASE_A(ChIn) && PLC_DI[ChIn].Mode >= PLC_DI_MODE_INC1)
                        {
                            //phase B: turn Off
                            PLC_DI[ChPair].Mode    = PLC_DI_MODE_OFF;
                            PLC_DI[ChPair].Status  = PLC_DI[ChPair].Mode;
                            PLC_DI[ChPair].NormVal = BIT_FALSE;
                            RTOS_DI_Reset(ChPair);
                        }
                        //phase A
                        PLC_DI[ChIn].Mode    = ModeIn;
                        PLC_DI[ChIn].Status  = PLC_DI[ChIn].Mode;
                        PLC_DI[ChIn].NormVal = ((ModeIn != PLC_DI_MODE_OFF) ? PlcDI_ReadNormVal(ChIn) : BIT_FALSE);
                        RTOS_DI_Reset(ChIn);

                        if(ModeIn == PLC_DI_MODE_TACH) RTOS_DI_TACH_TIM_Start(BIT_FALSE);
                    }
                    break;

                case PLC_DI_MODE_INC1:
                case PLC_DI_MODE_INC2:
                    //only for channels of pair phase A
                    if(PLC_DI_IS_PHASE_A(ChIn))
                    {
                        //phase A
                        PLC_DI[ChIn].Mode      = ModeIn;
                        PLC_DI[ChIn].Status    = PLC_DI[ChIn].Mode;
                        PLC_DI[ChIn].NormVal   = PlcDI_ReadNormVal(ChIn);
                        RTOS_DI_Reset(ChIn);
                        //phase B
                        PLC_DI[ChPair].Mode    = ModeIn;
                        PLC_DI[ChPair].Status  = PLC_DI[ChPair].Mode;
                        PLC_DI[ChPair].NormVal = PlcDI_ReadNormVal(ChPair);
                        RTOS_DI_Reset(ChPair);

                        if(ModeIn == PLC_DI_MODE_INC2) RTOS_DI_TACH_TIM_Start(BIT_FALSE);
                    }
                    break;
            }

#ifdef DEBUG_LOG_DI_Q
           	DebugLog("DI[%d].Mode=%d .Stat=%d .NormVal=%d\nDI[%d].Mode=%d .Stat=%d .NormVal=%d\n", ChIn, PLC_DI[ChIn].Mode, PLC_DI[ChIn].Status, PLC_DI[ChIn].NormVal, ChPair, PLC_DI[ChPair].Mode, PLC_DI[ChPair].Status, PLC_DI[ChPair].NormVal);
#endif // DEBUG_LOG_DI_Q

           	RTOS_DI_DATA_Q_Send(ChIn, PLC_DI_Q_ID_MODE);
           	RTOS_DI_DATA_Q_Send(ChIn, PLC_DI_Q_ID_STATUS);
			RTOS_DI_DATA_Q_Send(ChIn, PLC_DI_Q_ID_NORM_VAL);

           	RTOS_DI_DATA_Q_Send(ChPair, PLC_DI_Q_ID_MODE);
           	RTOS_DI_DATA_Q_Send(ChPair, PLC_DI_Q_ID_STATUS);
           	RTOS_DI_DATA_Q_Send(ChPair, PLC_DI_Q_ID_NORM_VAL);

           	return (BIT_TRUE);
        }
	}
	return (BIT_FALSE);
}

/** @brief  Set Counter setpoint value.
 *  @param  ChIn  - channel number.
 *  @param  ValIn - setpoint value.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_DI_SetCntrSetpoint(uint8_t ChIn, uint32_t ValIn)
{
#ifdef DEBUG_LOG_DI_Q
	DebugLog("RTOS_DI_SetCntrSetpoint\n");
#endif // DEBUG_LOG_DI_Q

	if(ChIn < PLC_DI_SZ)
	{
		if(PLC_DI[ChIn].CntrSetpoint != ValIn)
		{
			PLC_DI[ChIn].CntrSetpoint = ValIn;
			RTOS_DI_TestCntrSetpoint(ChIn);

			RTOS_DI_DATA_Q_Send(ChIn, PLC_DI_Q_ID_CNTR_SETPOINT);
			RTOS_DI_DATA_Q_Send(ChIn, PLC_DI_Q_ID_CNTR_SETPOINT_REACHED);

#ifdef DEBUG_LOG_DI_Q
            DebugLog("DI[%d].Sp=%d .SpA=%d\n", ChIn, PLC_DI[ChIn].CntrSetpoint, PLC_DI[ChIn].Pack.CntrSetpointAllow);
#endif // DEBUG_LOG_DI_Q
            return (BIT_TRUE);
		}
	}
	return (BIT_FALSE);
}

/** @brief  Set Counter setpoint allow.
 *  @param  ChIn  - channel number.
 *  @param  ValIn - setpoint allow.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_DI_SetCntrSetpointAllow(uint8_t ChIn, uint8_t ValIn)
{
#ifdef DEBUG_LOG_DI_Q
	DebugLog("RTOS_DI_SetCntrSetpointAllow\n");
#endif // DEBUG_LOG_DI_Q

	if(ChIn < PLC_DI_SZ)
	{
		if(PLC_DI[ChIn].Pack.CntrSetpointAllow != ValIn)
		{
			PLC_DI[ChIn].Pack.CntrSetpointAllow = ValIn;
			RTOS_DI_TestCntrSetpoint(ChIn);

			RTOS_DI_DATA_Q_Send(ChIn, PLC_DI_Q_ID_CNTR_SETPOINT_ALLOW);
			RTOS_DI_DATA_Q_Send(ChIn, PLC_DI_Q_ID_CNTR_SETPOINT_REACHED);

#ifdef DEBUG_LOG_DI_Q
            DebugLog("DI[%d].Sp=%d .SpA=%d\n", ChIn, PLC_DI[ChIn].CntrSetpoint, PLC_DI[ChIn].Pack.CntrSetpointAllow);
#endif // DEBUG_LOG_DI_Q
            return (BIT_TRUE);
		}
	}
	return (BIT_FALSE);
}

/** @brief  Set Tachometer setpoint value.
 *  @param  ChIn  - channel number.
 *  @param  ValIn - setpoint value.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_DI_SetTachSetpoint(uint8_t ChIn, uint16_t ValIn)
{
#ifdef DEBUG_LOG_DI_Q
	DebugLog("RTOS_DI_SetTachSetpoint\n");
#endif // DEBUG_LOG_DI_Q

	if(ChIn < PLC_DI_SZ)
	{
		if(PLC_DI[ChIn].TachSetpoint != ValIn)
		{
			PLC_DI[ChIn].TachSetpoint = ValIn;
			RTOS_DI_TestTachSetpoint(ChIn);

			RTOS_DI_DATA_Q_Send(ChIn, PLC_DI_Q_ID_TACH_SETPOINT);
			RTOS_DI_DATA_Q_Send(ChIn, PLC_DI_Q_ID_TACH_SETPOINT_REACHED);

#ifdef DEBUG_LOG_DI_Q
            DebugLog("DI[%d].Sp=%d .SpA=%d\n", ChIn, PLC_DI[ChIn].TachSetpoint, PLC_DI[ChIn].Pack.TachSetpointAllow);
#endif // DEBUG_LOG_DI_Q
            return (BIT_TRUE);
		}
	}
	return (BIT_FALSE);
}

/** @brief  Set Tachometer setpoint allow.
 *  @param  ChIn  - channel number.
 *  @param  ValIn - setpoint allow.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_DI_SetTachSetpointAllow(uint8_t ChIn, uint8_t ValIn)
{
#ifdef DEBUG_LOG_DI_Q
	DebugLog("RTOS_DI_SetTachSetpointAllow\n");
#endif // DEBUG_LOG_DI_Q

	if(ChIn < PLC_DI_SZ)
	{
		if(PLC_DI[ChIn].Pack.TachSetpointAllow != ValIn)
		{
			PLC_DI[ChIn].Pack.TachSetpointAllow = ValIn;
			RTOS_DI_TestTachSetpoint(ChIn);

			RTOS_DI_DATA_Q_Send(ChIn, PLC_DI_Q_ID_TACH_SETPOINT_ALLOW);
			RTOS_DI_DATA_Q_Send(ChIn, PLC_DI_Q_ID_TACH_SETPOINT_REACHED);

#ifdef DEBUG_LOG_DI_Q
            DebugLog("DI[%d].Sp=%d .SpA=%d\n", ChIn, PLC_DI[ChIn].TachSetpoint, PLC_DI[ChIn].Pack.TachSetpointAllow);
#endif // DEBUG_LOG_DI_Q
            return (BIT_TRUE);
		}
	}
	return (BIT_FALSE);
}

/** @brief  Set Reset.
 *  @param  ChIn  - channel number.
 *  @param  ValIn - reset command.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_DI_SetReset(uint8_t ChIn, uint8_t ValIn)
{
#ifdef DEBUG_LOG_DI_Q
	DebugLog("RTOS_DI_SetReset\n");
#endif // DEBUG_LOG_DI_Q

	if(ChIn < PLC_DI_SZ)
	{
		if(PLC_DI[ChIn].Pack.Reset != ValIn)
		{
	        //command from not encoder channels
	        //or from encoder channels of pair phase A
	        if(PLC_DI[ChIn].Mode < PLC_DI_MODE_INC1 || (PLC_DI[ChIn].Mode >= PLC_DI_MODE_INC1 && PLC_DI_IS_PHASE_A(ChIn)))
	        {
	            PLC_DI[ChIn].Pack.Reset = ((ValIn) ? BIT_TRUE : BIT_FALSE);
	            if(PLC_DI[ChIn].Pack.Reset) RTOS_DI_Reset(ChIn);
	            return (BIT_TRUE);
	        }
		}
	}
	return (BIT_FALSE);
}

/** @brief  Set filter delay.
 *  @param  ChIn  - channel number.
 *  @param  ValIn - filter delay.
 *  @return Result:
 *  @arg    = 0 - not set
 *  @arg    = 1 - set
 */
static uint8_t RTOS_DI_SetFilterDelay(uint8_t ChIn, uint32_t ValIn)
{
#ifdef DEBUG_LOG_DI_Q
	DebugLog("RTOS_DI_SetFilterDelay\n");
#endif // DEBUG_LOG_DI_Q

	if(ChIn < PLC_DI_SZ)
	{
		if(PLC_DI_FLTR[ChIn].FltrDelay != ValIn)
		{
			PLC_DI_FLTR[ChIn].FltrDelay = ValIn;
			RTOS_DI_DATA_Q_Send(ChIn, PLC_DI_Q_ID_FILTER_DELAY);

#ifdef DEBUG_LOG_DI_Q
            DebugLog("DI[%d].FltrDelay=%d\n", ChIn, PLC_DI_FLTR[ChIn].FltrDelay);
#endif // DEBUG_LOG_DI_Q
            return (BIT_TRUE);
		}
	}
	return (BIT_FALSE);
}

/** @brief  Set settings.
 *  @param  DataIn - pointer to data.
 *  @return None.
 */
static void RTOS_DI_Set(const PlcDI_Q_t *DataIn)
{
    if(DataIn)
    {
        switch(DataIn->ID)
        {
            case PLC_DI_Q_ID_MODE:
            	RTOS_DI_SetMode(DataIn->Ch, (uint8_t)DataIn->Val);
                break;

            case PLC_DI_Q_ID_CNTR_SETPOINT:
            	RTOS_DI_SetCntrSetpoint(DataIn->Ch, DataIn->Val);
            	break;

            case PLC_DI_Q_ID_CNTR_SETPOINT_ALLOW:
            	RTOS_DI_SetCntrSetpointAllow(DataIn->Ch, (uint8_t)DataIn->Val);
            	break;

            case PLC_DI_Q_ID_TACH_SETPOINT:
            	RTOS_DI_SetTachSetpoint(DataIn->Ch, (uint16_t)DataIn->Val);
            	break;

            case PLC_DI_Q_ID_TACH_SETPOINT_ALLOW:
            	RTOS_DI_SetTachSetpointAllow(DataIn->Ch, (uint8_t)DataIn->Val);
            	break;

            case PLC_DI_Q_ID_RESET:
            	RTOS_DI_SetReset(DataIn->Ch, (uint8_t)DataIn->Val);
            	break;

            case PLC_DI_Q_ID_FILTER_DELAY:
            	RTOS_DI_SetFilterDelay(DataIn->Ch, DataIn->Val);
            	break;
        }
    }
}


/** @brief  Callback for DI.IRQ.Exti
 *  @param  DataIn - channel number.
 *  @return None.
 */
static void PlcDI_Exti(PlcDI_IRQ_Q_t DataIn)
{
    portBASE_TYPE HiTaskWoken = pdFALSE;

	if(DataIn.Ch < PLC_DI_SZ)
	{
		if(PLC_DI_FLTR[DataIn.Ch].FltrDelay)
		{
			//with filter
			if(PLC_DI_FLTR[DataIn.Ch].FltrVal != DataIn.Val)
			{
				PLC_DI_FLTR[DataIn.Ch].FltrTs    = HAL_GetTick();
				PLC_DI_FLTR[DataIn.Ch].FltrTs   += PLC_DI_FLTR[DataIn.Ch].FltrDelay;
				PLC_DI_FLTR[DataIn.Ch].FltrVal   = DataIn.Val;
				PLC_DI_FLTR[DataIn.Ch].Fltr      = BIT_TRUE;
				RTOS_DI_FLTR_TIM_Start(BIT_TRUE);
			}
		}
		else
		{
		    //Send IRQ-data to RTOS_DI_IRQ_Q (not-blocking)
			//without filter
		    xQueueSendToBackFromISR(RTOS_DI_IRQ_Q, &DataIn, &HiTaskWoken);
		}
	}
}


/** @brief  Init DI_T
 *  @param  None.
 *  @return None.
 */
static void RTOS_DI_Init(void)
{
#ifdef DEBUG_LOG_MAIN
    DebugLog("RTOS_DI_Init\n");
#endif // DEBUG_LOG_MAIN

    uint8_t  cTachSurv = 0;
	uint8_t  BuffBy;
	uint16_t BuffWo;
	uint32_t BuffDWo;

	for(uint8_t i=0; i<PLC_DI_SZ; i++)
	{
		PLC_DI[i].Ch     = i;
		PLC_DI[i].ChPair = ((PLC_DI_IS_PHASE_A(i)) ? (i+1) : (i-1));

		BuffBy = PLC_DI_MODE_DEF;
		REG_CopyRegByPos(REG_DI_MODE__POS+i, REG_COPY_MB_TO_VAR, &BuffBy);
		PLC_DI[i].Mode = BuffBy;

		BuffBy = PLC_DI_CNTR_SETPOINT_ALLOW_DEF;
		REG_CopyRegByPos(REG_DI_CNTR_SETPOINT_ALLOW__POS+i, REG_COPY_MB_TO_VAR, &BuffBy);
		PLC_DI[i].Pack.CntrSetpointAllow   = BuffBy;
		PLC_DI[i].Pack.CntrSetpointReached = BIT_FALSE;

		BuffBy = PLC_DI_TACH_SETPOINT_ALLOW_DEF;
		REG_CopyRegByPos(REG_DI_TACH_SETPOINT_ALLOW__POS+i, REG_COPY_MB_TO_VAR, &BuffBy);
		PLC_DI[i].Pack.TachSetpointAllow   = BuffBy;
		PLC_DI[i].Pack.TachSetpointReached = BIT_FALSE;

		PLC_DI[i].Pack.Reset = BIT_FALSE;

		BuffDWo = PLC_DI_CNTR_SETPOINT_DEF;
		REG_CopyRegByPos(REG_DI_CNTR_SETPOINT__POS+i, REG_COPY_MB_TO_VAR, &BuffDWo);
		PLC_DI[i].CntrSetpoint = BuffDWo;

		BuffWo = PLC_DI_TACH_SETPOINT_DEF;
		REG_CopyRegByPos(REG_DI_TACH_SETPOINT__POS+i, REG_COPY_MB_TO_VAR, &BuffWo);
		PLC_DI[i].TachSetpoint = BuffWo;

		PLC_DI[i].NormVal     = BIT_FALSE;
		PLC_DI[i].CntrVal     = 0;
		PLC_DI[i].TachVal     = 0;
		PLC_DI[i].TachCntrVal = 0;
		PLC_DI[i].Status      = PLC_DI[i].Mode;

		BuffDWo = PLC_DI_FLTR_DELAY_DEF;
		REG_CopyRegByPos(REG_DI_FILTER_DELAY__POS+i, REG_COPY_MB_TO_VAR, &BuffDWo);
		PLC_DI_FLTR[i].FltrDelay = BuffDWo;
		PLC_DI_FLTR[i].Fltr      = BIT_FALSE;
		PLC_DI_FLTR[i].FltrTs    = HAL_GetTick();
		PLC_DI_FLTR[i].FltrVal   = BIT_FALSE;

		if(PLC_DI[i].Mode == PLC_DI_MODE_TACH || (PLC_DI[i].Mode == PLC_DI_MODE_INC2 && PLC_DI_IS_PHASE_B(i)))
		{
			cTachSurv++;
		}

#ifdef DEBUG_LOG_DI
        DebugLog("DI[%d].ChPair=%d .Mode=%d .Stat=%d\n", PLC_DI[i].Ch, PLC_DI[i].ChPair, PLC_DI[i].Mode, PLC_DI[i].Status);
#endif // DEBUG_LOG_DI
	}

	PLC_DI00_USER_FUNC.Exti = PlcDI_Exti;
	PLC_DI01_USER_FUNC.Exti = PlcDI_Exti;

	PlcDI_Init();
	if(cTachSurv) RTOS_DI_TACH_TIM_Start(BIT_FALSE);
}

/** @brief  DeInit DI_T
 *  @param  None.
 *  @return None.
 */
static void RTOS_DI_DeInit(void)
{
#ifdef DEBUG_LOG_MAIN
    DebugLog("RTOS_DI_DeInit\n");
#endif // DEBUG_LOG_MAIN

	PlcDI_DeInit();
}


/** @brief  Task DI_T (blocked)
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return None.
 */
void RTOS_DI_Task(void *ParamsIn)
{
	//variables
	PlcDI_Q_t  QueueData;
    BaseType_t QueueStatus;

    (void)ParamsIn; //fix unused

    RTOS_DI_Init();

    //start
    for(;;)
    {
    	//Read RTOS_DI_Q (blocking)
		QueueStatus = xQueueReceive(RTOS_DI_Q, &QueueData, portMAX_DELAY);
		if(QueueStatus == pdPASS)
		{
			RTOS_DI_Set(&QueueData);
		}

        //fast switch to other task
        taskYIELD();
    }

    RTOS_DI_DeInit();
}


/** @brief  DI_TACH_TIM Handler (auto-reloaded with controlled launch)
 *  @param  TimerIn - timer.
 *  @return None.
 */
void RTOS_DI_TACH_TIM_Handler(TimerHandle_t TimerIn)
{
#ifdef DEBUG_LOG_DI_TACH_TIM
	DebugLog("RTOS_DI_TACH_TimHandler\n");
#endif // DEBUG_LOG_DI_TACH_TIM

	uint8_t  cTachSurv = 0;
	uint16_t ValPrev;

	//fix unused
	(void)TimerIn;

	RTOS_DI_TACH_TIM_Stop();

	for(uint8_t i=0; i<PLC_DI_SZ; i++)
    {
        if(PLC_DI[i].Mode == PLC_DI_MODE_TACH || (PLC_DI[i].Mode == PLC_DI_MODE_INC2 && PLC_DI_IS_PHASE_B(i)))
        {
        	ValPrev = PLC_DI[i].TachVal;
        	PLC_DI[i].TachVal     = PLC_DI[i].TachCntrVal;
        	PLC_DI[i].TachCntrVal = 0;

        	RTOS_DI_TestTachSetpoint(i);
        	cTachSurv++;

        	if(PLC_DI[i].TachVal != ValPrev)
        	{
        		RTOS_DI_DATA_Q_Send(i, PLC_DI_Q_ID_TACH_VAL);
        	}
        }
    }

	//If no a DI-channel that configured to survey-mode, then will be automatically stop the DI_TACH_TIM
	if(cTachSurv) RTOS_DI_TACH_TIM_Start(BIT_FALSE);
}


/** @brief  DI_FLTR_TIM Handler (one-shot)
 *  @param  TimerIn - timer.
 *  @return None.
 */
void RTOS_DI_FLTR_TIM_Handler(TimerHandle_t TimerIn)
{
#ifdef DEBUG_LOG_DI_FLTR_TIM
	DebugLog("RTOS_DI_FLTR_TIM_Handler\n");
#endif // DEBUG_LOG_DI_FLTR_TIM

	PlcDI_IRQ_Q_t QueueData;
	uint8_t  cFltrSurv = 0;
	uint32_t CurrTs    = HAL_GetTick();

	//fix unused
	(void)TimerIn;

	RTOS_DI_FLTR_TIM_Stop();

	for(uint8_t i=0; i<PLC_DI_SZ; i++)
    {
        if(PLC_DI[i].Mode != PLC_DI_MODE_OFF && PLC_DI_FLTR[i].Fltr)
        {
        	if(PLC_DI_FLTR[i].FltrTs <= CurrTs)
        	{
        		QueueData.Ch  = PLC_DI[i].Ch;
        		QueueData.Val = PLC_DI_FLTR[i].FltrVal;
        		PLC_DI_FLTR[i].Fltr = BIT_FALSE;
    			//Send filtered normal value to RTOS_DI_IRQ_Q (not-blocking)
    			xQueueSendToBack(RTOS_DI_IRQ_Q, &QueueData, 0);
        	}
        	else
        	{
        		cFltrSurv++;
        	}
        }
    }

	//If no a DI-channel that configured to survey-mode, then will automatically stop the DI_FLTR_TIM
	if(cFltrSurv) RTOS_DI_FLTR_TIM_Start(BIT_FALSE);
}

#endif //RTE_MOD_DI
