/* @page mbrtu.c
 *       ModBus RTU Slave driver
 *       2020-2023
 */

#include "proto-mbrtu.h"


/** @brief  Init. interface context by default.
 *  @param  MBRTUIn  - pointer to interface context.
 *  @param  SlaveIn  - slave ID.
 *  @return None.
 */
void MBRTU_InitDef(MBRTU_t *MBRTUIn, const uint8_t SlaveIn)
{
    if(MBRTUIn)
    {
        MBRTUIn->Settings.BaudRate  = MBRTU_BAUDRATE_115200;
        MBRTUIn->Settings.DataBits  = MBRTU_DATA_BITS_8;
        MBRTUIn->Settings.Parity    = MBRTU_PARITY_NONE;
        MBRTUIn->Settings.StopBits  = MBRTU_STOP_BITS_1;
        MBRTUIn->Settings.Mode      = MBRTU_MODE_SLAVE;
        MBRTUIn->Settings.ByteOrder = MBRTU_BYTE_ORDER_1032;

        MBRTUIn->SlaveID 			= SlaveIn;

        //Rx
        MBRTUIn->RxCnt       		= 0;
        MBRTUIn->RxFunc      		= 0;
        MBRTUIn->RxStartAddr 		= 0;
        MBRTUIn->RxEndAddr   		= 0;
        MBRTUIn->RxNumRegs   		= 0;
        MBRTUIn->RxNumBytes  		= 0;
        MBRTUIn->RxSubFunc   		= 0;
        MBRTUIn->RxExc       		= MBRTU_EXC_OK;
        MBRTUIn->RxBuffOver  		= 0;
        MBRTUIn->RxQueueOver 		= 0;

        MBRTUIn->cBusExcErr  		= 0;
        MBRTUIn->cBusComErr  		= 0;
        MBRTUIn->cRes        		= 0;
        MBRTUIn->cNoRes      		= 0;
        MBRTUIn->cRxQueueErr 		= 0;

        MBRTUIn->TxCnt       		= 0;

        MBRTUIn->RxTx        		= MBRTU_FREE;
    }
}


/** @brief  Calculate CRC16 for frame.
 *  @param  FrameIn   - pointer to frame-buffer.
 *  @param  FrameSzIn - size of frame-buffer (without CRC bytes).
 *  @return CRC16.
 */
uint16_t MBRTU_CalcCRC16(const uint8_t *FrameIn, uint8_t FrameSzIn)
{
    uint16_t CRC16 = 0xffff, i, j, CarryFlag, a;

    if(FrameIn && FrameSzIn > 0)
    {
        for(i=0; i<FrameSzIn; i++)
        {
            CRC16 = CRC16^FrameIn[i];

            for(j=0; j<8; j++)
            {
                a = CRC16;
                CarryFlag = a&0x0001;
                CRC16 = CRC16>>1;
                if(CarryFlag==1) CRC16 = CRC16^0xa001;
            }
        }
    }

    return (CRC16);
}


/** @brief  Test Slave ID.
 *  @param  Slave1In - target slave ID.
 *  @param  Slave2In - correct slave ID.
 *  @return Result code:
 *  @arg     = 0 - target slave ID is incorrect
 *  @arg     = 1 - target slave ID is correct
 */
inline uint8_t MBRTU_TestSlaveID(uint8_t Slave1In, uint8_t Slave2In)
{
    return (uint8_t)((Slave1In != Slave2In) ? 0 : 1);
}

/** @brief  Test Table ID.
 *  @param  TableIn - table ID.
 *  @return Result code:
 *  @arg     =0 - table is not supported
 *  @arg    >=1 - table is supported (size of table)
 */
uint16_t MBRTU_TestTable(uint8_t TableIn)
{
    switch(TableIn)
    {
#if defined(MBRTU_COIL_READ_ALLOW) || defined(MBRTU_COIL_WRITE_ALLOW)
        case MBRTU_COIL_TABLE_ID:
            return (MBRTU_COIL_SZ);
#endif // MBRTU_COIL_READ_ALLOW || MBRTU_COIL_WRITE_ALLOW

#ifdef MBRTU_DISC_READ_ALLOW
        case MBRTU_DISC_TABLE_ID:
            return (MBRTU_DISC_SZ);
#endif // MBRTU_DISC_READ_ALLOW

#if defined(MBRTU_HOLD_READ_ALLOW) || defined(MBRTU_HOLD_WRITE_ALLOW)
        case MBRTU_HOLD_TABLE_ID:
            return (MBRTU_HOLD_SZ);
#endif // MBRTU_HOLD_READ_ALLOW || MBRTU_HOLD_WRITE_ALLOW

#ifdef MBRTU_INPT_READ_ALLOW
        case MBRTU_INPT_TABLE_ID:
            return (MBRTU_INPT_SZ);
#endif // MBRTU_INPT_READ_ALLOW

        default:
            break;
    }

    return (uint16_t)(0);
}

/** @brief  Test Function code.
 *  @param  FuncIn - function code.
 *  @return Result code:
 *  @arg     = 0 - function is not supported
 *  @arg     = 1 - function is supported
 */
uint8_t MBRTU_TestFunc(uint8_t FuncIn)
{
    switch(FuncIn)
    {
#ifdef MBRTU_COIL_READ_ALLOW
        case MBRTU_FUNC_01:
            return (uint8_t)(1);
#endif // MBRTU_COIL_READ_ALLOW

#ifdef MBRTU_DISC_READ_ALLOW
        case MBRTU_FUNC_02:
            return (uint8_t)(1);
#endif // MBRTU_DISC_READ_ALLOW

#ifdef MBRTU_HOLD_READ_ALLOW
        case MBRTU_FUNC_03:
            return (uint8_t)(1);
#endif // MBRTU_HOLD_READ_ALLOW

#ifdef MBRTU_INPT_READ_ALLOW
        case MBRTU_FUNC_04:
            return (uint8_t)(1);
#endif // MBRTU_INPT_READ_ALLOW

#ifdef MBRTU_COIL_WRITE_ALLOW
        case MBRTU_FUNC_05:
        case MBRTU_FUNC_15:
            return (uint8_t)(1);
#endif // MBRTU_COIL_WRITE_ALLOW

#ifdef MBRTU_HOLD_WRITE_ALLOW
        case MBRTU_FUNC_06:
        case MBRTU_FUNC_16:
            return (uint8_t)(1);
#endif // MBRTU_HOLD_WRITE_ALLOW

#ifdef MBRTU_DIAG_ALLOW
        case MBRTU_FUNC_08:
            return (uint8_t)(1);
#endif // MBRTU_DIAG_ALLOW

        default:
            break;
    }
    return (uint8_t)(0);
}

/** @brief  Test CRC.
 *  @param  FrameIn   - pointer to frame-buffer.
 *  @param  FrameSzIn - size of frame-buffer.
 *  @param  HiIn - Hi-byte of target CRC.
 *  @param  LoIn - Lo-byte of target CRC.
 *  @return Result code:
 *  @arg     = 0 - CRC is incorrect
 *  @arg     = 1 - CRC is correct
 */
uint8_t MBRTU_TestCRC16(const uint8_t *FrameIn, uint8_t FrameSzIn, uint8_t HiIn, uint8_t LoIn)
{
    uint16_t CRC16 = MBRTU_CalcCRC16(FrameIn, FrameSzIn);
    return (uint8_t)((CRC16 != MERGE_WORD(LoIn, HiIn)) ? 0 : 1);
}


/** @brief  Parse request.
 *  @param  MBRTUIn - pointer to Data structure.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *             MBRTUIn->RxCnt   (test)
 *           ~ MBRTUIn->RxExc   (set)
 *           ~ MBRTUIn->RxFunc  (set)
 *             MBRTUIn->SlaveID
 *             MBRTUIn->RxBuff
 */
uint8_t MBRTU_ParseReq(MBRTU_t *MBRTUIn)
{
    if(MBRTUIn)
    {
        if(MBRTUIn->RxCnt >= MBRTU_ADU_MIN_SZ)
        {
            // Test SlaveID
            if(!MBRTU_TestSlaveID(MBRTUIn->RxBuff[MBRTU_ADU_SLAVE_POS], MBRTUIn->SlaveID))
            {
                MBRTUIn->RxExc = MBRTU_EXC_SLAVE_ERR;
                return (MBRTU_EXC_SLAVE_ERR);
            }

            // Test Rx-buffer overflow (in USART.IRQ.RXNE)
            if(MBRTUIn->RxBuffOver != BIT_FALSE)
            {
                MBRTUIn->RxExc = MBRTU_EXC_DATA_ERR;
                return (MBRTU_EXC_DATA_ERR);
            }

            //Test CRC
            if(!MBRTU_TestCRC16(MBRTUIn->RxBuff, (MBRTUIn->RxCnt-MBRTU_ADU_CRC_SZ), MBRTUIn->RxBuff[MBRTUIn->RxCnt-1], MBRTUIn->RxBuff[MBRTUIn->RxCnt-2]))
            {
                MBRTUIn->RxExc = MBRTU_EXC_CRC_ERR;
                return (MBRTU_EXC_CRC_ERR);
            }

            // Set RxFunc (in USART.IRQ.RXNE)
            MBRTUIn->RxFunc = MBRTUIn->RxBuff[MBRTU_EXC_FUNC_ERR];

            return (MBRTU_EXC_OK);
        }
        else
        {
            MBRTUIn->RxExc = MBRTU_EXC_APU_ERR;
            return (MBRTU_EXC_APU_ERR);
        }
    }
    return (MBRTU_EXC_NONRECOV_ERR);
}


/** @brief  Create response header.
 *  @param  MBRTUIn   - pointer to Data structure.
 *  @param  ExcModeIn - exception mode:
 *  @arg     = 0 - normal response,
 *  @arg     = 1 - error response,
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->TxCnt  (set, must be set to 0 before using here!)
 *           ~ MBRTUIn->TxBuff (set)
 *             MBRTUIn->RxFunc
 *             MBRTUIn->SlaveID
 */
uint8_t MBRTU_CreateResHeader(MBRTU_t *MBRTUIn, uint8_t ExcModeIn)
{
    if(MBRTUIn)
    {
        //+ Slave ID
        MBRTUIn->TxBuff[MBRTUIn->TxCnt] = MBRTUIn->SlaveID;
        MBRTUIn->TxCnt++;
        //+ Func
        MBRTUIn->TxBuff[MBRTUIn->TxCnt] = ((ExcModeIn == MBRTU_RESPONSE_EXC) ? (MBRTU_FUNC_ERR_PRE|MBRTUIn->RxFunc) : MBRTUIn->RxFunc);
        MBRTUIn->TxCnt++;

        return (MBRTU_EXC_OK);
    }
    return (MBRTU_EXC_NONRECOV_ERR);
}

/** @brief  Create response CRC.
 *  @param  MBRTUIn - pointer to Data structure.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->TxCnt  (set)
 *           ~ MBRTUIn->TxBuff (set)
 */
uint8_t MBRTU_CreateResCRC(MBRTU_t *MBRTUIn)
{
    uint16_t CRC16 = 0;
    uint8_t  iByte = 0;

    if(MBRTUIn)
    {
        CRC16 = MBRTU_CalcCRC16(MBRTUIn->TxBuff, MBRTUIn->TxCnt);
        for(iByte=0; iByte<2; iByte++)
        {
            //+ CRC: Lo, Hi
            MBRTUIn->TxBuff[MBRTUIn->TxCnt] = BYTE_N(CRC16, iByte);
            MBRTUIn->TxCnt++;
        }

        return (MBRTU_EXC_OK);
    }
    return (MBRTU_EXC_NONRECOV_ERR);
}

/** @brief  Create exception response.
 *  @param  MBRTUIn - pointer to Data structure.
 *  @param  ExcIn   - exception code.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->TxCnt  (set)
 *           ~ MBRTUIn->TxBuff (set)
 */
uint8_t MBRTU_CreateResExc(MBRTU_t *MBRTUIn, uint8_t ExcIn)
{
    if(MBRTUIn)
    {
        MBRTUIn->TxCnt = 0;
        //+ Header
        MBRTU_CreateResHeader(MBRTUIn, MBRTU_RESPONSE_EXC);
        //+ Exception code
        MBRTUIn->TxBuff[MBRTUIn->TxCnt] = ExcIn;
        MBRTUIn->TxCnt++;
        //+ CRC
        MBRTU_CreateResCRC(MBRTUIn);

        return (MBRTU_EXC_OK);
    }
    return (MBRTU_EXC_NONRECOV_ERR);
}


/** @brief  Test request to table of Holding registers.
 *  @param  MBRTUIn - pointer to Data structure.
 *  @param  ReqTyIn - request type:
 *  @arg      = 0 - read
 *  @arg      = 1 - write
 *  @param  ModeIn  - write mode:
 *  @arg      = 0 - single register
 *  @arg      = 1 - multiple registers
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *             MBRTUIn->RxCnt  (test)
 *           ~ MBRTUIn->RxExc  (set)
 */
uint8_t MBRTU_TestHoldReq(MBRTU_t *MBRTUIn, uint8_t ReqTyIn, uint8_t ModeIn)
{
    uint8_t ReqSz = 0;

    if(MBRTUIn)
    {
        if(ReqTyIn == MBRTU_REQUEST_READ)
        {
            ReqSz = MBRTU_HOLD_READ_REQUEST_SZ;
        }
        else
        {
            ReqSz = ((ModeIn == MBRTU_WRITE_SINGLE) ? MBRTU_HOLD_SWRITE_REQUEST_SZ : MBRTU_HOLD_MWRITE_REQUEST_SZ);
        }

        MBRTUIn->RxExc = ((MBRTUIn->RxCnt < ReqSz) ? MBRTU_EXC_DATA_ERR : MBRTU_EXC_OK);
        return (MBRTUIn->RxExc);
    }
    return (MBRTU_EXC_NONRECOV_ERR);
}

/** @brief  Test quantity of Holding registers.
 *  @param  MBRTUIn - pointer to Data structure.
 *  @param  ReqTyIn - request type:
 *  @arg      = 0 - read
 *  @arg      = 1 - write (multiple)
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->RxNumRegs (set, test)
 *           ~ MBRTUIn->RxExc     (set)
 *             MBRTUIn->RxBuff
 */
uint8_t MBRTU_TestHoldNRegs(MBRTU_t *MBRTUIn, uint8_t ReqTyIn)
{
    uint16_t NRegsMin = 0, NRegsMax = 0;

    if(MBRTUIn)
    {
        NRegsMin = ((ReqTyIn == MBRTU_REQUEST_READ) ? MBRTU_HOLD_READ_NREGS_MIN : MBRTU_HOLD_WRITE_NREGS_MIN);
        NRegsMax = ((ReqTyIn == MBRTU_REQUEST_READ) ? MBRTU_HOLD_READ_NREGS_MAX : MBRTU_HOLD_WRITE_NREGS_MAX);

        //Hi, Lo
        MBRTUIn->RxNumRegs = MERGE_WORD(MBRTUIn->RxBuff[MBRTU_APU_HOLD_NREGS_POS+1], MBRTUIn->RxBuff[MBRTU_APU_HOLD_NREGS_POS]);
        MBRTUIn->RxExc     = (!(VAL_IN_LIMITS(NRegsMin, MBRTUIn->RxNumRegs, NRegsMax)) ? MBRTU_EXC_DATA_ERR : MBRTU_EXC_OK);
        return (MBRTUIn->RxExc);
    }
    return (MBRTU_EXC_NONRECOV_ERR);
}

/** @brief  Test quantity of bytes data for multiple write (Holding).
 *  @param  MBRTUIn - pointer to Data structure.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->RxNumBytes (set, test)
 *             MBRTUIn->RxBuff     (used)
 *           ~ MBRTUIn->RxExc      (set)
 */
uint8_t MBRTU_TestHoldNBytes(MBRTU_t *MBRTUIn)
{
    if(MBRTUIn)
    {
        MBRTUIn->RxNumBytes = MBRTUIn->RxBuff[MBRTU_APU_HOLD_NBYTES_POS];
        MBRTUIn->RxExc      = ((MBRTUIn->RxNumBytes != (MBRTUIn->RxCnt-MBRTU_ADU_CONST_SZ)) ? MBRTU_EXC_DATA_ERR : MBRTU_EXC_OK);
        return (MBRTUIn->RxExc);
    }
    return (MBRTU_EXC_NONRECOV_ERR);
}

/** @brief  Test addresses of Holding registers.
 *  @param  MBRTUIn - pointer to Data structure.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->RxStartAddr (set)
 *           ~ MBRTUIn->RxEndAddr   (set)
 *           ~ MBRTUIn->RxExc       (set)
 *             MBRTUIn->RxNumRegs
 *             MBRTUIn->RxBuff
 */
uint8_t MBRTU_TestHoldAddr(MBRTU_t *MBRTUIn)
{
    if(MBRTUIn)
    {
        //Hi, Lo
        MBRTUIn->RxStartAddr = MERGE_WORD(MBRTUIn->RxBuff[MBRTU_APU_HOLD_ADDR_POS+1], MBRTUIn->RxBuff[MBRTU_APU_HOLD_ADDR_POS]);
        MBRTUIn->RxEndAddr   = (MBRTUIn->RxStartAddr+MBRTUIn->RxNumRegs-1);
        MBRTUIn->RxExc       = (!(VAL_IN_LIMITS(MBRTU_HOLD_START, MBRTUIn->RxStartAddr, MBRTU_HOLD_END) && VAL_IN_LIMITS(MBRTU_HOLD_START, MBRTUIn->RxEndAddr, MBRTU_HOLD_END)) ? MBRTU_EXC_ADDR_ERR : MBRTU_EXC_OK);
        return (MBRTUIn->RxExc);
    }
    return (MBRTU_EXC_NONRECOV_ERR);
}

/** @brief  Test request to table of Input registers.
 *  @param  MBRTUIn - pointer to Data structure.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *             MBRTUIn->RxCnt  (test)
 *           ~ MBRTUIn->RxExc  (set)
 */
uint8_t MBRTU_TestInptReq(MBRTU_t *MBRTUIn)
{
    if(MBRTUIn)
    {
        MBRTUIn->RxExc = ((MBRTUIn->RxCnt < MBRTU_INPT_READ_REQUEST_SZ) ? MBRTU_EXC_DATA_ERR : MBRTU_EXC_OK);
        return (MBRTUIn->RxExc);
    }
    return (MBRTU_EXC_NONRECOV_ERR);
}

/** @brief  Test quantity of Input registers.
 *  @param  MBRTUIn - pointer to Data structure.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->RxNumRegs (set, test)
 *           ~ MBRTUIn->RxExc     (set)
 *             MBRTUIn->RxBuff
 */
uint8_t MBRTU_TestInptNRegs(MBRTU_t *MBRTUIn)
{
    if(MBRTUIn)
    {
        //Hi, Lo
        MBRTUIn->RxNumRegs = MERGE_WORD(MBRTUIn->RxBuff[MBRTU_APU_INPT_NREGS_POS+1], MBRTUIn->RxBuff[MBRTU_APU_INPT_NREGS_POS]);
        MBRTUIn->RxExc     = (!(VAL_IN_LIMITS(MBRTU_INPT_READ_NREGS_MIN, MBRTUIn->RxNumRegs, MBRTU_INPT_READ_NREGS_MAX)) ? MBRTU_EXC_DATA_ERR : MBRTU_EXC_OK);
        return (MBRTUIn->RxExc);
    }
    return (MBRTU_EXC_NONRECOV_ERR);
}

/** @brief  Test addresses of Input registers.
 *  @param  MBRTUIn - pointer to Data structure.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->RxStartAddr (set)
 *           ~ MBRTUIn->RxEndAddr   (set)
 *           ~ MBRTUIn->RxExc       (set)
 *             MBRTUIn->RxNumRegs
 *             MBRTUIn->RxBuff
 */
uint8_t MBRTU_TestInptAddr(MBRTU_t *MBRTUIn)
{
    if(MBRTUIn)
    {
        //Hi, Lo
        MBRTUIn->RxStartAddr = MERGE_WORD(MBRTUIn->RxBuff[MBRTU_APU_INPT_ADDR_POS+1], MBRTUIn->RxBuff[MBRTU_APU_INPT_ADDR_POS]);
        MBRTUIn->RxEndAddr   = (MBRTUIn->RxStartAddr+MBRTUIn->RxNumRegs-1);
        MBRTUIn->RxExc       = (!(VAL_IN_LIMITS(MBRTU_INPT_START, MBRTUIn->RxStartAddr, MBRTU_INPT_END) && VAL_IN_LIMITS(MBRTU_INPT_START, MBRTUIn->RxEndAddr, MBRTU_INPT_END)) ? MBRTU_EXC_ADDR_ERR : MBRTU_EXC_OK);
        return (MBRTUIn->RxExc);
    }
    return (MBRTU_EXC_NONRECOV_ERR);
}


/** @brief  Handler of request to read numeric registers (Holding or Inputs).
 *  @param  MBRTUIn - pointer to Data structure.
 *  @param  TableIn - ModBus Table ID.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->RxExc     (set)
 *           ~ MBRTUIn->TxCnt     (set, 0, ++)
 *           ~ MBRTUIn->TxBuff    (set)
 *             MBRTUIn->RxNumRegs
 *             MBRTUIn->RxStartAddr
 *             MBRTUIn->RxEndAddr
 */
uint8_t MBRTU_ReadRegs(MBRTU_t *MBRTUIn, uint8_t TableIn)
{
    REG_t   *Reg;
    uint16_t iAddr;
    uint8_t  i, RegWsz;

    if(MBRTUIn)
    {
        //Test request size
        if(TableIn == MBRTU_HOLD_TABLE_ID) MBRTU_TestHoldReq(MBRTUIn, MBRTU_REQUEST_READ, 0);
        else MBRTU_TestInptReq(MBRTUIn);
        if(MBRTUIn->RxExc != MBRTU_EXC_OK) return (MBRTUIn->RxExc);

        //Test quantity of registers
        if(TableIn == MBRTU_HOLD_TABLE_ID) MBRTU_TestHoldNRegs(MBRTUIn, MBRTU_REQUEST_READ);
        else MBRTU_TestInptNRegs(MBRTUIn);
        if(MBRTUIn->RxExc != MBRTU_EXC_OK) return (MBRTUIn->RxExc);

        //Test start and end register addresses
        if(TableIn == MBRTU_HOLD_TABLE_ID) MBRTU_TestHoldAddr(MBRTUIn);
        else MBRTU_TestInptAddr(MBRTUIn);
        if(MBRTUIn->RxExc != MBRTU_EXC_OK) return (MBRTUIn->RxExc);

        //Create response
        MBRTUIn->TxCnt = 0;
        //+ Header
        MBRTU_CreateResHeader(MBRTUIn, MBRTU_RESPONSE_NORMAL);
        //+ Byte count
        MBRTUIn->TxBuff[MBRTUIn->TxCnt] = MBRTUIn->RxNumRegs*2;
        MBRTUIn->TxCnt++;

        iAddr = MBRTUIn->RxStartAddr;
        Type_InitWords(MBRTUIn->DataBuff, TYPE_DOUBLE_WSZ, 0);

        while(iAddr<=MBRTUIn->RxEndAddr)
        {
            Reg = REG_GetByMbAddr(TableIn, iAddr);

            if(Reg)
            {
                RegWsz = Reg->Wsz;
                //read from REG_t to DataBuff (+ encode byte order)
                if(MBRTUIn->Settings.ByteOrder == MBRTU_BYTE_ORDER_0123)
                     REG_CopyWordsFromMb(Reg, MBRTUIn->DataBuff, TYPE_DOUBLE_WSZ, MBRTU_BYTE_ORDER_1032, BIT_FALSE);
                else REG_CopyWordsFromMb(Reg, MBRTUIn->DataBuff, TYPE_DOUBLE_WSZ, MBRTUIn->Settings.ByteOrder, BIT_FALSE);
            }
            else
            {
                RegWsz = TYPE_WORD_WSZ;
            }

            for(i=0; i<RegWsz; i++)
            {
                //if incompleted data
                if(iAddr > MBRTUIn->RxEndAddr)
                {
                    MBRTUIn->RxExc = MBRTU_EXC_DATA_ERR;
                    return (MBRTUIn->RxExc);
                }
                //set Tx
                MBRTUIn->TxBuff[MBRTUIn->TxCnt] = BYTE0(MBRTUIn->DataBuff[i]);
                MBRTUIn->TxCnt++;
                MBRTUIn->TxBuff[MBRTUIn->TxCnt] = BYTE1(MBRTUIn->DataBuff[i]);
                MBRTUIn->TxCnt++;
                iAddr++;
            }
        }
        //+ CRC
        MBRTU_CreateResCRC(MBRTUIn);

        return (MBRTUIn->RxExc);
    }
    return (MBRTU_EXC_NONRECOV_ERR);
}


/** @brief  Handler of request to write Holding registers (single or multiple).
 *  @param  MBRTUIn - pointer to Data structure.
 *  @param  ModeIn  - write mode:
 *  @arg      = 0 - single register
 *  @arg      = 1 - multiple registers
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->RxExc       (set)
 *           ~ MBRTUIn->TxCnt       (set, 0, ++)
 *           ~ MBRTUIn->TxBuff      (set)
 *           ~ MBRTUIn->RxNumRegs   (set)
 *           ~ MBRTUIn->RxNumBytes  (set)
 */
uint8_t MBRTU_WriteHoldRegs(MBRTU_t *MBRTUIn, uint8_t ModeIn)
{
    REG_t   *Reg;
    uint16_t iAddr;
    uint8_t  iByte, iRx, i, RegWsz;

    if(MBRTUIn)
    {
        //Test request size
        MBRTU_TestHoldReq(MBRTUIn, MBRTU_REQUEST_WRITE, ModeIn);
        if(MBRTUIn->RxExc != MBRTU_EXC_OK) return (MBRTUIn->RxExc);

        if(ModeIn == MBRTU_WRITE_SINGLE)
        {
            MBRTUIn->RxNumRegs  = 1;
            MBRTUIn->RxNumBytes = 2;
        }
        else //MBRTU_WRITE_MULTIPLE
        {
            //Test quantity of registers
            MBRTU_TestHoldNRegs(MBRTUIn, MBRTU_REQUEST_WRITE);
            if(MBRTUIn->RxExc != MBRTU_EXC_OK) return (MBRTUIn->RxExc);

            //Test quantity of bytes
            MBRTU_TestHoldNBytes(MBRTUIn);
            if(MBRTUIn->RxExc != MBRTU_EXC_OK) return (MBRTUIn->RxExc);
        }

        //Test start and end register addresses
        MBRTU_TestHoldAddr(MBRTUIn);
        if(MBRTUIn->RxExc != MBRTU_EXC_OK) return (MBRTUIn->RxExc);

        //Create response
        MBRTUIn->TxCnt = 0;
        //+ Header
        MBRTU_CreateResHeader(MBRTUIn, MBRTU_RESPONSE_NORMAL);
        //+ Start register address: Hi, Lo
        MBRTUIn->TxBuff[MBRTUIn->TxCnt] = MBRTUIn->RxBuff[MBRTU_APU_HOLD_ADDR_POS];
        MBRTUIn->TxCnt++;
        MBRTUIn->TxBuff[MBRTUIn->TxCnt] = MBRTUIn->RxBuff[MBRTU_APU_HOLD_ADDR_POS+1];
        MBRTUIn->TxCnt++;
        // + Register value: Hi, Lo        (Single mode)
        // + Quantity of registers: Hi, Lo (Multiple mode)
        MBRTUIn->TxBuff[MBRTUIn->TxCnt] = MBRTUIn->RxBuff[MBRTU_APU_HOLD_NREGS_POS];
        MBRTUIn->TxCnt++;
        MBRTUIn->TxBuff[MBRTUIn->TxCnt] = MBRTUIn->RxBuff[MBRTU_APU_HOLD_NREGS_POS+1];
        MBRTUIn->TxCnt++;
        //+ CRC
        MBRTU_CreateResCRC(MBRTUIn);

        //Write received data into Data table
        iAddr  = MBRTUIn->RxStartAddr;
        iRx    = ((ModeIn == MBRTU_WRITE_SINGLE) ? MBRTU_APU_HOLD_SDATA_POS : MBRTU_APU_HOLD_MDATA_POS);

        while(iAddr<=MBRTUIn->RxEndAddr)
        {
            Reg = REG_GetByMbAddr(MBRTU_HOLD_TABLE_ID, iAddr);

            if(Reg)
            {
                RegWsz = Reg->Wsz;
            }
            else
            {
                RegWsz = TYPE_WORD_WSZ;
            }

            for(i=0; i<RegWsz; i++)
            {
                //if incompleted data
                if(iAddr > MBRTUIn->RxEndAddr)
                {
                    MBRTUIn->RxExc = MBRTU_EXC_DATA_ERR;
                    return (MBRTUIn->RxExc);
                }
                //set DataBuffer (+ merge bytes to word)
                for(iByte=0; iByte<2; iByte++)
                {
                    MBRTUIn->DataBuff[i] = WORD_SET_BYTE(MBRTUIn->DataBuff[i], MBRTUIn->RxBuff[iRx], iByte);
                    iRx++;
                }
                iAddr++;
            }

            if(Reg)
            {
                //write from DataBuff to REG_t (+ decode byte order)
#ifdef RTE_MOD_REG_MON
                if(MBRTUIn->Settings.ByteOrder == MBRTU_BYTE_ORDER_0123)
                     REG_CopyWordsToMb(Reg, MBRTUIn->DataBuff, TYPE_DOUBLE_WSZ, MBRTU_BYTE_ORDER_1032, BIT_FALSE, BIT_TRUE);
                else REG_CopyWordsToMb(Reg, MBRTUIn->DataBuff, TYPE_DOUBLE_WSZ, MBRTUIn->Settings.ByteOrder, BIT_FALSE, BIT_TRUE);
#else
                if(MBRTUIn->Settings.ByteOrder == MBRTU_BYTE_ORDER_0123)
                     REG_CopyWordsToMb(Reg, MBRTUIn->DataBuff, TYPE_DOUBLE_WSZ, MBRTU_BYTE_ORDER_1032, BIT_FALSE, BIT_FALSE);
                else REG_CopyWordsToMb(Reg, MBRTUIn->DataBuff, TYPE_DOUBLE_WSZ, MBRTUIn->Settings.ByteOrder, BIT_FALSE, BIT_FALSE);
#endif // RTE_MOD_REG_MON
            }
        }

        return (MBRTUIn->RxExc);
    }

    return (MBRTU_EXC_NONRECOV_ERR);
}


/** @brief  Test request to table of Coils.
 *  @param  MBRTUIn - pointer to Data structure.
 *  @param  ReqTyIn - request type:
 *  @arg      = 0 - read
 *  @arg      = 1 - write
 *  @param  ModeIn  - write mode:
 *  @arg      = 0 - single register
 *  @arg      = 1 - multiple registers
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *             MBRTUIn->RxCnt  (test)
 *           ~ MBRTUIn->RxExc  (set)
 */
uint8_t MBRTU_TestCoilReq(MBRTU_t *MBRTUIn, uint8_t ReqTyIn, uint8_t ModeIn)
{
    uint8_t ReqSz = 0;

    if(MBRTUIn)
    {
        if(ReqTyIn == MBRTU_REQUEST_READ)
        {
            ReqSz = MBRTU_COIL_READ_REQUEST_SZ;
        }
        else
        {
            ReqSz = ((ModeIn == MBRTU_WRITE_SINGLE) ? MBRTU_COIL_SWRITE_REQUEST_SZ : MBRTU_COIL_MWRITE_REQUEST_SZ);
        }

        MBRTUIn->RxExc = ((MBRTUIn->RxCnt < ReqSz) ? MBRTU_EXC_DATA_ERR : MBRTU_EXC_OK);
        return (MBRTUIn->RxExc);
    }
    return (MBRTU_EXC_NONRECOV_ERR);
}

/** @brief  Test quantity of Coils.
 *  @param  MBRTUIn - pointer to Data structure.
 *  @param  ReqTyIn - request type:
 *  @arg      = 0 - read
 *  @arg      = 1 - write (multiple)
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->RxNumRegs (set, test)
 *           ~ MBRTUIn->RxExc     (set)
 *             MBRTUIn->RxBuff
 */
uint8_t MBRTU_TestCoilNRegs(MBRTU_t *MBRTUIn, uint8_t ReqTyIn)
{
    uint16_t NRegsMin = 0, NRegsMax = 0;

    if(MBRTUIn)
    {
        NRegsMin = ((ReqTyIn == MBRTU_REQUEST_READ) ? MBRTU_COIL_READ_NREGS_MIN : MBRTU_COIL_WRITE_NREGS_MIN);
        NRegsMax = ((ReqTyIn == MBRTU_REQUEST_READ) ? MBRTU_COIL_READ_NREGS_MAX : MBRTU_COIL_WRITE_NREGS_MAX);

        //Hi, Lo
        MBRTUIn->RxNumRegs = MERGE_WORD(MBRTUIn->RxBuff[MBRTU_APU_COIL_NREGS_POS+1], MBRTUIn->RxBuff[MBRTU_APU_COIL_NREGS_POS]);
        MBRTUIn->RxExc     = (!(VAL_IN_LIMITS(NRegsMin, MBRTUIn->RxNumRegs, NRegsMax)) ? MBRTU_EXC_DATA_ERR : MBRTU_EXC_OK);
        return (MBRTUIn->RxExc);
    }
    return (MBRTU_EXC_NONRECOV_ERR);
}

/** @brief  Test quantity of bytes data for multiple write (Coils).
 *  @param  MBRTUIn - pointer to Data structure.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->RxNumBytes (set, test)
 *           ~ MBRTUIn->RxExc      (set)
 *             MBRTUIn->RxNumRegs
 *             MBRTUIn->RxBuff
 */
uint8_t MBRTU_TestCoilNBytes(MBRTU_t *MBRTUIn)
{
    if(MBRTUIn)
    {
        MBRTUIn->RxNumBytes = MBRTUIn->RxBuff[MBRTU_APU_COIL_NBYTES_POS];
        MBRTUIn->RxExc      = (!(MBRTUIn->RxNumBytes == (MBRTUIn->RxCnt-MBRTU_ADU_CONST_SZ) && (MBRTUIn->RxNumBytes*8) >= MBRTUIn->RxNumRegs) ? MBRTU_EXC_DATA_ERR : MBRTU_EXC_OK);
        return (MBRTUIn->RxExc);
    }
    return (MBRTU_EXC_NONRECOV_ERR);
}

/** @brief  Test addresses of Coils.
 *  @param  MBRTUIn - pointer to Data structure.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->RxStartAddr (set)
 *           ~ MBRTUIn->RxEndAddr   (set)
 *           ~ MBRTUIn->RxExc       (set)
 *             MBRTUIn->RxNumRegs
 *             MBRTUIn->RxBuff
 */
uint8_t MBRTU_TestCoilAddr(MBRTU_t *MBRTUIn)
{
    if(MBRTUIn)
    {
        //Hi, Lo
        MBRTUIn->RxStartAddr = MERGE_WORD(MBRTUIn->RxBuff[MBRTU_APU_COIL_ADDR_POS+1], MBRTUIn->RxBuff[MBRTU_APU_COIL_ADDR_POS]);
        MBRTUIn->RxEndAddr   = (MBRTUIn->RxStartAddr+MBRTUIn->RxNumRegs-1);
        MBRTUIn->RxExc       = (!(VAL_IN_LIMITS(MBRTU_COIL_START, MBRTUIn->RxStartAddr, MBRTU_COIL_END) && VAL_IN_LIMITS(MBRTU_COIL_START, MBRTUIn->RxEndAddr, MBRTU_COIL_END)) ? MBRTU_EXC_ADDR_ERR : MBRTU_EXC_OK);
        return (MBRTUIn->RxExc);
    }
    return (MBRTU_EXC_NONRECOV_ERR);
}

/** @brief  Test request to table of Dicrete inputs.
 *  @param  MBRTUIn - pointer to Data structure.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *             MBRTUIn->RxCnt  (test)
 *           ~ MBRTUIn->RxExc  (set)
 */
uint8_t MBRTU_TestDiscReq(MBRTU_t *MBRTUIn)
{
    if(MBRTUIn)
    {
        MBRTUIn->RxExc = ((MBRTUIn->RxCnt < MBRTU_DISC_READ_REQUEST_SZ) ? MBRTU_EXC_DATA_ERR : MBRTU_EXC_OK);
        return (MBRTUIn->RxExc);
    }
    return (MBRTU_EXC_NONRECOV_ERR);
}

/** @brief  Test quantity of Dicrete inputs.
 *  @param  MBRTUIn - pointer to Data structure.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->RxNumRegs (set, test)
 *           ~ MBRTUIn->RxExc     (set)
 *             MBRTUIn->RxBuff
 */
uint8_t MBRTU_TestDiscNRegs(MBRTU_t *MBRTUIn)
{
    if(MBRTUIn)
    {
        //Hi, Lo
        MBRTUIn->RxNumRegs = MERGE_WORD(MBRTUIn->RxBuff[MBRTU_APU_DISC_NREGS_POS+1], MBRTUIn->RxBuff[MBRTU_APU_DISC_NREGS_POS]);
        MBRTUIn->RxExc     = (!(VAL_IN_LIMITS(MBRTU_DISC_READ_NREGS_MIN, MBRTUIn->RxNumRegs, MBRTU_DISC_READ_NREGS_MAX)) ? MBRTU_EXC_DATA_ERR : MBRTU_EXC_OK);
        return (MBRTUIn->RxExc);
    }
    return (MBRTU_EXC_NONRECOV_ERR);
}

/** @brief  Test addresses of Dicrete inputs.
 *  @param  MBRTUIn - pointer to Data structure.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->RxStartAddr (set)
 *           ~ MBRTUIn->RxEndAddr   (set)
 *           ~ MBRTUIn->RxExc       (set)
 *             MBRTUIn->RxNumRegs
 *             MBRTUIn->RxBuff
 */
uint8_t MBRTU_TestDiscAddr(MBRTU_t *MBRTUIn)
{
    if(MBRTUIn)
    {
        //Hi, Lo
        MBRTUIn->RxStartAddr = MERGE_WORD(MBRTUIn->RxBuff[MBRTU_APU_DISC_ADDR_POS+1], MBRTUIn->RxBuff[MBRTU_APU_DISC_ADDR_POS]);
        MBRTUIn->RxEndAddr   = (MBRTUIn->RxStartAddr+MBRTUIn->RxNumRegs-1);
        MBRTUIn->RxExc       = (!(VAL_IN_LIMITS(MBRTU_DISC_START, MBRTUIn->RxStartAddr, MBRTU_DISC_END) && VAL_IN_LIMITS(MBRTU_DISC_START, MBRTUIn->RxEndAddr, MBRTU_DISC_END)) ? MBRTU_EXC_ADDR_ERR : MBRTU_EXC_OK);
        return (MBRTUIn->RxExc);
    }
    return (MBRTU_EXC_NONRECOV_ERR);
}


/** @brief  Handler of request to read dicretes (Coils or Inputs).
 *  @param  MBRTUIn - pointer to Data structure.
 *  @param  TableIn - ModBus Table ID (mbrtu.h).
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->RxExc     (set)
 *           ~ MBRTUIn->TxCnt     (set)
 *           ~ MBRTUIn->TxBuff    (set)
 *             MBRTUIn->RxNumRegs
 *             MBRTUIn->RxStartAddr
 *             MBRTUIn->RxEndAddr
 */
uint8_t MBRTU_ReadDiscretes(MBRTU_t *MBRTUIn, uint8_t TableIn)
{
    REG_t   *Reg;
    uint16_t iAddr;
    uint8_t  iBytes;
    int8_t   iBit;

    if(MBRTUIn)
    {
        //Test request size
        if(TableIn == MBRTU_COIL_TABLE_ID) MBRTU_TestCoilReq(MBRTUIn, MBRTU_REQUEST_READ, 0);
        else MBRTU_TestDiscReq(MBRTUIn);
        if(MBRTUIn->RxExc != MBRTU_EXC_OK) return (MBRTUIn->RxExc);

        //Test quantity of registers
        if(TableIn == MBRTU_COIL_TABLE_ID) MBRTU_TestCoilNRegs(MBRTUIn, MBRTU_REQUEST_READ);
        else MBRTU_TestDiscNRegs(MBRTUIn);
        if(MBRTUIn->RxExc != MBRTU_EXC_OK) return (MBRTUIn->RxExc);

        //Test start and end register addresses
        if(TableIn == MBRTU_COIL_TABLE_ID) MBRTU_TestCoilAddr(MBRTUIn);
        else MBRTU_TestDiscAddr(MBRTUIn);
        if(MBRTUIn->RxExc != MBRTU_EXC_OK) return (MBRTUIn->RxExc);

        //Create response

        MBRTUIn->TxCnt = 0;
        //+ Header
        MBRTU_CreateResHeader(MBRTUIn, MBRTU_RESPONSE_NORMAL);
        //+ Byte count (changing bottom)
        MBRTUIn->TxBuff[MBRTUIn->TxCnt] = 0;
        MBRTUIn->TxCnt++;
        //+ Data (first byte init)
        MBRTUIn->TxBuff[MBRTUIn->TxCnt] = 0;

        Type_InitWords(MBRTUIn->DataBuff, TYPE_DOUBLE_WSZ, 0);
        iAddr  = MBRTUIn->RxStartAddr;
        iBytes = 1;
        iBit   = -1;

        while(iAddr<=MBRTUIn->RxEndAddr)
        {
            Reg = REG_GetByMbAddr(TableIn, iAddr);
            if(Reg) REG_CopyWordsFromMb(Reg, MBRTUIn->DataBuff, TYPE_DOUBLE_WSZ, TYPE_BYTE_ORDER_DEF, BIT_FALSE);

            //set Tx
            if(iBit < 7)
            {
                iBit++;
            }
            else
            {
                iBit = 0;
                iBytes++;
                MBRTUIn->TxCnt++;
                //Tx-byte init
                MBRTUIn->TxBuff[MBRTUIn->TxCnt] = 0;
            }
            //+ Data (bytes)
            MBRTUIn->TxBuff[MBRTUIn->TxCnt] = BYTE_SET_BIT(MBRTUIn->TxBuff[MBRTUIn->TxCnt], MBRTUIn->DataBuff[0], iBit);
            iAddr++;
        }
        MBRTUIn->TxCnt++;
        //~ Byte count
        MBRTUIn->TxBuff[MBRTU_APU_DISC_RBYTES_POS] = iBytes;
        //+ CRC
        MBRTU_CreateResCRC(MBRTUIn);

        return (MBRTUIn->RxExc);
    }
    return (MBRTU_EXC_NONRECOV_ERR);
}


/** @brief  Handler of request to write Coils (single or multiple).
 *  @param  MBRTUIn - pointer to Data structure.
 *  @param  ModeIn  - write mode:
 *  @arg      = 0 - single coil
 *  @arg      = 1 - multiple coils
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->RxExc       (set)
 *           ~ MBRTUIn->TxCnt       (set)
 *           ~ MBRTUIn->TxBuff      (set)
 *             MBRTUIn->RxNumRegs   (set)
 *             MBRTUIn->RxNumBytes  (set)
 */
uint8_t MBRTU_WriteCoils(MBRTU_t *MBRTUIn, uint8_t ModeIn)
{
    REG_t   *Reg;
    uint16_t iAddr;
    uint8_t  iRx;
    int8_t   iBit;

    if(MBRTUIn)
    {
        //Test request size
        MBRTU_TestCoilReq(MBRTUIn, MBRTU_REQUEST_WRITE, ModeIn);
        if(MBRTUIn->RxExc != MBRTU_EXC_OK) return (MBRTUIn->RxExc);

        if(ModeIn == MBRTU_WRITE_SINGLE)
        {
            MBRTUIn->RxNumRegs  = 1;
            MBRTUIn->RxNumBytes = 2;
        }
        else //MBRTU_WRITE_MULTIPLE
        {
            //Test quantity of registers
            MBRTU_TestCoilNRegs(MBRTUIn, MBRTU_REQUEST_WRITE);
            if(MBRTUIn->RxExc != MBRTU_EXC_OK) return (MBRTUIn->RxExc);

            //Test quantity of bytes
            MBRTU_TestCoilNBytes(MBRTUIn);
            if(MBRTUIn->RxExc != MBRTU_EXC_OK) return (MBRTUIn->RxExc);
        }

        //Test start and end register addresses
        MBRTU_TestCoilAddr(MBRTUIn);
        if(MBRTUIn->RxExc != MBRTU_EXC_OK) return (MBRTUIn->RxExc);

        //Create response
        MBRTUIn->TxCnt = 0;
        //+ Header
        MBRTU_CreateResHeader(MBRTUIn, MBRTU_RESPONSE_NORMAL);
        //+ Start register address: Hi, Lo
        MBRTUIn->TxBuff[MBRTUIn->TxCnt] = MBRTUIn->RxBuff[MBRTU_APU_COIL_ADDR_POS];
        MBRTUIn->TxCnt++;
        MBRTUIn->TxBuff[MBRTUIn->TxCnt] = MBRTUIn->RxBuff[MBRTU_APU_COIL_ADDR_POS+1];
        MBRTUIn->TxCnt++;
        // + Coil value: Hi, Lo        (Single mode)
        // + Quantity of coils: Hi, Lo (Multiple mode)
        MBRTUIn->TxBuff[MBRTUIn->TxCnt] = MBRTUIn->RxBuff[MBRTU_APU_COIL_NREGS_POS];
        MBRTUIn->TxCnt++;
        MBRTUIn->TxBuff[MBRTUIn->TxCnt] = MBRTUIn->RxBuff[MBRTU_APU_COIL_NREGS_POS+1];
        MBRTUIn->TxCnt++;
        //+ CRC
        MBRTU_CreateResCRC(MBRTUIn);

        //Write received data into Data table
        iAddr  = MBRTUIn->RxStartAddr;
        iBit   = -1;
        iRx    = ((ModeIn == MBRTU_WRITE_SINGLE) ? MBRTU_APU_COIL_SDATA_POS : MBRTU_APU_COIL_MDATA_POS);

        while(iAddr<=MBRTUIn->RxEndAddr)
        {
            Reg = REG_GetByMbAddr(MBRTU_COIL_TABLE_ID, iAddr);

            if(iBit < 7)
            {
                iBit++;
            }
            else
            {
                iBit = 0;
                iRx++;
            }

            if(Reg)
            {
                //+ Data: Hi, Lo
                if(ModeIn == MBRTU_WRITE_SINGLE)
                {
                    //for single write mode:
                    // value is word (Hi, Lo)
                    // value of 0XFF00 requests the coil to be ON, otherwise - to be OFF
                    MBRTUIn->DataBuff[0] = (uint16_t)((MERGE_WORD(MBRTUIn->RxBuff[iRx+1], MBRTUIn->RxBuff[iRx]) == 0xFF00) ? BIT_TRUE : BIT_FALSE);
                }
                else
                {
                    MBRTUIn->DataBuff[0] = BIT_GET_VALUE(MBRTUIn->RxBuff[iRx], iBit);
                }
#ifdef RTE_MOD_REG_MON
                REG_CopyWordsToMb(Reg, MBRTUIn->DataBuff, TYPE_DOUBLE_WSZ, TYPE_BYTE_ORDER_DEF, BIT_FALSE, BIT_TRUE);
#else
                REG_CopyWordsToMb(Reg, MBRTUIn->DataBuff, TYPE_DOUBLE_WSZ, TYPE_BYTE_ORDER_DEF, BIT_FALSE, BIT_FALSE);
#endif // RTE_MOD_REG_MON
            }
            iAddr++;
        }

        return (MBRTUIn->RxExc);
    }
    return (MBRTU_EXC_NONRECOV_ERR);
}


/** @brief  Test request to diagnostics.
 *  @param  MBRTUIn - pointer to Data structure.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *             MBRTUIn->RxCnt  (test)
 *           ~ MBRTUIn->RxExc  (change)
 */
uint8_t MBRTU_TestDiagReq(MBRTU_t *MBRTUIn)
{
    if(MBRTUIn)
    {
        MBRTUIn->RxExc = ((MBRTUIn->RxCnt < MBRTU_DIAG_REQUEST_SZ) ? MBRTU_EXC_DATA_ERR : MBRTU_EXC_OK);
        return (MBRTUIn->RxExc);
    }
    return (MBRTU_EXC_NONRECOV_ERR);
}

/** @brief  Handler of diagnostics sub-function code (Echo).
 *  @param  MBRTUIn - pointer to Data structure.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->TxCnt  (change)
 *           ~ MBRTUIn->TxBuff (change)
 */
uint8_t MBRTU_DiagEcho(MBRTU_t *MBRTUIn)
{
    uint8_t iRx = 0;

    if(MBRTUIn)
    {
        //Create response
        MBRTUIn->TxCnt = 0;
        //+ Header
        MBRTU_CreateResHeader(MBRTUIn, MBRTU_RESPONSE_NORMAL);

        for(iRx=MBRTU_ADU_DIAG_SUBFUNC_POS; iRx<MBRTUIn->RxCnt-MBRTU_ADU_CRC_SZ; iRx++)
        {
            //+ Data
            MBRTUIn->TxBuff[MBRTUIn->TxCnt] = MBRTUIn->RxBuff[iRx];
            MBRTUIn->TxCnt++;
        }
        //+ CRC
        MBRTU_CreateResCRC(MBRTUIn);

        return (MBRTU_EXC_OK);
    }
    return (MBRTU_EXC_NONRECOV_ERR);
}

/** @brief  Handler of diagnostics sub-function code (Return Counter).
 *  @param  MBRTUIn - pointer to Data structure.
 *  @param  CntIn   - counter value
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->TxCnt  (change)
 *           ~ MBRTUIn->TxBuff (change)
 *             MBRTUIn->SubFunc
 */
uint8_t MBRTU_DiagCount(MBRTU_t *MBRTUIn, uint16_t CntIn)
{
    if(MBRTUIn)
    {
        //Create response
        MBRTUIn->TxCnt = 0;
        //+ Header
        MBRTU_CreateResHeader(MBRTUIn, MBRTU_RESPONSE_NORMAL);
        //+ SubFunc: Hi, Lo
        MBRTUIn->TxBuff[MBRTUIn->TxCnt] = BYTE1(MBRTUIn->RxSubFunc);
        MBRTUIn->TxCnt++;
        MBRTUIn->TxBuff[MBRTUIn->TxCnt] = BYTE0(MBRTUIn->RxSubFunc);
        MBRTUIn->TxCnt++;
        //+ Data: Hi, Lo
        MBRTUIn->TxBuff[MBRTUIn->TxCnt] = BYTE1(CntIn);
        MBRTUIn->TxCnt++;
        MBRTUIn->TxBuff[MBRTUIn->TxCnt] = BYTE0(CntIn);
        MBRTUIn->TxCnt++;
        //+ CRC
        MBRTU_CreateResCRC(MBRTUIn);

        return (MBRTU_EXC_OK);
    }
    return (MBRTU_EXC_NONRECOV_ERR);
}

/** @brief  Handler of request to diagnostics.
 *  @param  MBRTUIn - pointer to Data structure.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->RxExc      (change)
 *             MBRTUIn->RxSubFunc  (change, test)
 *             MBRTUIn->cBusComErr (change)
 *             MBRTUIn->cBusExcErr (change)
 *             MBRTUIn->cNoRes     (change)
 */
uint8_t MBRTU_Diagnostics(MBRTU_t *MBRTUIn)
{
    if(MBRTUIn)
    {
        //Test request size
        MBRTU_TestDiagReq(MBRTUIn);
        if(MBRTUIn->RxExc != MBRTU_EXC_OK) return (MBRTUIn->RxExc);

        //Read sub-function code
        MBRTUIn->RxSubFunc = MERGE_WORD(MBRTUIn->RxBuff[MBRTU_ADU_DIAG_SUBFUNC_POS+1], MBRTUIn->RxBuff[MBRTU_ADU_DIAG_SUBFUNC_POS]);

        switch(MBRTUIn->RxSubFunc)
        {
            //Return Query Data
            case MBRTU_SUBFUNC_00:
                MBRTUIn->RxExc = MBRTU_DiagEcho(MBRTUIn);
                break;

            //Clear Counters and Diagnostic Register
            case MBRTU_SUBFUNC_10:
                MBRTUIn->cBusComErr  = 0;
                MBRTUIn->cBusExcErr  = 0;
                MBRTUIn->cRes        = 0;
                MBRTUIn->cNoRes      = 0;
                MBRTUIn->cRxQueueErr = 0;
                MBRTUIn->RxExc = MBRTU_DiagEcho(MBRTUIn);
                break;

            //Return Bus Communication Error Count
            case MBRTU_SUBFUNC_12:
                MBRTUIn->RxExc = MBRTU_DiagCount(MBRTUIn, MBRTUIn->cBusComErr);
                break;

            //Return Bus Exception Error Count
            case MBRTU_SUBFUNC_13:
                MBRTUIn->RxExc = MBRTU_DiagCount(MBRTUIn, MBRTUIn->cBusExcErr);
                break;

            //Return ServerNo Response Count
            case MBRTU_SUBFUNC_15:
                MBRTUIn->RxExc = MBRTU_DiagCount(MBRTUIn, MBRTUIn->cNoRes);
                break;

            default:
                MBRTUIn->RxExc = MBRTU_EXC_DATA_ERR;
        }

        return (MBRTUIn->RxExc);
    }
    return (MBRTU_EXC_NONRECOV_ERR);
}


/** @brief  Create response.
 *  @param  MBRTUIn - pointer to Data structure.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->RxExc  (set, test)
 *             MBRTUIn->RxFunc
 */
uint8_t MBRTU_CreateRes(MBRTU_t *MBRTUIn)
{
    if(MBRTUIn)
    {
        if(MBRTUIn->RxExc != MBRTU_EXC_OK) return (MBRTUIn->RxExc);

        //Test Function code
        switch(MBRTUIn->RxFunc)
        {
#ifdef MBRTU_COIL_READ_ALLOW
            case MBRTU_FUNC_01:
                return MBRTU_ReadDiscretes(MBRTUIn, MBRTU_COIL_TABLE_ID);
#endif // MBRTU_COIL_READ_ALLOW

#ifdef MBRTU_DISC_READ_ALLOW
            case MBRTU_FUNC_02:
                return MBRTU_ReadDiscretes(MBRTUIn, MBRTU_DISC_TABLE_ID);
#endif // MBRTU_DISC_READ_ALLOW

#ifdef MBRTU_HOLD_READ_ALLOW
            case MBRTU_FUNC_03:
                return MBRTU_ReadRegs(MBRTUIn, MBRTU_HOLD_TABLE_ID);
#endif // MBRTU_HOLD_READ_ALLOW

#ifdef MBRTU_INPT_READ_ALLOW
            case MBRTU_FUNC_04:
                return MBRTU_ReadRegs(MBRTUIn, MBRTU_INPT_TABLE_ID);
#endif // MBRTU_INPT_READ_ALLOW

#ifdef MBRTU_COIL_WRITE_ALLOW
            case MBRTU_FUNC_05:
                return MBRTU_WriteCoils(MBRTUIn, MBRTU_WRITE_SINGLE);
            case MBRTU_FUNC_15:
                return MBRTU_WriteCoils(MBRTUIn, MBRTU_WRITE_MULTIPLE);
#endif // MBRTU_COIL_WRITE_ALLOW

#ifdef MBRTU_HOLD_WRITE_ALLOW
            case MBRTU_FUNC_06:
                return MBRTU_WriteHoldRegs(MBRTUIn, MBRTU_WRITE_SINGLE);
            case MBRTU_FUNC_16:
                return MBRTU_WriteHoldRegs(MBRTUIn, MBRTU_WRITE_MULTIPLE);
#endif // MBRTU_HOLD_WRITE_ALLOW

#ifdef MBRTU_DIAG_ALLOW
            case MBRTU_FUNC_08:
                return MBRTU_Diagnostics(MBRTUIn);
#endif // MBRTU_DIAG_ALLOW

            default:
                MBRTUIn->RxExc = MBRTU_EXC_FUNC_ERR;
                return (MBRTUIn->RxExc);
        }
    }
    return (MBRTU_EXC_NONRECOV_ERR);
}
