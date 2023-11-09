/* @page reg.c
 *       PLC411::RTE
 *       Registers :: API (Common)
 *       2022, atgroup09@gmail.com
 */

#include "reg.h"


/** @var Registers
 */
static REG_t REGS[REG_SZ];

/** @var Data-table of registers (Boolean)
 */
static uint8_t REGS_DATA_BOOL[REG_DATA_BOOL_SZ];

/** @var Data-table of registers (Numbers)
 */
static uint16_t REGS_DATA_NUMB[REG_DATA_NUMB_SZ];


/** @brief  Get pointer to register by position in REGS.
 *  @param  IDxIn - position in REGS.
 *  @return Pointer to register or 0 if error.
 */
REG_t *REG_GetByIDx(uint16_t IDxIn)
{
    return ((IDxIn < REG_SZ) ? &REGS[IDxIn] : 0);
}

/** @brief  Get pointer to register by start position.
 *  @param  SPosIn   - start position of register group in REGS (ex.: REG_DI_NORM_VAL__POS).
 *  @param  iGroupIn - position of register in the group (>= 0) (iGroup).
 *  @return Pointer to register or 0 if error.
 */
REG_t *REG_GetByPos(uint16_t SPosIn, int32_t iGroupIn)
{
    if(iGroupIn > -1)
    {
        //calculate IDx (position in REGS)
        uint16_t IDx = SPosIn+((uint16_t)iGroupIn);
        return (REG_GetByIDx(IDx));
    }

    return (0);
}


#pragma GCC diagnostic ignored "-Wtype-limits"

/** @brief  Get pointer to register by ModBus address.
 *  @param  MbTableIn - ModBus Table ID (mbrtu.h).
 *  @param  MbAddrIn  - ModBus Register address.
 *  @return Pointer to register or 0 if error.
 */
REG_t *REG_GetByMbAddr(uint8_t MbTableIn, uint16_t MbAddrIn)
{
    //start position of group in REGS (__POS)
    uint16_t Pos = 0;
    //position of register in the group (>= 0) (iGroup)
    int32_t  iGroup  = -1;

    switch(MbTableIn)
    {
        case MBRTU_COIL_TABLE_ID:

            if(VAL_IN_LIMITS(REG_DI_TACH_SETPOINT_ALLOW__MBPOS, MbAddrIn, REG_DI_TACH_SETPOINT_ALLOW__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_DI_TACH_SETPOINT_ALLOW__MBPOS, REG_DI_TACH_SETPOINT_ALLOW__TYPE_WSZ);
                Pos    = REG_DI_TACH_SETPOINT_ALLOW__POS;
            }
            else if(VAL_IN_LIMITS(REG_DI_CNTR_SETPOINT_ALLOW__MBPOS, MbAddrIn, REG_DI_CNTR_SETPOINT_ALLOW__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_DI_CNTR_SETPOINT_ALLOW__MBPOS, REG_DI_CNTR_SETPOINT_ALLOW__TYPE_WSZ);
                Pos    = REG_DI_CNTR_SETPOINT_ALLOW__POS;
            }
            else if(VAL_IN_LIMITS(REG_DI_RESET__MBPOS, MbAddrIn, REG_DI_RESET__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_DI_RESET__MBPOS, REG_DI_RESET__TYPE_WSZ);
                Pos    = REG_DI_RESET__POS;
            }
            else if(VAL_IN_LIMITS(REG_DO_NORM_VAL__MBPOS, MbAddrIn, REG_DO_NORM_VAL__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_DO_NORM_VAL__MBPOS, REG_DO_NORM_VAL__TYPE_WSZ);
                Pos    = REG_DO_NORM_VAL__POS;
            }
            else if(VAL_IN_LIMITS(REG_DO_FAST_VAL__MBPOS, MbAddrIn, REG_DO_FAST_VAL__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_DO_FAST_VAL__MBPOS, REG_DO_FAST_VAL__TYPE_WSZ);
                Pos    = REG_DO_FAST_VAL__POS;
            }
            else if(VAL_IN_LIMITS(REG_DO_PWM_ALLOW__MBPOS, MbAddrIn, REG_DO_PWM_ALLOW__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_DO_PWM_ALLOW__MBPOS, REG_DO_PWM_ALLOW__TYPE_WSZ);
                Pos    = REG_DO_PWM_ALLOW__POS;
            }
            else if(VAL_IN_LIMITS(REG_SYS_CMD__MBPOS, MbAddrIn, REG_SYS_CMD__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_SYS_CMD__MBPOS, REG_SYS_CMD__TYPE_WSZ);
                Pos    = REG_SYS_CMD__POS;
            }
            else if(VAL_IN_LIMITS(REG_USER_DATA1__MBPOS, MbAddrIn, REG_USER_DATA1__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_USER_DATA1__MBPOS, REG_USER_DATA1__TYPE_WSZ);
                Pos    = REG_USER_DATA1__POS;
            }
            else
            {
                return (0);
            }
            break;

        case MBRTU_DISC_TABLE_ID:

            if(VAL_IN_LIMITS(REG_DI_NORM_VAL__MBPOS, MbAddrIn, REG_DI_NORM_VAL__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_DI_NORM_VAL__MBPOS, REG_DI_NORM_VAL__TYPE_WSZ);
                Pos    = REG_DI_NORM_VAL__POS;
            }
            else if(VAL_IN_LIMITS(REG_DI_TACH_SETPOINT_REACHED__MBPOS, MbAddrIn, REG_DI_TACH_SETPOINT_REACHED__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_DI_TACH_SETPOINT_REACHED__MBPOS, REG_DI_TACH_SETPOINT_REACHED__TYPE_WSZ);
                Pos    = REG_DI_TACH_SETPOINT_REACHED__POS;
            }
            else if(VAL_IN_LIMITS(REG_DI_CNTR_SETPOINT_REACHED__MBPOS, MbAddrIn, REG_DI_CNTR_SETPOINT_REACHED__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_DI_CNTR_SETPOINT_REACHED__MBPOS, REG_DI_CNTR_SETPOINT_REACHED__TYPE_WSZ);
                Pos    = REG_DI_CNTR_SETPOINT_REACHED__POS;
            }
            else
            {
                return (0);
            }
            break;

        case MBRTU_HOLD_TABLE_ID:

            if(VAL_IN_LIMITS(REG_DI_TACH_SETPOINT__MBPOS, MbAddrIn, REG_DI_TACH_SETPOINT__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_DI_TACH_SETPOINT__MBPOS, REG_DI_TACH_SETPOINT__TYPE_WSZ);
                Pos    = REG_DI_TACH_SETPOINT__POS;
            }
            else if(VAL_IN_LIMITS(REG_DI_CNTR_SETPOINT__MBPOS, MbAddrIn, REG_DI_CNTR_SETPOINT__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_DI_CNTR_SETPOINT__MBPOS, REG_DI_CNTR_SETPOINT__TYPE_WSZ);
                Pos    = REG_DI_CNTR_SETPOINT__POS;
            }
            else if(VAL_IN_LIMITS(REG_DI_MODE__MBPOS, MbAddrIn, REG_DI_MODE__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_DI_MODE__MBPOS, REG_DI_MODE__TYPE_WSZ);
                Pos    = REG_DI_MODE__POS;
            }
            else if(VAL_IN_LIMITS(REG_DI_FILTER_DELAY__MBPOS, MbAddrIn, REG_DI_FILTER_DELAY__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_DI_FILTER_DELAY__MBPOS, REG_DI_FILTER_DELAY__TYPE_WSZ);
                Pos    = REG_DI_FILTER_DELAY__POS;
            }
            else if(VAL_IN_LIMITS(REG_DO_PWM_VAL__MBPOS, MbAddrIn, REG_DO_PWM_VAL__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_DO_PWM_VAL__MBPOS, REG_DO_PWM_VAL__TYPE_WSZ);
                Pos    = REG_DO_PWM_VAL__POS;
            }
            else if(VAL_IN_LIMITS(REG_DO_PWM_PERIOD__MBPOS, MbAddrIn, REG_DO_PWM_PERIOD__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_DO_PWM_PERIOD__MBPOS, REG_DO_PWM_PERIOD__TYPE_WSZ);
                Pos    = REG_DO_PWM_PERIOD__POS;
            }
            else if(VAL_IN_LIMITS(REG_DO_MODE__MBPOS, MbAddrIn, REG_DO_MODE__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_DO_MODE__MBPOS, REG_DO_MODE__TYPE_WSZ);
                Pos    = REG_DO_MODE__POS;
            }
            else if(VAL_IN_LIMITS(REG_AI_MODE__MBPOS, MbAddrIn, REG_AI_MODE__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_AI_MODE__MBPOS, REG_AI_MODE__TYPE_WSZ);
                Pos    = REG_AI_MODE__POS;
            }
            else if(VAL_IN_LIMITS(REG_AI_KA__MBPOS, MbAddrIn, REG_AI_KA__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_AI_KA__MBPOS, REG_AI_KA__TYPE_WSZ);
                Pos    = REG_AI_KA__POS;
            }
            else if(VAL_IN_LIMITS(REG_AI_KB__MBPOS, MbAddrIn, REG_AI_KB__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_AI_KB__MBPOS, REG_AI_KB__TYPE_WSZ);
                Pos    = REG_AI_KB__POS;
            }
        	else if(VAL_IN_LIMITS(REG_USER_DATA2__MBPOS, MbAddrIn, REG_USER_DATA2__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_USER_DATA2__MBPOS, REG_USER_DATA2__TYPE_WSZ);
                Pos    = REG_USER_DATA2__POS;
            }
            else
            {
                return (0);
            }
            break;

        case MBRTU_INPT_TABLE_ID:

            if(VAL_IN_LIMITS(REG_DI_TACH_VAL__MBPOS, MbAddrIn, REG_DI_TACH_VAL__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_DI_TACH_VAL__MBPOS, REG_DI_TACH_VAL__TYPE_WSZ);
                Pos    = REG_DI_TACH_VAL__POS;
            }
            else if(VAL_IN_LIMITS(REG_DI_CNTR_VAL__MBPOS, MbAddrIn, REG_DI_CNTR_VAL__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_DI_CNTR_VAL__MBPOS, REG_DI_CNTR_VAL__TYPE_WSZ);
                Pos    = REG_DI_CNTR_VAL__POS;
            }
            else if(VAL_IN_LIMITS(REG_DI_STATUS__MBPOS, MbAddrIn, REG_DI_STATUS__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_DI_STATUS__MBPOS, REG_DI_STATUS__TYPE_WSZ);
                Pos    = REG_DI_STATUS__POS;
            }
            else if(VAL_IN_LIMITS(REG_DO_STATUS__MBPOS, MbAddrIn, REG_DO_STATUS__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_DO_STATUS__MBPOS, REG_DO_STATUS__TYPE_WSZ);
                Pos    = REG_DO_STATUS__POS;
            }
            else if(VAL_IN_LIMITS(REG_AI_VAL__MBPOS, MbAddrIn, REG_AI_VAL__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_AI_VAL__MBPOS, REG_AI_VAL__TYPE_WSZ);
                Pos    = REG_AI_VAL__POS;
            }
        	else if(VAL_IN_LIMITS(REG_AI_STATUS__MBPOS, MbAddrIn, REG_AI_STATUS__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_AI_STATUS__MBPOS, REG_AI_STATUS__TYPE_WSZ);
                Pos    = REG_AI_STATUS__POS;
            }
        	else if(VAL_IN_LIMITS(REG_SYS_STAT__MBPOS, MbAddrIn, REG_SYS_STAT__MBPOS_END))
            {
                iGroup = REG_CALC_POS_BY_MBADDR(MbAddrIn, REG_SYS_STAT__MBPOS, REG_SYS_STAT__TYPE_WSZ);
                Pos    = REG_SYS_STAT__POS;
            }
            else
            {
                return (0);
            }
            break;

        default:
            return (0);
    }

//#ifdef DEBUG_LOG_REG
//    DebugLog("GetByMbAddr: MbTable=%d MbAddr=%d Pos=%d iGroup=%d\n", MbTableIn, MbAddrIn, Pos, iGroup);
//#endif // DEBUG_LOG_REG

    return (REG_GetByPos(Pos, iGroup));
}



#ifdef RTE_MOD_REG_MON

/** @brief  Send change-monitoring status to Queue (by REG_t).
 *  @param  QueueIn - target queue.
 *  @param  RegIn   - pointer to register.
 *  @return Result:
 *  @arg      = 0 - error
 *  @arg      = 1 - OK
 */
static uint8_t REG_MonitorSendToQueue(REG_t *RegIn, QueueHandle_t QueueIn)
{
    if(RegIn && QueueIn)
    {
#ifdef DEBUG_LOG_REG_MON
        DebugLog("RegMonToQueue: iReg=%d iGroup=%d mbt=%d mba=%d\n", RegIn->iReg, RegIn->iGroup, RegIn->MbTable, RegIn->MbAddr);
#endif // DEBUG_LOG_REG_MON

        //Write Queue (not-blocking)
        //send updated register
        xQueueSendToBack(QueueIn, &(RegIn->iReg), 0);

        return (BIT_TRUE);
    }
    return (BIT_FALSE);
}

/** @brief  Send change-monitoring status to Queue (RTOS_DATA_REG_MONITOR_Q) (by REG_t).
 *  @param  RegIn - pointer to register.
 *  @return Result:
 *  @arg      = 0 - error
 *  @arg      = 1 - OK
 */
static inline uint8_t REG_MonitorSendToQueueData(REG_t *RegIn)
{
    return (REG_MonitorSendToQueue(RegIn, RTOS_DATA_REG_MONITOR_Q));
}

/** @brief  Change-monitoring (by REG_t).
 *  @param  RegIn     - pointer to register.
 *  @param  QueueIn   - target queue.
 *  @param  ValIn     - current register value.
 *  @param  ValPrevIn - previous register value.
 *  @return Result:
 *  @arg      = 0 - not changed
 *  @arg      = 1 - changed
 */
static inline uint8_t REG_Monitor(REG_t *RegIn, QueueHandle_t QueueIn, uint16_t ValIn, uint16_t ValPrevIn)
{
    return ((ValIn != ValPrevIn) ? REG_MonitorSendToQueue(RegIn, QueueIn) : BIT_FALSE);
}

/** @brief  Change-monitoring (by position in REGS).
 *  @param  IDxIn     - position in REGS.
 *  @param  QueueIn   - target queue.
 *  @param  ValIn     - current register value.
 *  @param  ValPrevIn - previous register value.
 *  @return Result:
 *  @arg      = 0 - not changed
 *  @arg      = 1 - changed
 */
/*
static uint8_t REG_MonitorByIDx(uint16_t IDxIn, QueueHandle_t QueueIn, uint16_t ValIn, uint16_t ValPrevIn)
{
	REG_t *Reg = REG_GetByIDx(IDxIn);
    return (REG_Monitor(Reg, QueueIn, ValIn, ValPrevIn));
}
*/

/** @brief  Change-monitoring (by ModBus Address).
 *  @param  MbTableIn - ModBus table ID.
 *  @param  MbAddrIn  - ModBus address of register.
 *  @param  QueueIn   - target queue.
 *  @param  ValIn     - current register value.
 *  @param  ValPrevIn - previous register value.
 *  @param  IDxIn     - pointer to store register position in REGS or 0.
 *  @return Result:
 *  @arg      = 0 - not changed
 *  @arg      = 1 - changed
 */
static uint8_t REG_MonitorByMbAddr(uint8_t MbTableIn, uint16_t MbAddrIn, QueueHandle_t QueueIn, uint16_t ValIn, uint16_t ValPrevIn, uint16_t *IDxIn)
{
    REG_t *Reg = REG_GetByMbAddr(MbTableIn, MbAddrIn);
    if(Reg)
    {
        if(IDxIn) *IDxIn = Reg->iReg;
        return (REG_Monitor(Reg, QueueIn, ValIn, ValPrevIn));
    }
    return (BIT_FALSE);
}

/** @brief  Change-monitoring (RTOS_DATA_REG_MONITOR_Q) (by REG_t).
 *  @param  RegIn     - pointer to register.
 *  @param  ValIn     - current register value.
 *  @param  ValPrevIn - previous register value.
 *  @return Result:
 *  @arg      = 0 - not changed
 *  @arg      = 1 - changed
 */
static inline uint8_t REG_MonitorForQueueData(REG_t *RegIn, uint16_t ValIn, uint16_t ValPrevIn)
{
    return (REG_Monitor(RegIn, RTOS_DATA_REG_MONITOR_Q, ValIn, ValPrevIn));
}

/** @brief  Change-monitoring (RTOS_DATA_REG_MONITOR_Q) (by ModBus Address).
 *  @param  MbTableIn - ModBus table ID.
 *  @param  MbAddrIn  - ModBus address of register.
 *  @param  ValIn     - current register value.
 *  @param  ValPrevIn - previous register value.
 *  @param  IDxIn     - pointer to store register position in REGS or 0.
 *  @return Result:
 *  @arg      = 0 - not changed
 *  @arg      = 1 - changed
 */
static inline uint8_t REG_MonitorForQueueDataByMbAddr(uint8_t MbTableIn, uint16_t MbAddrIn, uint16_t ValIn, uint16_t ValPrevIn, uint16_t *IDxIn)
{
    return (REG_MonitorByMbAddr(MbTableIn, MbAddrIn, RTOS_DATA_REG_MONITOR_Q, ValIn, ValPrevIn, IDxIn));
}

#endif // RTE_MOD_REG_MON



/** @brief  Copy words (+ change-monitoring multibyte values).
 *  @param  FromIn    - pointer to source buffer of words.
 *  @param  FromSzIn  - size of source buffer of words.
 *  @param  ToIn      - pointer to destination buffer of words.
 *  @param  MbTableIn - ModBus table ID (mbrtu.h).
 *  @param  MbAddrIn  - ModBus address.
 *  @return Size of copied words.
 *  @note
 *  MbTableIn and MbAddrIn are used to get REG_t from REGS for change-monitoring.
 */
uint8_t REG_CopyWords(uint16_t *FromIn, uint16_t FromSzIn, uint16_t *ToIn, uint8_t MbTableIn, uint16_t MbAddrIn)
{
    uint16_t i=0;

#ifdef RTE_MOD_REG_MON
    uint8_t  fChange = BIT_FALSE;
#endif // RTE_MOD_REG_MON

    if(FromIn && FromSzIn > 0 && ToIn)
    {
        for(i=0; i<FromSzIn; i++)
        {
#ifdef RTE_MOD_REG_MON
            if(!fChange) fChange = REG_MonitorForQueueDataByMbAddr(MbTableIn, (MbAddrIn+i), (*(FromIn+i)), (*(ToIn+i)), 0);
#else
            (void)MbTableIn;
            (void)MbAddrIn;
#endif // RTE_MOD_REG_MON
            *(ToIn+i) = *(FromIn+i);
        }
    }
    return (i);
}

/** @brief  Copy a value into ModBus (Data) Table.
 *  @param  TypeIn      - data type of value (type.h).
 *  @param  ValueBitIn  - pointer to buffer of bit-value (for Boolean Data Table).
 *  @param  ValueWordIn - pointer to buffer of word-value (for Numeric Data Table).
 *  @param  MbTableIn   - ModBus (Data) Table ID (mbrtu.h).
 *  @param  MbVarIn     - pointer to ModBus (Data) Table register.
 *  @param  MonIn       - change-monitoring:
 *  @arg      = 0 - off
 *  @arg      = 1 - on
 *  @return Result:
 *  @arg      = 0 - error
 *  @arg      = 1 - OK
 *  @note   Size of copied data by TypeIn.
 */
uint8_t REG_CopyValueToMb(uint8_t TypeIn, uint8_t *ValueBitIn, uint16_t *ValueWordIn, uint8_t MbTableIn, uint16_t MbAddrIn, void *MbVarIn, uint8_t MonIn)
{
    uint8_t Sz;

    if(ValueBitIn && ValueWordIn && MbVarIn)
    {
        switch(MbTableIn)
        {
            case MBRTU_COIL_TABLE_ID:
            case MBRTU_DISC_TABLE_ID:
#ifdef RTE_MOD_REG_MON
                if(MonIn) REG_MonitorForQueueDataByMbAddr(MbTableIn, MbAddrIn, (uint16_t)(*(uint8_t *)ValueBitIn), (uint16_t)(*(uint8_t *)MbVarIn), 0);
#else
                (void)MbTableIn;
                (void)MbAddrIn;
                (void)MonIn;
#endif // RTE_MOD_REG_MON
                *(uint8_t *)MbVarIn = *ValueBitIn;
                return (BIT_TRUE);

            case MBRTU_HOLD_TABLE_ID:
            case MBRTU_INPT_TABLE_ID:
                Sz = Type_GetWSz(TypeIn);
#ifdef RTE_MOD_REG_MON
                if(MonIn) return ((REG_CopyWords(ValueWordIn, Sz, (uint16_t *)MbVarIn, MbTableIn, MbAddrIn)) ? BIT_TRUE : BIT_FALSE);
#else
                (void)MbTableIn;
                (void)MbAddrIn;
                (void)MonIn;
#endif // RTE_MOD_REG_MON
                return ((Type_CopyWords(ValueWordIn, Sz, (uint16_t *)MbVarIn)) ? BIT_TRUE : BIT_FALSE);
        }
    }
    return (BIT_FALSE);
}

/** @brief  Copy a value from Word-buffer into ModBus (Data) Table.
 *  @param  RegIn     - pointer to register (REG_t).
 *  @param  FromIn    - pointer to Word-buffer.
 *  @param  FromSzIn  - size of Word-buffer (<= size of register value type in words: __WSZ; type.h).
 *  @param  FromOrdIn - byte ordering type of Word-buffer (type.h).
 *  @param  ZeroedIn  - zeroed Word-buffer:
 *  @arg      = 0 - no,
 *  @arg      = 1 - yes.
 *  @param  MonIn - change-monitoring:
 *  @arg      = 0 - off
 *  @arg      = 1 - on
 *  @return Result:
 *  @arg      = 0 - error
 *  @arg      = 1 - OK
 */
uint8_t REG_CopyWordsToMb(REG_t *RegIn, uint16_t *FromIn, uint8_t FromSzIn, uint8_t FromOrdIn, uint8_t ZeroedIn, uint8_t MonIn)
{
    uint8_t fChange;

    if(RegIn && FromIn && FromSzIn)
    {
        switch(RegIn->MbTable)
        {
            case MBRTU_COIL_TABLE_ID:
            case MBRTU_DISC_TABLE_ID:
#ifdef RTE_MOD_REG_MON
                if(MonIn) REG_MonitorForQueueData(RegIn, *FromIn, (uint16_t)(*(uint8_t *)RegIn->pMbVar));
#else
                (void)MonIn;
#endif // RTE_MOD_REG_MON
                *(uint8_t *)RegIn->pMbVar= *FromIn;
                return (1);

            case MBRTU_HOLD_TABLE_ID:
            case MBRTU_INPT_TABLE_ID:
                fChange = 0;
                Type_CopyWordsExt(FromIn, FromSzIn, FromOrdIn, (uint16_t *)RegIn->pMbVar, RegIn->Wsz, TYPE_BYTE_ORDER_DEF, ZeroedIn, &fChange);
#ifdef RTE_MOD_REG_MON
                if(MonIn && fChange) REG_MonitorSendToQueueData(RegIn);
#else
                (void)MonIn;
#endif // RTE_MOD_REG_MON
                return (RegIn->Wsz);
        }
    }
    return (0);
}

/** @brief  Copy a value from ModBus (Data) Table.
 *  @param  TypeIn      - data type of value (type.h).
 *  @param  ValueBitIn  - pointer to buffer of bit-value (for Boolean Data Table).
 *  @param  ValueWordIn - pointer to buffer of word-value (for Numeric Data Table).
 *  @param  MbTableIn   - ModBus (Data) Table ID (mbrtu.h).
 *  @param  MbVarIn     - pointer to ModBus (Data) Table register.
 *  @return Result:
 *  @arg      = 0 - error
 *  @arg      = 1 - OK
 *  @note   Size of copied data by TypeIn.
 */
uint8_t REG_CopyValueFromMb(uint8_t TypeIn, uint8_t *ValueBitIn, uint16_t *ValueWordIn, uint8_t MbTableIn, void *MbVarIn)
{
    uint8_t Sz;

    if(ValueBitIn && ValueWordIn && MbVarIn)
    {
        switch(MbTableIn)
        {
            case MBRTU_COIL_TABLE_ID:
            case MBRTU_DISC_TABLE_ID:
                *ValueBitIn    = *(uint8_t *)MbVarIn;
                ValueWordIn[0] = (uint16_t)(*ValueBitIn);
                return (BIT_TRUE);

            case MBRTU_HOLD_TABLE_ID:
            case MBRTU_INPT_TABLE_ID:
                Sz = Type_GetWSz(TypeIn);
                return ((Type_CopyWords((uint16_t *)MbVarIn, Sz, ValueWordIn)) ? BIT_TRUE : BIT_FALSE);
        }
    }
    return (BIT_FALSE);
}


/** @brief  Copy a value from Data Table into Word-buffer.
 *  @param  RegIn    - pointer to register (REG_t).
 *  @param  ToIn     - pointer to Word-buffer.
 *  @param  ToSzIn   - size of Word-buffer (<= size of register value type in words: __WSZ; type.h).
 *  @param  ToOrdIn  - byte ordering type of Word-buffer (type.h).
 *  @param  ZeroedIn - zeroed Word-buffer:
 *  @arg      = 0 - no,
 *  @arg      = 1 - yes.
 *  @return Result:
 *  @arg      = 0 - error
 *  @arg      = 1 - OK
 */
uint8_t REG_CopyWordsFromMb(REG_t *RegIn, uint16_t *ToIn, uint8_t ToSzIn, uint8_t ToOrdIn, uint8_t ZeroedIn)
{
    if(RegIn && ToIn && ToSzIn)
    {
        switch(RegIn->MbTable)
        {
            case MBRTU_COIL_TABLE_ID:
            case MBRTU_DISC_TABLE_ID:
                if(ZeroedIn) Type_InitWords(ToIn, ToSzIn, 0);
                *ToIn = Type_OrderWordBytes((uint16_t)(*(uint8_t *)RegIn->pMbVar), TYPE_BYTE_ORDER_DEF, ToOrdIn);
                return (1);

            case MBRTU_HOLD_TABLE_ID:
            case MBRTU_INPT_TABLE_ID:
                return (Type_CopyWordsExt((uint16_t *)RegIn->pMbVar, RegIn->Wsz, TYPE_BYTE_ORDER_DEF, ToIn, ToSzIn, ToOrdIn, ZeroedIn, 0));
        }
    }
    return (0);
}

#ifdef RTE_MOD_APP
/** @brief  Copy unsigned numeric value from Located variable into Data Table.
 *  @param  RegIn - pointer to register.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not float numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported BOOL, BYTE, WORD, DWORD, LWORD register types.
 */
uint8_t REG_CopyUnsignedAppToMb(REG_t *RegIn)
{
    LWORD_uwt Ut;
    Type_InitWords(Ut.words, TYPE_LWORD_WSZ, 0);

    uint8_t BitVal = BIT_FALSE;

    if(RegIn)
    {
        if(RegIn->pAppVar && RegIn->pMbVar && (RegIn->Type == TYPE_BYTE || RegIn->Type == TYPE_WORD || RegIn->Type == TYPE_DWORD || RegIn->Type == TYPE_LWORD))
        {
            switch(RegIn->Type)
            {
                case TYPE_BYTE:
                    Ut.data = (uint64_t)(*(IEC_BYTE *)(RegIn->pAppVar->v_buf));
                    break;
                case TYPE_WORD:
                    Ut.data = (uint64_t)(*(IEC_WORD *)(RegIn->pAppVar->v_buf));
                    break;
                case TYPE_DWORD:
                    Ut.data = (uint64_t)(*(IEC_DWORD *)(RegIn->pAppVar->v_buf));
                    break;
                case TYPE_LWORD:
                    Ut.data = (*(IEC_LWORD *)(RegIn->pAppVar->v_buf));
                    break;
            }

            if(Ut.data > 0) BitVal = BIT_TRUE;
            return (REG_CopyValueToMb(RegIn->Type, &BitVal, Ut.words, RegIn->MbTable, RegIn->MbAddr, RegIn->pMbVar, RegIn->Monitor));
        }
    }
    return (BIT_FALSE);
}
#endif // RTE_MOD_APP

/** @brief  Copy unsigned numeric value from Data Table into Variable.
 *  @param  RegIn - pointer to register.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not double numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported BOOL, BYTE, WORD, DWORD, LWORD register types.
 */
uint8_t REG_CopyUnsignedMbToVar(REG_t *RegIn, void *VarIn)
{
    LWORD_uwt Ut;
    Type_InitWords(Ut.words, TYPE_LWORD_WSZ, 0);

    uint8_t BitVal = BIT_FALSE;

    if(RegIn && VarIn)
    {
        if(RegIn->pMbVar && (RegIn->Type == TYPE_BYTE || RegIn->Type == TYPE_WORD || RegIn->Type == TYPE_DWORD || RegIn->Type == TYPE_LWORD))
        {
            Ut.data = 0;
            if(REG_CopyValueFromMb(RegIn->Type, &BitVal, Ut.words, RegIn->MbTable, RegIn->pMbVar))
            {
                switch(RegIn->Type)
                {
                    case TYPE_BYTE:
                        (*(IEC_BYTE *)(VarIn))  = (IEC_BYTE)Ut.data;
                        break;
                    case TYPE_WORD:
                        (*(IEC_WORD *)(VarIn))  = (IEC_WORD)Ut.data;
                        break;
                    case TYPE_DWORD:
                        (*(IEC_DWORD *)(VarIn)) = (IEC_DWORD)Ut.data;
                        break;
                    case TYPE_LWORD:
                        (*(IEC_LWORD *)(VarIn)) = (IEC_LWORD)Ut.data;
                        break;
                }

                return (BIT_TRUE);
            }
        }
    }
    return (BIT_FALSE);
}

#ifdef RTE_MOD_APP
/** @brief  Copy unsigned numeric value from Data Table into Located Variable.
 *  @param  RegIn - pointer to register.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not double numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported BOOL, BYTE, WORD, DWORD, LWORD register types.
 */
uint8_t REG_CopyUnsignedMbToApp(REG_t *RegIn)
{
    if(RegIn)
    {
        if(RegIn->pAppVar)
        {
            return (REG_CopyUnsignedMbToVar(RegIn, RegIn->pAppVar->v_buf));
        }
    }
    return (BIT_FALSE);
}
#endif // RTE_MOD_APP

/** @brief  Copy unsigned numeric value from Variable into Data Table.
 *  @param  RegIn - pointer to register.
 *  @param  VarIn - pointer to Variable.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not float numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported BOOL, BYTE, WORD, DWORD, LWORD register types.
 */
uint8_t REG_CopyUnsignedVarToMb(REG_t *RegIn, const void *VarIn)
{
    LWORD_uwt Ut;
    Type_InitWords(Ut.words, TYPE_LWORD_WSZ, 0);

    uint8_t BitVal = BIT_FALSE;

    if(RegIn && VarIn)
    {
        if(RegIn->pMbVar && (RegIn->Type == TYPE_BYTE || RegIn->Type == TYPE_WORD || RegIn->Type == TYPE_DWORD || RegIn->Type == TYPE_LWORD))
        {
            switch(RegIn->Type)
            {
                case TYPE_BYTE:
                    Ut.data = (uint64_t)(*(IEC_BYTE *)VarIn);
                    break;
                case TYPE_WORD:
                    Ut.data = (uint64_t)(*(IEC_WORD *)VarIn);
                    break;
                case TYPE_DWORD:
                    Ut.data = (uint64_t)(*(IEC_DWORD *)VarIn);
                    break;
                case TYPE_LWORD:
                    Ut.data = (*(IEC_LWORD *)VarIn);
                    break;
            }

            if(Ut.data > 0) BitVal = BIT_TRUE;
            return (REG_CopyValueToMb(RegIn->Type, &BitVal, Ut.words, RegIn->MbTable, RegIn->MbAddr, RegIn->pMbVar, RegIn->Monitor));
        }
    }
    return (BIT_FALSE);
}

#ifdef RTE_MOD_APP
/** @brief  Copy unsigned numeric value from Variable into Located Variable.
 *  @param  RegIn - pointer to register.
 *  @param  VarIn - pointer to Variable.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not double numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported BOOL, BYTE, WORD, DWORD, LWORD register types.
 */
uint8_t REG_CopyUnsignedVarToApp(REG_t *RegIn, const void *VarIn)
{
    if(RegIn && VarIn)
    {
        if(RegIn->pAppVar)
        {
            switch(RegIn->Type)
            {
                case TYPE_BYTE:
                    (*(IEC_BYTE *)(RegIn->pAppVar->v_buf)) = (*(IEC_BYTE *)VarIn);
                    return (BIT_TRUE);
                case TYPE_WORD:
                    (*(IEC_WORD *)(RegIn->pAppVar->v_buf))  = (*(IEC_WORD *)VarIn);
                    return (BIT_TRUE);
                case TYPE_DWORD:
                    (*(IEC_DWORD *)(RegIn->pAppVar->v_buf)) = (*(IEC_DWORD *)VarIn);
                    return (BIT_TRUE);
                case TYPE_LWORD:
                    (*(IEC_LWORD *)(RegIn->pAppVar->v_buf)) = (*(IEC_LWORD *)VarIn);
                    return (BIT_TRUE);
            }
        }
    }
    return (BIT_FALSE);
}
#endif // RTE_MOD_APP

/** @brief  Copy unsigned numeric value.
 *  @param  RegIn - pointer to register.
 *  @param  DstIn - destination of copy (reg.h):
 *  @arg      = REG_COPY_APP_TO_MB
 *  @arg      = REG_COPY_APP_TO_MB__NO_MON
 *  @arg      = REG_COPY_MB_TO_APP
 *  @arg      = REG_COPY_MB_TO_VAR
 *  @arg      = REG_COPY_VAR_TO_APP
 *  @arg      = REG_COPY_VAR_TO_MB
 *  @arg      = REG_COPY_VAR_TO_MB__NO_MON
 *  @arg      = REG_COPY_VAR_TO_ALL
 *  @arg      = REG_COPY_VAR_TO_ALL__NO_MON
 *  @param  VarIn - pointer to Variable or 0.
 *  @return Result:
 *  @arg      = 0 - error
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported BOOL, BYTE, WORD, DWORD, LWORD register types.
 */
uint8_t REG_CopyUnsigned(REG_t *RegIn, uint8_t DstIn, void *VarIn)
{
#ifdef RTE_MOD_REG_MON
    if(RegIn)
    {
       RegIn->Monitor = ((DstIn < REG_COPY_APP_TO_MB__NO_MON) ? BIT_TRUE : BIT_FALSE);
    }
#endif // RTE_MOD_REG_MON

    switch(DstIn)
    {
#ifdef RTE_MOD_APP
        case REG_COPY_APP_TO_MB:
        case REG_COPY_APP_TO_MB__NO_MON:
            return (REG_CopyUnsignedAppToMb(RegIn));

        case REG_COPY_MB_TO_APP:
            return (REG_CopyUnsignedMbToApp(RegIn));

        case REG_COPY_VAR_TO_APP:
            return (REG_CopyUnsignedVarToApp(RegIn, VarIn));
#endif // RTE_MOD_APP

        case REG_COPY_MB_TO_VAR:
            return (REG_CopyUnsignedMbToVar(RegIn, VarIn));

        case REG_COPY_VAR_TO_MB:
        case REG_COPY_VAR_TO_MB__NO_MON:
            return (REG_CopyUnsignedVarToMb(RegIn, VarIn));

        case REG_COPY_VAR_TO_ALL:
        case REG_COPY_VAR_TO_ALL__NO_MON:
#ifdef RTE_MOD_APP
            REG_CopyUnsignedVarToApp(RegIn, VarIn);
#endif // RTE_MOD_APP
            return (REG_CopyUnsignedVarToMb(RegIn, VarIn));
    }
    return (BIT_FALSE);
}

#ifdef RTE_MOD_APP
/** @brief  Copy signed numeric value from Located variable into Data Table.
 *  @param  RegIn - pointer to register.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not float numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported SINT, INT, DINT, LINT register types.
 */
uint8_t REG_CopySignedAppToMb(REG_t *RegIn)
{
    LINT_uwt Ut;
    Type_InitWords(Ut.words, TYPE_LINT_WSZ, 0);

    uint8_t BitVal = BIT_FALSE;

    if(RegIn)
    {
        if(RegIn->pAppVar && RegIn->pMbVar && (RegIn->Type == TYPE_SINT || RegIn->Type == TYPE_INT || RegIn->Type == TYPE_DINT || RegIn->Type == TYPE_LINT))
        {
            switch(RegIn->Type)
            {
                case TYPE_SINT:
                    Ut.data = (int64_t)(*(IEC_SINT *)(RegIn->pAppVar->v_buf));
                    break;
                case TYPE_INT:
                    Ut.data = (int64_t)(*(IEC_INT *)(RegIn->pAppVar->v_buf));
                    break;
                case TYPE_DINT:
                    Ut.data = (int64_t)(*(IEC_DINT *)(RegIn->pAppVar->v_buf));
                    break;
                case TYPE_LINT:
                    Ut.data = (*(IEC_LINT *)(RegIn->pAppVar->v_buf));
                    break;
            }

            if(Ut.data > 0) BitVal = BIT_TRUE;
            return (REG_CopyValueToMb(RegIn->Type, &BitVal, Ut.words, RegIn->MbTable, RegIn->MbAddr, RegIn->pMbVar, RegIn->Monitor));
        }
    }
    return (BIT_FALSE);
}
#endif // RTE_MOD_APP

/** @brief  Copy signed numeric value from Data Table into Variable.
 *  @param  RegIn - pointer to register.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not double numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported SINT, INT, DINT, LINT register types.
 */
uint8_t REG_CopySignedMbToVar(REG_t *RegIn, void *VarIn)
{
    LINT_uwt Ut;
    Type_InitWords(Ut.words, TYPE_LINT_WSZ, 0);

    uint8_t BitVal = BIT_FALSE;

    if(RegIn && VarIn)
    {
        if(RegIn->pMbVar && (RegIn->Type == TYPE_SINT || RegIn->Type == TYPE_INT || RegIn->Type == TYPE_DINT || RegIn->Type == TYPE_LINT))
        {
            Ut.data = 0;
            if(REG_CopyValueFromMb(RegIn->Type, &BitVal, Ut.words, RegIn->MbTable, RegIn->pMbVar))
            {
                switch(RegIn->Type)
                {
                    case TYPE_SINT:
                        (*(IEC_SINT *)(VarIn)) = (IEC_SINT)Ut.data;
                        break;
                    case TYPE_INT:
                        (*(IEC_INT *)(VarIn))  = (IEC_INT)Ut.data;
                        break;
                    case TYPE_DINT:
                        (*(IEC_DINT *)(VarIn)) = (IEC_DINT)Ut.data;
                        break;
                    case TYPE_LINT:
                        (*(IEC_LINT *)(VarIn)) = (IEC_LINT)Ut.data;
                        break;
                }

                return (BIT_TRUE);
            }
        }
    }
    return (BIT_FALSE);
}

#ifdef RTE_MOD_APP
/** @brief  Copy signed numeric value from Data Table into Located Variable.
 *  @param  RegIn - pointer to register.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not double numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported SINT, INT, DINT, LINT register types.
 */
uint8_t REG_CopySignedMbToApp(REG_t *RegIn)
{
    if(RegIn)
    {
        if(RegIn->pAppVar)
        {
            return (REG_CopySignedMbToVar(RegIn, RegIn->pAppVar->v_buf));
        }
    }
    return (BIT_FALSE);
}
#endif // RTE_MOD_APP

/** @brief  Copy signed numeric value from Variable into Data Table.
 *  @param  RegIn - pointer to register.
 *  @param  VarIn - pointer to Variable.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not float numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported SINT, INT, DINT, LINT register types.
 */
uint8_t REG_CopySignedVarToMb(REG_t *RegIn, const void *VarIn)
{
    LINT_uwt Ut;
    Type_InitWords(Ut.words, TYPE_LINT_WSZ, 0);

    uint8_t BitVal = BIT_FALSE;

    if(RegIn && VarIn)
    {
        if(RegIn->pMbVar && (RegIn->Type == TYPE_SINT || RegIn->Type == TYPE_INT || RegIn->Type == TYPE_DINT || RegIn->Type == TYPE_LINT))
        {
            switch(RegIn->Type)
            {
                case TYPE_SINT:
                    Ut.data = (int64_t)(*(IEC_SINT *)VarIn);
                    break;
                case TYPE_INT:
                    Ut.data = (int64_t)(*(IEC_INT *)VarIn);
                    break;
                case TYPE_DINT:
                    Ut.data = (int64_t)(*(IEC_DINT *)VarIn);
                    break;
                case TYPE_LINT:
                    Ut.data = (*(IEC_LINT *)VarIn);
                    break;
            }

            if(Ut.data > 0) BitVal = BIT_TRUE;
            return (REG_CopyValueToMb(RegIn->Type, &BitVal, Ut.words, RegIn->MbTable, RegIn->MbAddr, RegIn->pMbVar, RegIn->Monitor));
        }
    }
    return (BIT_FALSE);
}

#ifdef RTE_MOD_APP
/** @brief  Copy signed numeric value from Variable into Located Variable.
 *  @param  RegIn - pointer to register.
 *  @param  VarIn - pointer to Variable.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not double numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported SINT, INT, DINT, LINT register types.
 */
uint8_t REG_CopySignedVarToApp(REG_t *RegIn, const void *VarIn)
{
    if(RegIn && VarIn)
    {
        if(RegIn->pAppVar)
        {
            switch(RegIn->Type)
            {
                case TYPE_SINT:
                    (*(IEC_SINT *)(RegIn->pAppVar->v_buf)) = (*(IEC_SINT *)VarIn);
                    return (BIT_TRUE);
                case TYPE_INT:
                    (*(IEC_INT *)(RegIn->pAppVar->v_buf))  = (*(IEC_INT *)VarIn);
                    return (BIT_TRUE);
                case TYPE_DINT:
                    (*(IEC_DINT *)(RegIn->pAppVar->v_buf)) = (*(IEC_DINT *)VarIn);
                    return (BIT_TRUE);
                case TYPE_LINT:
                    (*(IEC_LINT *)(RegIn->pAppVar->v_buf)) = (*(IEC_LINT *)VarIn);
                    return (BIT_TRUE);
            }
        }
    }
    return (BIT_FALSE);
}
#endif // RTE_MOD_APP

/** @brief  Copy signed numeric value.
 *  @param  RegIn - pointer to register.
 *  @param  DstIn - destination of copy (reg.h):
 *  @arg      = REG_COPY_APP_TO_MB
 *  @arg      = REG_COPY_APP_TO_MB__NO_MON
 *  @arg      = REG_COPY_MB_TO_APP
 *  @arg      = REG_COPY_MB_TO_VAR
 *  @arg      = REG_COPY_VAR_TO_APP
 *  @arg      = REG_COPY_VAR_TO_MB
 *  @arg      = REG_COPY_VAR_TO_MB__NO_MON
 *  @arg      = REG_COPY_VAR_TO_ALL
 *  @arg      = REG_COPY_VAR_TO_ALL__NO_MON
 *  @param  VarIn - pointer to Variable or 0.
 *  @return Result:
 *  @arg      = 0 - error
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported SINT, INT, DINT, LINT register types.
 */
uint8_t REG_CopySigned(REG_t *RegIn, uint8_t DstIn, void *VarIn)
{
#ifdef RTE_MOD_REG_MON
    if(RegIn)
    {
       RegIn->Monitor = ((DstIn < REG_COPY_APP_TO_MB__NO_MON) ? BIT_TRUE : BIT_FALSE);
    }
#endif // RTE_MOD_REG_MON

    switch(DstIn)
    {
#ifdef RTE_MOD_APP
        case REG_COPY_APP_TO_MB:
        case REG_COPY_APP_TO_MB__NO_MON:
            return (REG_CopySignedAppToMb(RegIn));

        case REG_COPY_MB_TO_APP:
            return (REG_CopySignedMbToApp(RegIn));

        case REG_COPY_VAR_TO_APP:
            return (REG_CopySignedVarToApp(RegIn, VarIn));
#endif // RTE_MOD_APP

        case REG_COPY_MB_TO_VAR:
            return (REG_CopySignedMbToVar(RegIn, VarIn));

        case REG_COPY_VAR_TO_MB:
        case REG_COPY_VAR_TO_MB__NO_MON:
            return (REG_CopySignedVarToMb(RegIn, VarIn));

        case REG_COPY_VAR_TO_ALL:
        case REG_COPY_VAR_TO_ALL__NO_MON:
#ifdef RTE_MOD_APP
            REG_CopySignedVarToApp(RegIn, VarIn);
#endif // RTE_MOD_APP
            return (REG_CopySignedVarToMb(RegIn, VarIn));
    }
    return (BIT_FALSE);
}

#ifdef RTE_MOD_APP
/** @brief  Copy float numeric value from Located variable into Data Table.
 *  @param  RegIn - pointer to register.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not float numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported FLOAT, REAL register types.
 */
uint8_t REG_CopyFloatAppToMb(REG_t *RegIn)
{
    FLOAT_uwt Ut;
    Type_InitWords(Ut.words, TYPE_FLOAT_WSZ, 0);

    uint8_t BitVal = BIT_FALSE;

    if(RegIn)
    {
        if(RegIn->pAppVar && RegIn->pMbVar && RegIn->Type == TYPE_FLOAT)
        {
            Ut.data = (*(IEC_REAL *)(RegIn->pAppVar->v_buf));
            if(Ut.data > 0) BitVal = BIT_TRUE;
            return (REG_CopyValueToMb(RegIn->Type, &BitVal, Ut.words, RegIn->MbTable, RegIn->MbAddr, RegIn->pMbVar, RegIn->Monitor));
        }
    }
    return (BIT_FALSE);
}
#endif // RTE_MOD_APP

/** @brief  Copy float numeric value from Data Table into Variable.
 *  @param  RegIn - pointer to register.
 *  @param  VarIn - pointer to Variable.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not double numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported FLOAT, REAL register types.
 */
uint8_t REG_CopyFloatMbToVar(REG_t *RegIn, void *VarIn)
{
    FLOAT_uwt Ut;
    Type_InitWords(Ut.words, TYPE_FLOAT_WSZ, 0);

    uint8_t BitVal = BIT_FALSE;

    if(RegIn && VarIn)
    {
        if(RegIn->pMbVar && RegIn->Type == TYPE_FLOAT)
        {
            Ut.data = 0.0;
            if(REG_CopyValueFromMb(RegIn->Type, &BitVal, Ut.words, RegIn->MbTable, RegIn->pMbVar))
            {
                (*(IEC_REAL *)(VarIn)) = (IEC_REAL)Ut.data;
                return (BIT_TRUE);
            }
        }
    }
    return (BIT_FALSE);
}

#ifdef RTE_MOD_APP
/** @brief  Copy float numeric value from Data Table into Located Variable.
 *  @param  RegIn - pointer to register.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not double numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported FLOAT, REAL register types.
 */
uint8_t REG_CopyFloatMbToApp(REG_t *RegIn)
{
    if(RegIn)
    {
        if(RegIn->pAppVar)
        {
            return (REG_CopyFloatMbToVar(RegIn, RegIn->pAppVar->v_buf));
        }
    }
    return (BIT_FALSE);
}
#endif // RTE_MOD_APP

/** @brief  Copy float numeric value from Variable into Data Table.
 *  @param  RegIn - pointer to register.
 *  @param  VarIn - pointer to Variable.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not float numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported FLOAT, REAL register types.
 */
uint8_t REG_CopyFloatVarToMb(REG_t *RegIn, const void *VarIn)
{
    FLOAT_uwt Ut;
    Type_InitWords(Ut.words, TYPE_FLOAT_WSZ, 0);

    uint8_t BitVal = BIT_FALSE;

    if(RegIn && VarIn)
    {
        if(RegIn->pMbVar && RegIn->Type == TYPE_FLOAT)
        {
            Ut.data = (*(IEC_REAL *)(VarIn));
            if(Ut.data > 0) BitVal = BIT_TRUE;
            return (REG_CopyValueToMb(RegIn->Type, &BitVal, Ut.words, RegIn->MbTable, RegIn->MbAddr, RegIn->pMbVar, RegIn->Monitor));
        }
    }
    return (BIT_FALSE);
}

#ifdef RTE_MOD_APP
/** @brief  Copy float numeric value from Variable into Located Variable.
 *  @param  RegIn - pointer to register.
 *  @param  VarIn - pointer to Variable.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not double numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported FLOAT, REAL register types.
 */
uint8_t REG_CopyFloatVarToApp(REG_t *RegIn, const void *VarIn)
{
    if(RegIn && VarIn)
    {
        if(RegIn->pAppVar && RegIn->Type == TYPE_FLOAT)
        {
            (*(IEC_REAL *)(RegIn->pAppVar->v_buf)) = (*(IEC_REAL *)VarIn);
            return (BIT_TRUE);
        }
    }
    return (BIT_FALSE);
}
#endif // RTE_MOD_APP

/** @brief  Copy float numeric value.
 *  @param  RegIn - pointer to register.
 *  @param  DstIn - destination of copy (reg.h):
 *  @arg      = REG_COPY_APP_TO_MB
 *  @arg      = REG_COPY_APP_TO_MB__NO_MON
 *  @arg      = REG_COPY_MB_TO_APP
 *  @arg      = REG_COPY_MB_TO_VAR
 *  @arg      = REG_COPY_VAR_TO_APP
 *  @arg      = REG_COPY_VAR_TO_MB
 *  @arg      = REG_COPY_VAR_TO_MB__NO_MON
 *  @arg      = REG_COPY_VAR_TO_ALL
 *  @arg      = REG_COPY_VAR_TO_ALL__NO_MON
 *  @param  VarIn - pointer to Variable or 0.
 *  @return Result:
 *  @arg      = 0 - error
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported FLOAT, REAL register types.
 */
uint8_t REG_CopyFloat(REG_t *RegIn, uint8_t DstIn, void *VarIn)
{
#ifdef RTE_MOD_REG_MON
    if(RegIn)
    {
       RegIn->Monitor = ((DstIn < REG_COPY_APP_TO_MB__NO_MON) ? BIT_TRUE : BIT_FALSE);
    }
#endif // RTE_MOD_REG_MON

    switch(DstIn)
    {
#ifdef RTE_MOD_APP
        case REG_COPY_APP_TO_MB:
        case REG_COPY_APP_TO_MB__NO_MON:
            return (REG_CopyFloatAppToMb(RegIn));

        case REG_COPY_MB_TO_APP:
            return (REG_CopyFloatMbToApp(RegIn));

        case REG_COPY_VAR_TO_APP:
            return (REG_CopyFloatVarToApp(RegIn, VarIn));
#endif // RTE_MOD_APP

        case REG_COPY_MB_TO_VAR:
            return (REG_CopyFloatMbToVar(RegIn, VarIn));

        case REG_COPY_VAR_TO_MB:
        case REG_COPY_VAR_TO_MB__NO_MON:
            return (REG_CopyFloatVarToMb(RegIn, VarIn));

        case REG_COPY_VAR_TO_ALL:
        case REG_COPY_VAR_TO_ALL__NO_MON:
#ifdef RTE_MOD_APP
            REG_CopyFloatVarToApp(RegIn, VarIn);
#endif // RTE_MOD_APP
            return (REG_CopyFloatVarToMb(RegIn, VarIn));
    }
    return (BIT_FALSE);
}

#ifdef RTE_MOD_APP
/** @brief  Copy double numeric value from Located variable into ModBus (Data) Table.
 *  @param  RegIn - pointer to register.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not float numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported DOUBLE, LREAL register types.
 */
uint8_t REG_CopyDoubleAppToMb(REG_t *RegIn)
{
    DOUBLE_uwt Ut;
    Type_InitWords(Ut.words, TYPE_DOUBLE_WSZ, 0);

    uint8_t BitVal = BIT_FALSE;

    if(RegIn)
    {
        if(RegIn->pAppVar && RegIn->pMbVar && RegIn->Type == TYPE_DOUBLE)
        {
            Ut.data = (*(IEC_LREAL *)(RegIn->pAppVar->v_buf));
            if(Ut.data > 0) BitVal = BIT_TRUE;
            return (REG_CopyValueToMb(RegIn->Type, &BitVal, Ut.words, RegIn->MbTable, RegIn->MbAddr, RegIn->pMbVar, RegIn->Monitor));
        }
    }
    return (BIT_FALSE);
}
#endif // RTE_MOD_APP

/** @brief  Copy double numeric value from ModBus (Data) Table into Variable.
 *  @param  RegIn - pointer to register.
 *  @param  VarIn - pointer to Variable.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not double numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported DOUBLE, LREAL register types.
 */
uint8_t REG_CopyDoubleMbToVar(REG_t *RegIn, void *VarIn)
{
    DOUBLE_uwt Ut;
    Type_InitWords(Ut.words, TYPE_DOUBLE_WSZ, 0);

    uint8_t BitVal = BIT_FALSE;

    if(RegIn && VarIn)
    {
        if(RegIn->pMbVar && RegIn->Type == TYPE_DOUBLE)
        {
            Ut.data = 0.0;
            if(REG_CopyValueFromMb(RegIn->Type, &BitVal, Ut.words, RegIn->MbTable, RegIn->pMbVar))
            {
                (*(IEC_LREAL *)(VarIn)) = (IEC_LREAL)Ut.data;
                return (BIT_TRUE);
            }
        }
    }
    return (BIT_FALSE);
}

#ifdef RTE_MOD_APP
/** @brief  Copy double numeric value from ModBus (Data) Table into Located Variable.
 *  @param  RegIn - pointer to register.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not double numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported DOUBLE, LREAL register types.
 */
uint8_t REG_CopyDoubleMbToApp(REG_t *RegIn)
{
    if(RegIn)
    {
        if(RegIn->pAppVar)
        {
            return (REG_CopyDoubleMbToVar(RegIn, RegIn->pAppVar->v_buf));
        }
    }
    return (BIT_FALSE);
}
#endif // RTE_MOD_APP

/** @brief  Copy double numeric value from Variable into ModBus (Data) Table.
 *  @param  RegIn - pointer to register.
 *  @param  VarIn - pointer to Variable.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not float numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported DOUBLE, LREAL register types.
 */
uint8_t REG_CopyDoubleVarToMb(REG_t *RegIn, const void *VarIn)
{
    DOUBLE_uwt Ut;
    Type_InitWords(Ut.words, TYPE_DOUBLE_WSZ, 0);

    uint8_t BitVal = BIT_FALSE;

    if(RegIn && VarIn)
    {
        if(RegIn->pMbVar && RegIn->Type == TYPE_DOUBLE)
        {
            Ut.data = (*(IEC_LREAL *)(VarIn));
            if(Ut.data > 0) BitVal = BIT_TRUE;
            return (REG_CopyValueToMb(RegIn->Type, &BitVal, Ut.words, RegIn->MbTable, RegIn->MbAddr, RegIn->pMbVar, RegIn->Monitor));
        }
    }
    return (BIT_FALSE);
}

#ifdef RTE_MOD_APP
/** @brief  Copy double numeric value from Variable into Located Variable.
 *  @param  RegIn - pointer to register.
 *  @param  VarIn - pointer to Variable.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not double numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported DOUBLE, LREAL register types.
 */
uint8_t REG_CopyDoubleVarToApp(REG_t *RegIn, const void *VarIn)
{
    if(RegIn && VarIn)
    {
        if(RegIn->pAppVar && RegIn->Type == TYPE_DOUBLE)
        {
            (*(IEC_LREAL *)(RegIn->pAppVar->v_buf)) = (*(IEC_LREAL *)VarIn);
            return (BIT_TRUE);
        }
    }
    return (BIT_FALSE);
}
#endif // RTE_MOD_APP

/** @brief  Copy double numeric value.
 *  @param  RegIn - pointer to register.
 *  @param  DstIn - destination of copy (reg.h):
 *  @arg      = REG_COPY_APP_TO_MB
 *  @arg      = REG_COPY_APP_TO_MB__NO_MON
 *  @arg      = REG_COPY_MB_TO_APP
 *  @arg      = REG_COPY_MB_TO_VAR
 *  @arg      = REG_COPY_VAR_TO_APP
 *  @arg      = REG_COPY_VAR_TO_MB
 *  @arg      = REG_COPY_VAR_TO_MB__NO_MON
 *  @arg      = REG_COPY_VAR_TO_ALL
 *  @arg      = REG_COPY_VAR_TO_ALL__NO_MON
 *  @param  VarIn - pointer to Variable or 0.
 *  @return Result:
 *  @arg      = 0 - error
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported DOUBLE, LREAL register types.
 */
uint8_t REG_CopyDouble(REG_t *RegIn, uint8_t DstIn, void *VarIn)
{
#ifdef RTE_MOD_REG_MON
    if(RegIn)
    {
       RegIn->Monitor = ((DstIn < REG_COPY_APP_TO_MB__NO_MON) ? BIT_TRUE : BIT_FALSE);
    }
#endif // RTE_MOD_REG_MON

    switch(DstIn)
    {
#ifdef RTE_MOD_APP
        case REG_COPY_APP_TO_MB:
        case REG_COPY_APP_TO_MB__NO_MON:
            return (REG_CopyDoubleAppToMb(RegIn));

        case REG_COPY_MB_TO_APP:
            return (REG_CopyDoubleMbToApp(RegIn));

        case REG_COPY_VAR_TO_APP:
            return (REG_CopyDoubleVarToApp(RegIn, VarIn));
#endif // RTE_MOD_APP

        case REG_COPY_MB_TO_VAR:
            return (REG_CopyDoubleMbToVar(RegIn, VarIn));

        case REG_COPY_VAR_TO_MB:
        case REG_COPY_VAR_TO_MB__NO_MON:
            return (REG_CopyDoubleVarToMb(RegIn, VarIn));

        case REG_COPY_VAR_TO_ALL:
        case REG_COPY_VAR_TO_ALL__NO_MON:
#ifdef RTE_MOD_APP
            REG_CopyDoubleVarToApp(RegIn, VarIn);
#endif // RTE_MOD_APP
            return (REG_CopyDoubleVarToMb(RegIn, VarIn));
    }
    return (BIT_FALSE);
}


/** @brief  Copy single register.
 *  @param  RegIn - pointer to register.
 *  @param  DstIn - destination of copy (reg.h):
 *  @arg      = REG_COPY_APP_TO_MB
 *  @arg      = REG_COPY_APP_TO_MB__NO_MON
 *  @arg      = REG_COPY_MB_TO_APP
 *  @arg      = REG_COPY_MB_TO_VAR
 *  @arg      = REG_COPY_VAR_TO_APP
 *  @arg      = REG_COPY_VAR_TO_MB
 *  @arg      = REG_COPY_VAR_TO_MB__NO_MON
 *  @arg      = REG_COPY_VAR_TO_ALL
 *  @arg      = REG_COPY_VAR_TO_ALL__NO_MON
 *  @param  VarIn - pointer to Variable or 0.
 *  @return Result:
 *  @arg      = 0 - error
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 */
uint8_t REG_CopyReg(REG_t *RegIn, uint8_t DstIn, void *VarIn)
{
    if(RegIn)
    {
//#ifdef DEBUG_LOG_REG
//        DebugLog("CopyReg: iReg=%d MbAddr=%d\n", RegIn->iReg, RegIn->MbAddr);
//#endif // DEBUG_LOG_REG

        switch(RegIn->Type)
        {
            case TYPE_BYTE:
            case TYPE_WORD:
            case TYPE_DWORD:
            case TYPE_LWORD:
                return (REG_CopyUnsigned(RegIn, DstIn, VarIn));

            case TYPE_SINT:
            case TYPE_INT:
            case TYPE_DINT:
            case TYPE_LINT:
                return (REG_CopySigned(RegIn, DstIn, VarIn));

            case TYPE_FLOAT:
                return (REG_CopyFloat(RegIn, DstIn, VarIn));

            case TYPE_DOUBLE:
                return (REG_CopyDouble(RegIn, DstIn, VarIn));
        }
    }
    return (BIT_FALSE);
}


static uint8_t REG_CopyRegByte(REG_t *RegIn, uint8_t DstIn, const void *VarIn, uint8_t VarTypeIn)
{
    uint8_t Var;

    if(RegIn && VarIn)
    {
        switch(VarTypeIn)
        {
            case TYPE_BYTE:
                Var = (*(uint8_t *)VarIn);
                break;
            case TYPE_WORD:
                Var = (uint8_t)(*(uint16_t *)VarIn);
                break;
            case TYPE_DWORD:
                Var = (uint8_t)(*(uint32_t *)VarIn);
                break;
            case TYPE_LWORD:
                Var = (uint8_t)(*(uint64_t *)VarIn);
                break;
            case TYPE_SINT:
                Var = (uint8_t)(*(int8_t *)VarIn);
                break;
            case TYPE_INT:
                Var = (uint8_t)(*(int16_t *)VarIn);
                break;
            case TYPE_DINT:
                Var = (uint8_t)(*(int32_t *)VarIn);
                break;
            case TYPE_LINT:
                Var = (uint8_t)(*(int64_t *)VarIn);
                break;
            case TYPE_FLOAT:
                Var = (uint8_t)(*(float *)VarIn);
                break;
            case TYPE_DOUBLE:
                Var = (uint8_t)(*(double *)VarIn);
                break;
            default:
                return (BIT_FALSE);
        }
        return (REG_CopyReg(RegIn, DstIn, &Var));
    }
    return (BIT_FALSE);
}

static uint8_t REG_CopyRegWord(REG_t *RegIn, uint8_t DstIn, const void *VarIn, uint8_t VarTypeIn)
{
    uint16_t Var;

    if(RegIn && VarIn)
    {
        switch(VarTypeIn)
        {
            case TYPE_BYTE:
                Var = (uint16_t)(*(uint8_t *)VarIn);
                break;
            case TYPE_WORD:
                Var = (*(uint16_t *)VarIn);
                break;
            case TYPE_DWORD:
                Var = (uint16_t)(*(uint32_t *)VarIn);
                break;
            case TYPE_LWORD:
                Var = (uint16_t)(*(uint64_t *)VarIn);
                break;
            case TYPE_SINT:
                Var = (uint16_t)(*(int8_t *)VarIn);
                break;
            case TYPE_INT:
                Var = (uint16_t)(*(int16_t *)VarIn);
                break;
            case TYPE_DINT:
                Var = (uint16_t)(*(int32_t *)VarIn);
                break;
            case TYPE_LINT:
                Var = (uint16_t)(*(int64_t *)VarIn);
                break;
            case TYPE_FLOAT:
                Var = (uint16_t)(*(float *)VarIn);
                break;
            case TYPE_DOUBLE:
                Var = (uint16_t)(*(double *)VarIn);
                break;
            default:
                return (BIT_FALSE);
        }
        return (REG_CopyReg(RegIn, DstIn, &Var));
    }
    return (BIT_FALSE);
}

static uint8_t REG_CopyRegDWord(REG_t *RegIn, uint8_t DstIn, const void *VarIn, uint8_t VarTypeIn)
{
    uint32_t Var;

    if(RegIn && VarIn)
    {
        switch(VarTypeIn)
        {
            case TYPE_BYTE:
                Var = (uint32_t)(*(uint8_t *)VarIn);
                break;
            case TYPE_WORD:
                Var = (uint32_t)(*(uint16_t *)VarIn);
                break;
            case TYPE_DWORD:
                Var = (*(uint32_t *)VarIn);
                break;
            case TYPE_LWORD:
                Var = (uint32_t)(*(uint64_t *)VarIn);
                break;
            case TYPE_SINT:
                Var = (uint32_t)(*(int8_t *)VarIn);
                break;
            case TYPE_INT:
                Var = (uint32_t)(*(int16_t *)VarIn);
                break;
            case TYPE_DINT:
                Var = (uint32_t)(*(int32_t *)VarIn);
                break;
            case TYPE_LINT:
                Var = (uint32_t)(*(int64_t *)VarIn);
                break;
            case TYPE_FLOAT:
                Var = (uint32_t)(*(float *)VarIn);
                break;
            case TYPE_DOUBLE:
                Var = (uint32_t)(*(double *)VarIn);
                break;
            default:
                return (BIT_FALSE);
        }
        return (REG_CopyReg(RegIn, DstIn, &Var));
    }
    return (BIT_FALSE);
}

static uint8_t REG_CopyRegLWord(REG_t *RegIn, uint8_t DstIn, const void *VarIn, uint8_t VarTypeIn)
{
    uint64_t Var;

    if(RegIn && VarIn)
    {
        switch(VarTypeIn)
        {
            case TYPE_BYTE:
                Var = (uint64_t)(*(uint8_t *)VarIn);
                break;
            case TYPE_WORD:
                Var = (uint64_t)(*(uint16_t *)VarIn);
                break;
            case TYPE_DWORD:
                Var = (uint64_t)(*(uint32_t *)VarIn);
                break;
            case TYPE_LWORD:
                Var = (*(uint64_t *)VarIn);
                break;
            case TYPE_SINT:
                Var = (uint64_t)(*(int8_t *)VarIn);
                break;
            case TYPE_INT:
                Var = (uint64_t)(*(int16_t *)VarIn);
                break;
            case TYPE_DINT:
                Var = (uint64_t)(*(int32_t *)VarIn);
                break;
            case TYPE_LINT:
                Var = (uint64_t)(*(int64_t *)VarIn);
                break;
            case TYPE_FLOAT:
                Var = (uint64_t)(*(float *)VarIn);
                break;
            case TYPE_DOUBLE:
                Var = (uint64_t)(*(double *)VarIn);
                break;
            default:
                return (BIT_FALSE);
        }
        return (REG_CopyReg(RegIn, DstIn, &Var));
    }
    return (BIT_FALSE);
}

static uint8_t REG_CopyRegSInt(REG_t *RegIn, uint8_t DstIn, const void *VarIn, uint8_t VarTypeIn)
{
    int8_t Var;

    if(RegIn && VarIn)
    {
        switch(VarTypeIn)
        {
            case TYPE_BYTE:
                Var = (int8_t)(*(uint8_t *)VarIn);
                break;
            case TYPE_WORD:
                Var = (int8_t)(*(uint16_t *)VarIn);
                break;
            case TYPE_DWORD:
                Var = (int8_t)(*(uint32_t *)VarIn);
                break;
            case TYPE_LWORD:
                Var = (int8_t)(*(uint64_t *)VarIn);
                break;
            case TYPE_SINT:
                Var = (*(int8_t *)VarIn);
                break;
            case TYPE_INT:
                Var = (int8_t)(*(int16_t *)VarIn);
                break;
            case TYPE_DINT:
                Var = (int8_t)(*(int32_t *)VarIn);
                break;
            case TYPE_LINT:
                Var = (int8_t)(*(int64_t *)VarIn);
                break;
            case TYPE_FLOAT:
                Var = (int8_t)(*(float *)VarIn);
                break;
            case TYPE_DOUBLE:
                Var = (int8_t)(*(double *)VarIn);
                break;
            default:
                return (BIT_FALSE);
        }
        return (REG_CopyReg(RegIn, DstIn, &Var));
    }
    return (BIT_FALSE);
}

static uint8_t REG_CopyRegInt(REG_t *RegIn, uint8_t DstIn, const void *VarIn, uint8_t VarTypeIn)
{
    int16_t Var;

    if(RegIn && VarIn)
    {
        switch(VarTypeIn)
        {
            case TYPE_BYTE:
                Var = (int16_t)(*(uint8_t *)VarIn);
                break;
            case TYPE_WORD:
                Var = (int16_t)(*(uint16_t *)VarIn);
                break;
            case TYPE_DWORD:
                Var = (int16_t)(*(uint32_t *)VarIn);
                break;
            case TYPE_LWORD:
                Var = (int16_t)(*(uint64_t *)VarIn);
                break;
            case TYPE_SINT:
                Var = (int16_t)(*(int8_t *)VarIn);
                break;
            case TYPE_INT:
                Var = (*(int16_t *)VarIn);
                break;
            case TYPE_DINT:
                Var = (int16_t)(*(int32_t *)VarIn);
                break;
            case TYPE_LINT:
                Var = (int16_t)(*(int64_t *)VarIn);
                break;
            case TYPE_FLOAT:
                Var = (int16_t)(*(float *)VarIn);
                break;
            case TYPE_DOUBLE:
                Var = (int16_t)(*(double *)VarIn);
                break;
            default:
                return (BIT_FALSE);
        }
        return (REG_CopyReg(RegIn, DstIn, &Var));
    }
    return (BIT_FALSE);
}

static uint8_t REG_CopyRegDInt(REG_t *RegIn, uint8_t DstIn, const void *VarIn, uint8_t VarTypeIn)
{
    int32_t Var;

    if(RegIn && VarIn)
    {
        switch(VarTypeIn)
        {
            case TYPE_BYTE:
                Var = (int32_t)(*(uint8_t *)VarIn);
                break;
            case TYPE_WORD:
                Var = (int32_t)(*(uint16_t *)VarIn);
                break;
            case TYPE_DWORD:
                Var = (int32_t)(*(uint32_t *)VarIn);
                break;
            case TYPE_LWORD:
                Var = (int32_t)(*(uint64_t *)VarIn);
                break;
            case TYPE_SINT:
                Var = (int32_t)(*(int8_t *)VarIn);
                break;
            case TYPE_INT:
                Var = (int32_t)(*(int16_t *)VarIn);
                break;
            case TYPE_DINT:
                Var = (*(int32_t *)VarIn);
                break;
            case TYPE_LINT:
                Var = (int32_t)(*(int64_t *)VarIn);
                break;
            case TYPE_FLOAT:
                Var = (int32_t)(*(float *)VarIn);
                break;
            case TYPE_DOUBLE:
                Var = (int32_t)(*(double *)VarIn);
                break;
            default:
                return (BIT_FALSE);
        }
        return (REG_CopyReg(RegIn, DstIn, &Var));
    }
    return (BIT_FALSE);
}

static uint8_t REG_CopyRegLInt(REG_t *RegIn, uint8_t DstIn, const void *VarIn, uint8_t VarTypeIn)
{
    int64_t Var;

    if(RegIn && VarIn)
    {
        switch(VarTypeIn)
        {
            case TYPE_BYTE:
                Var = (int64_t)(*(uint8_t *)VarIn);
                break;
            case TYPE_WORD:
                Var = (int64_t)(*(uint16_t *)VarIn);
                break;
            case TYPE_DWORD:
                Var = (int64_t)(*(uint32_t *)VarIn);
                break;
            case TYPE_LWORD:
                Var = (int64_t)(*(uint64_t *)VarIn);
                break;
            case TYPE_SINT:
                Var = (int64_t)(*(int8_t *)VarIn);
                break;
            case TYPE_INT:
                Var = (int64_t)(*(int16_t *)VarIn);
                break;
            case TYPE_DINT:
                Var = (int64_t)(*(int32_t *)VarIn);
                break;
            case TYPE_LINT:
                Var = (*(int64_t *)VarIn);
                break;
            case TYPE_FLOAT:
                Var = (int64_t)(*(float *)VarIn);
                break;
            case TYPE_DOUBLE:
                Var = (int64_t)(*(double *)VarIn);
                break;
            default:
                return (BIT_FALSE);
        }
        return (REG_CopyReg(RegIn, DstIn, &Var));
    }
    return (BIT_FALSE);
}

static uint8_t REG_CopyRegFloat(REG_t *RegIn, uint8_t DstIn, const void *VarIn, uint8_t VarTypeIn)
{
    float Var;

    if(RegIn && VarIn)
    {
        switch(VarTypeIn)
        {
            case TYPE_BYTE:
                Var = (float)(*(uint8_t *)VarIn);
                break;
            case TYPE_WORD:
                Var = (float)(*(uint16_t *)VarIn);
                break;
            case TYPE_DWORD:
                Var = (float)(*(uint32_t *)VarIn);
                break;
            case TYPE_LWORD:
                Var = (float)(*(uint64_t *)VarIn);
                break;
            case TYPE_SINT:
                Var = (float)(*(int8_t *)VarIn);
                break;
            case TYPE_INT:
                Var = (float)(*(int16_t *)VarIn);
                break;
            case TYPE_DINT:
                Var = (float)(*(int32_t *)VarIn);
                break;
            case TYPE_LINT:
                Var = (float)(*(int64_t *)VarIn);
                break;
            case TYPE_FLOAT:
                Var = (*(float *)VarIn);
                break;
            case TYPE_DOUBLE:
                Var = (float)(*(double *)VarIn);
                break;
            default:
                return (BIT_FALSE);
        }
        return (REG_CopyReg(RegIn, DstIn, &Var));
    }
    return (BIT_FALSE);
}

static uint8_t REG_CopyRegDouble(REG_t *RegIn, uint8_t DstIn, const void *VarIn, uint8_t VarTypeIn)
{
    double Var;

    if(RegIn && VarIn)
    {
        switch(VarTypeIn)
        {
            case TYPE_BYTE:
                Var = (double)(*(uint8_t *)VarIn);
                break;
            case TYPE_WORD:
                Var = (double)(*(uint16_t *)VarIn);
                break;
            case TYPE_DWORD:
                Var = (double)(*(uint32_t *)VarIn);
                break;
            case TYPE_LWORD:
                Var = (double)(*(uint64_t *)VarIn);
                break;
            case TYPE_SINT:
                Var = (double)(*(int8_t *)VarIn);
                break;
            case TYPE_INT:
                Var = (double)(*(int16_t *)VarIn);
                break;
            case TYPE_DINT:
                Var = (double)(*(int32_t *)VarIn);
                break;
            case TYPE_LINT:
                Var = (double)(*(int64_t *)VarIn);
                break;
            case TYPE_FLOAT:
                Var = (double)(*(float *)VarIn);
                break;
            case TYPE_DOUBLE:
                Var = (*(double *)VarIn);
                break;
            default:
                return (BIT_FALSE);
        }
        return (REG_CopyReg(RegIn, DstIn, &Var));
    }
    return (BIT_FALSE);
}

/** @brief  Copy any numeric value to single register.
 *  @param  RegIn     - pointer to register.
 *  @param  DstIn - destination of copy (reg.h):
 *  @arg      = REG_COPY_APP_TO_MB
 *  @arg      = REG_COPY_APP_TO_MB__NO_MON
 *  @arg      = REG_COPY_MB_TO_APP
 *  @arg      = REG_COPY_MB_TO_VAR
 *  @arg      = REG_COPY_VAR_TO_APP
 *  @arg      = REG_COPY_VAR_TO_MB
 *  @arg      = REG_COPY_VAR_TO_MB__NO_MON
 *  @arg      = REG_COPY_VAR_TO_ALL
 *  @arg      = REG_COPY_VAR_TO_ALL__NO_MON
 *  @param  VarIn     - pointer to Variable.
 *  @param  VarTypeIn - type of Variable:
 *  @arg      = TYPE_BYTE
 *            = TYPE_WORD
 *            = TYPE_DWORD
 *            = TYPE_LWORD
 *            = TYPE_SINT
 *            = TYPE_INT
 *            = TYPE_DINT
 *            = TYPE_LINT
 *            = TYPE_FLOAT
 *            = TYPE_DOUBLE
 *  @return Result:
 *  @arg      = 0 - error
 *  @arg      = 1 - OK
 */
uint8_t REG_CopyVar(REG_t *RegIn, uint8_t DstIn, const void *VarIn, uint8_t VarTypeIn)
{
    if(RegIn && VarIn)
    {
        switch(RegIn->Type)
        {
            case TYPE_BYTE:
                return (REG_CopyRegByte(RegIn, DstIn, VarIn, VarTypeIn));
            case TYPE_WORD:
                return (REG_CopyRegWord(RegIn, DstIn, VarIn, VarTypeIn));
            case TYPE_DWORD:
                return (REG_CopyRegDWord(RegIn, DstIn, VarIn, VarTypeIn));
            case TYPE_LWORD:
                return (REG_CopyRegLWord(RegIn, DstIn, VarIn, VarTypeIn));
            case TYPE_SINT:
                return (REG_CopyRegSInt(RegIn, DstIn, VarIn, VarTypeIn));
            case TYPE_INT:
                return (REG_CopyRegInt(RegIn, DstIn, VarIn, VarTypeIn));
            case TYPE_DINT:
                return (REG_CopyRegDInt(RegIn, DstIn, VarIn, VarTypeIn));
            case TYPE_LINT:
                return (REG_CopyRegLInt(RegIn, DstIn, VarIn, VarTypeIn));
            case TYPE_FLOAT:
                return (REG_CopyRegFloat(RegIn, DstIn, VarIn, VarTypeIn));
            case TYPE_DOUBLE:
                return (REG_CopyRegDouble(RegIn, DstIn, VarIn, VarTypeIn));
        }
    }
    return (BIT_FALSE);
}


/** @brief  Copy single register (by register position in REGS).
 *  @param  RegPosIn - position of register in REGS.
 *  @param  DstIn - destination of copy (reg.h):
 *  @arg      = REG_COPY_APP_TO_MB
 *  @arg      = REG_COPY_APP_TO_MB__NO_MON
 *  @arg      = REG_COPY_MB_TO_APP
 *  @arg      = REG_COPY_MB_TO_VAR
 *  @arg      = REG_COPY_VAR_TO_APP
 *  @arg      = REG_COPY_VAR_TO_MB
 *  @arg      = REG_COPY_VAR_TO_MB__NO_MON
 *  @arg      = REG_COPY_VAR_TO_ALL
 *  @arg      = REG_COPY_VAR_TO_ALL__NO_MON
 *  @param  VarIn - pointer to Variable or 0.
 *  @return Result:
 *  @arg      = 0 - error
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 */
uint8_t REG_CopyRegByPos(uint16_t RegPosIn, uint8_t DstIn, void *VarIn)
{
	REG_t *Reg = REG_GetByIDx(RegPosIn);
    return (REG_CopyReg(Reg, DstIn, VarIn));
}


/** @brief  Copy group of registers.
 *  @param  PosIn - register position in REGS.
 *  @param  SzIn  - number of registers to copy.
 *  @param  DstIn - destination of copy (reg.h):
 *  @arg      = REG_COPY_APP_TO_MB
 *  @arg      = REG_COPY_APP_TO_MB__NO_MON
 *  @arg      = REG_COPY_MB_TO_APP
 *  @arg      = REG_COPY_MB_TO_VAR
 *  @arg      = REG_COPY_VAR_TO_APP
 *  @arg      = REG_COPY_VAR_TO_MB
 *  @arg      = REG_COPY_VAR_TO_MB__NO_MON
 *  @arg      = REG_COPY_VAR_TO_ALL
 *  @arg      = REG_COPY_VAR_TO_ALL__NO_MON
 *  @param  VarIn - pointer to Variable or 0.
 *  @return The number of copied registers.
 */
uint16_t REG_CopyRegs(uint16_t PosIn, uint16_t SzIn, uint8_t DstIn, void *VarIn)
{
    uint16_t PosEnd = PosIn + SzIn - 1;
    uint16_t Res = 0, i = 0;
    REG_t   *Reg = NULL;

    if(PosIn < REG_SZ && SzIn > 0 && PosEnd < REG_SZ)
    {
        for(i=PosIn; i<=PosEnd; i++)
        {
        	Reg = REG_GetByIDx(i);
            Res+= REG_CopyReg(Reg, DstIn, VarIn);
        }
    }
    return (Res);
}



/** @brief  Test Position of Data Table.
 *  @param  TableIn - table ID (reg-map.h)
 *  @param  PosIn   - position.
 *  @param  WSzIn   - size of words for value:
 *  @arg       =1 - for Bool-table
 *  @arg      >=1 - for Numeric-table (ex.: 2 words for FLOAT)
 *  @return Pointer to register or 0 (if table or position is not supported)
 */
static void *REG_TestDataTablePos(uint8_t TableIn, uint16_t PosIn, uint8_t WSzIn)
{
    uint16_t PosEnd = 0;

    if(WSzIn > 0)
    {
        PosEnd = (PosIn + WSzIn - 1);

        switch(TableIn)
        {
            case REG_DATA_BOOL_TABLE_ID:
                if(PosIn < REG_DATA_BOOL_SZ && PosEnd < REG_DATA_BOOL_SZ)
                {
                    return ((void *)&REGS_DATA_BOOL[PosIn]);
                }
                break;

            case REG_DATA_NUMB_TABLE_ID:
                if(PosIn < REG_DATA_NUMB_SZ && PosEnd < REG_DATA_NUMB_SZ)
                {
                    return ((void *)&REGS_DATA_NUMB[PosIn]);
                }
                break;
        }
    }
    return (0);
}

/** @brief  Init. group of registers in REGS.
 *  @param  GIDIn        - Unique ID of group/subgroup.
 *  @param  ZoneIn       - Zone ID.
 *  @param  TypeSzIn     - Data Type Size ID.
 *  @param  GroupIn      - Group ID.
 *  @param  TypeIn       - Data Type ID.
 *  @param  PosIn        - Start position in REGS (offset).
 *  @param  SzIn         - Number of registers.
 *  @param  SaddrIn      - Start register address.
 *  @param  MbTableIn    - ModBus Table ID.
 *  @param  MbPosIn      - Start position in ModBus table (offset).
 *  @param  A00In        - Value of a_data[0] (<0 - not used; ex. -10 - use calculated register address).
 *  @param  A01In        - Value of a_data[1] (<0 - not used; ex. -10 - use calculated register address).
 *  @param  A02In        - Value of a_data[2] (<0 - not used; ex. -10 - use calculated register address).
 *  @param  DataTableIn  - Data Table ID.
 *  @param  DataPosIn    - Start position in Data table (offset).
*  @param  RetainIn     - Retain (EEPROM):
 *  @arg                   = -1 - all registers of the group
 *  @arg                   = 0  - not retain
 *  @arg                   > 0  - quantity of retain registers in the group
 *  @param  TitleIn      - String title.
 *  @return The number of inited registers.
 */
uint16_t REG_InitRegs(uint16_t GIDIn, uint8_t ZoneIn, uint8_t TypeSzIn, uint16_t GroupIn, uint8_t TypeIn, uint16_t PosIn, uint16_t SzIn, uint16_t SaddrIn, uint8_t MbTableIn, uint16_t MbPosIn, int32_t A00In, int32_t A01In, int32_t A02In, uint8_t DataTableIn, uint16_t DataPosIn, uint16_t RetainIn, const char *TitleIn)
{
    uint16_t PosEnd     = PosIn + SzIn - 1;
    uint16_t Addr       = SaddrIn;
    uint16_t AddrEnd    = SaddrIn + SzIn - 1;
    uint8_t  WSz        = Type_GetWSz(TypeIn);
    uint16_t Res        = 0, i = 0;
    REG_t   *Reg        = REGS;
    uint16_t DataAddr   = DataPosIn;

    /* @TODO Add Addresses of Retain Registers
    uint16_t AddEndrRetain = 0;

    if(RetainIn != REG_RETAIN_NONE)
    {
    	AddrRetain = ((RetainIn == REG_RETAIN_ALL) ? AddrEnd : (Addr+RetainIn-1));
    }
    */
    (void)TitleIn;
    (void)RetainIn;

#ifdef RTE_MOD_APP
    int32_t  A00, A01, A02;
#else
    (void)A00In;
    (void)A01In;
    (void)A02In;
    (void)ZoneIn;
    (void)TypeSzIn;
#endif // RTE_MOD_APP

#ifdef DEBUG_LOG_REG
    char Zone[3]      = {'I', 'M', 'Q'};
    char TypeSz[5]    = {'X', 'B', 'W', 'D', 'L'};
    char MbTable[7]   = {'*', 'C', 'D', 'H', 'I', 'd', 'h'};
    char DataTable[3] = {'*', 'B', 'N'};
#endif // DEBUG_LOG_REG

    //Test position, size and address
    if(PosIn < REG_SZ && SzIn > 0 && PosEnd < REG_SZ && SaddrIn < REG_ADDR_MAX && AddrEnd < REG_ADDR_MAX && WSz > 0)
    {
#ifdef DEBUG_LOG_REG
        DebugLog("Reg: (OK)\n");
#endif // DEBUG_LOG_REG

        for(i=PosIn; i<=PosEnd; i++, Addr++, Res++)
        {
#ifdef RTE_MOD_APP
            A00 = ((A00In == REG_AXX_ADDR) ? (int32_t)Addr : A00In);
            A01 = ((A01In == REG_AXX_ADDR) ? (int32_t)Addr : A01In);
            A02 = ((A02In == REG_AXX_ADDR) ? (int32_t)Addr : A02In);
#endif // RTE_MOD_APP

            (Reg+i)->GroupID   = GroupIn;
            (Reg+i)->GID       = GIDIn;
            (Reg+i)->iReg      = i;
            (Reg+i)->iGroup    = Addr;
            (Reg+i)->Type      = TypeIn;
            (Reg+i)->Wsz       = WSz;

            DataAddr           = REG_CALC_MBADDR(Addr, WSz, DataPosIn);
            (Reg+i)->DataTable = DataTableIn;
            (Reg+i)->pMbVar    = REG_TestDataTablePos(DataTableIn, DataAddr, WSz);

#ifdef RTE_MOD_APP
            (Reg+i)->pAppVar   = PlcApp_TestLocVar(ZoneIn, TypeSzIn, GroupIn, A00, A01, A02);
#endif // RTE_MOD_APP

            (Reg+i)->MbTable   = MbTableIn;
            (Reg+i)->MbAddr    = REG_CALC_MBADDR(Addr, WSz, MbPosIn);

            //@TODO Add Addresses of Retain Registers
            //      ...
            (Reg+i)->Retain    = REG_RETAIN_NONE;

            Res++;

#ifdef RTE_MOD_LED_START
            if((Reg+i)->EeAddr > PLC_EEPROM_ADDR_NONE)
            {
                //LED Link/Start (blink)
                PlcDO_Toggle(PLC_LED_PORT, PLC_LED1_PIN, PLC_LED1_PIN_MODE);
                DelayMs(10);
            }
#endif // RTE_MOD_LED_START

#ifdef DEBUG_LOG_REG
            if(i == PosIn || i == PosEnd)
            {
                DebugLog("[%d] %c%c%d.", i, Zone[ZoneIn], TypeSz[TypeSzIn], GroupIn);

                if(A00In > REG_AXX_NONE)
                     DebugLog("%d.", A00In);
                else if(A00In == REG_AXX_ADDR)
                     DebugLog("%d.", Addr);

                if(A01In > REG_AXX_NONE)
                     DebugLog("%d.", A01In);
                else if(A01In == REG_AXX_ADDR)
                     DebugLog("%d.", Addr);

                if(A02In > REG_AXX_NONE)
                     DebugLog("%d", A02In);
                else if(A02In == REG_AXX_ADDR)
                     DebugLog("%d", Addr);

                DebugLog(" DTable=%c DAddr=%d pMbVar=%d", DataTable[DataTableIn], DataAddr, (Reg+i)->pMbVar);
                DebugLog(" MbTable=%c MbAddr=%d", MbTable[MbTableIn], (Reg+i)->MbAddr);
#ifdef RTE_MOD_APP
                if((Reg+i)->pAppVar) DebugLog(" pAppVar=%d", (Reg+i)->pAppVar);
#endif // RTE_MOD_APP

                DebugLog(" EE=%d\n", (Reg+i)->Retain);
            }
#endif // DEBUG_LOG_REG
        }
    }
    else
    {
#ifdef DEBUG_LOG_REG
        DebugLog("Reg: (Error): %c%c%d_%d.%d.%d(%d). start=%d end=%d\n", Zone[ZoneIn], TypeSz[TypeSzIn], GroupIn, A00In, A01In, A02In, PosIn, PosEnd);
#endif // DEBUG_LOG_REG
    }

    return (Res);
}


/** @brief  Clear Data Tables.
 *  @param  None.
 *  @return None.
 */
void REG_Clear(void)
{
    Type_InitBytes(REGS_DATA_BOOL, REG_DATA_BOOL_SZ, 0);
    Type_InitWords(REGS_DATA_NUMB, REG_DATA_NUMB_SZ, 0);
}
