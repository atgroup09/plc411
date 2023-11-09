/* @page mbrtu.h
 *       PLC411::RTE
 *       ModBUs RTU (API)
 *       2020-2023, atgroup09@gmail.com
 */

/*!
 * Constants which defines the format of a modbus frame. The example is
 * shown for a Modbus RTU/ASCII frame. Note that the Modbus PDU is not
 * dependent on the underlying transport.
 *
 * <code>
 *  <------------------------ MODBUS ADU (1) ------------------------------>
 *              <----------- MODBUS PDU (1') ---------------->
 *  +-----------+---------------+----------------------------+-------------+
 *  | Address   | Function Code | Data                       | CRC/LRC     |
 *  +-----------+---------------+----------------------------+-------------+
 *  |           |               |                            |
 * (2)        (3/2')           (3')                         (4)
 *
 * (1)  ... MB_ADU_SIZE_MAX = 256
 * (2)  ... MB_ADU_ADDR_OFF = 0
 * (3)  ... MB_ADU_PDU_OFF  = 1
 * (4)  ... MB_ADU_SIZE_CRC = 2
 *
 * (1') ... MB_PDU_SIZE_MAX = 253
 * (2') ... MB_PDU_FUNC_OFF = 0
 * (3') ... MB_PDU_DATA_OFF = 1
 * </code>
 */

#ifndef MBRTU_H
#define MBRTU_H

#include "reg.h"


/** @def Size of Data-buffer (bytes)
 */
#define MBRTU_BUFF_SZ                  (uint8_t)250




/** @def ADU size (bytes)
 */
#define MBRTU_ADU_MIN_SZ               (uint8_t)4      //Minimum size of ADU
#define MBRTU_ADU_MAX_SZ               (uint8_t)256    //Maximum size of ADU


/** @def PDU size (bytes)
 */
#define MBRTU_PDU_MIN_SZ               (uint8_t)1      //Minimum size of PDU
#define MBRTU_PDU_MAX_SZ               (uint8_t)253    //Maximum size of PDU


/** @def ADU-part size (bytes)
 */
#define MBRTU_ADU_SLAVE_SZ             (uint8_t)1      //Slave address
#define MBRTU_ADU_FUNC_SZ              (uint8_t)1      //Function code
#define MBRTU_ADU_ADDR_SZ              (uint8_t)2      //Start register address
#define MBRTU_ADU_NREGS_SZ             (uint8_t)2      //Quattity of registers
#define MBRTU_ADU_NBYTES_SZ            (uint8_t)1      //Quattity of bytes
#define MBRTU_ADU_CRC_SZ               (uint8_t)2      //CRC
#define MBRTU_ADU_CONST_SZ             (uint8_t)(MBRTU_ADU_SLAVE_SZ+MBRTU_ADU_FUNC_SZ+MBRTU_ADU_ADDR_SZ+MBRTU_ADU_NREGS_SZ+MBRTU_ADU_NBYTES_SZ+MBRTU_ADU_CRC_SZ)

#define MBRTU_ADU_SUBFUNC_SZ           (uint8_t)2      //Sub-function code (diagnostics)


/** @def ADU-part position (bytes)
 */
#define MBRTU_ADU_SLAVE_POS            (uint8_t)0      //Slave address
#define MBRTU_ADU_FUNC_POS             (uint8_t)1      //Function code
#define MBRTU_ADU_ADDR_POS             (uint8_t)2      //Start register address (first  byte position)
#define MBRTU_ADU_NBYTES_POS           (uint8_t)2      //Quattity of bytes
#define MBRTU_ADU_DATA_POS             (uint8_t)3      //Data
#define MBRTU_ADU_NREGS_POS            (uint8_t)4      //Quantity of Registers

#define MBRTU_APU_COIL_ADDR_POS        (uint8_t)2      //Start register address
#define MBRTU_APU_COIL_NREGS_POS       (uint8_t)4      //Quantity of registers (write multiple) or Data (write single)
#define MBRTU_APU_COIL_NBYTES_POS      (uint8_t)6      //Quantity of Bytes (write multiple)
#define MBRTU_APU_COIL_RBYTES_POS      (uint8_t)2      //Quantity of Bytes in response (read)
#define MBRTU_APU_COIL_SDATA_POS       (uint8_t)4      //Data (write single)
#define MBRTU_APU_COIL_MDATA_POS       (uint8_t)7      //Data (write multiple)

#define MBRTU_APU_DISC_ADDR_POS        (uint8_t)2      //Start register address
#define MBRTU_APU_DISC_NREGS_POS       (uint8_t)4      //Quantity of registers
#define MBRTU_APU_DISC_RBYTES_POS      (uint8_t)2      //Quantity of Bytes in response (read)

#define MBRTU_APU_HOLD_ADDR_POS        (uint8_t)2      //Start register address
#define MBRTU_APU_HOLD_NREGS_POS       (uint8_t)4      //Quantity of registers (write multiple) or Data (write single)
#define MBRTU_APU_HOLD_NBYTES_POS      (uint8_t)6      //Quantity of Bytes (write multiple)
#define MBRTU_APU_HOLD_SDATA_POS       (uint8_t)4      //Data (write single)
#define MBRTU_APU_HOLD_MDATA_POS       (uint8_t)7      //Data (write multiple)

#define MBRTU_APU_INPT_ADDR_POS        (uint8_t)2      //Start register address
#define MBRTU_APU_INPT_NREGS_POS       (uint8_t)4      //Quantity of registers

#define MBRTU_ADU_DIAG_SUBFUNC_POS     (uint8_t)2      //Sub-function code (diagnostics)
#define MBRTU_APU_DIAG_DATA_POS        (uint8_t)4      //Data


/** @def Exception codes
 */
#define MBRTU_EXC_OK                   (uint8_t)0      //no errors
#define MBRTU_EXC_FUNC_ERR             (uint8_t)1      //ILLEGAL FUNCTION
#define MBRTU_EXC_ADDR_ERR             (uint8_t)2      //ILLEGAL DATA ADDRESS
#define MBRTU_EXC_DATA_ERR             (uint8_t)3      //ILLEGAL DATA VALUE
#define MBRTU_EXC_NONRECOV_ERR         (uint8_t)4      //SERVERDEVICE FAILURE
#define MBRTU_EXC_LONGTIME             (uint8_t)5      //ACKNOW LEDGE
#define MBRTU_EXC_PROCESS              (uint8_t)6      //SERVERDEVICE BUSY
#define MBRTU_EXC_SLAVE_ERR            (uint8_t)200    //system error: incorrect Slave ID (request is ignored)
#define MBRTU_EXC_COM_NUM              (uint8_t)201    //system error: incorrect number of COM-port (request is ignored)
#define MBRTU_EXC_COM_MODE             (uint8_t)202    //system error: incorrect mode of COM-port (request is ignored)
#define MBRTU_EXC_NUM                  (uint8_t)203    //system error: incorrect Num (quantity of read/write registers) (request is ignored)
#define MBRTU_EXC_CRC_ERR              (uint8_t)250    //system error: illegal CRC  (request is ignored)
#define MBRTU_EXC_RX_OVERFLOW_ERR      (uint8_t)251    //system error: RX-buffer overflow  (request is ignored)
#define MBRTU_EXC_APU_ERR              (uint8_t)254    //system error: illegal APU minimum size (request is ignored)


/** @def Function codes
 */
#define MBRTU_FUNC_01                  (uint8_t)1      //Read Coils
#define MBRTU_FUNC_02                  (uint8_t)2      //Read Discrete inputs
#define MBRTU_FUNC_03                  (uint8_t)3      //Read Holding Registers
#define MBRTU_FUNC_04                  (uint8_t)4      //Read Input Registers
#define MBRTU_FUNC_05                  (uint8_t)5      //Write Coil  (single)
#define MBRTU_FUNC_15                  (uint8_t)15     //Write Coils (multiple)
#define MBRTU_FUNC_06                  (uint8_t)6      //Write Holding Register  (single)
#define MBRTU_FUNC_16                  (uint8_t)16     //Write Holding Registers (multiple)
#define MBRTU_FUNC_08                  (uint8_t)8      //Diagnostics (Serial Line only)

/** @def Function codes (mask)
 *       where function code is bit position in the mask
 */
#define MBRTU_FUNC_MASK                (uint32_t)98686


/** @def Sub-function codes (diagnostics)
 */
#define MBRTU_SUBFUNC_00               (uint8_t)0      //Return Query Data (echo)
#define MBRTU_SUBFUNC_10               (uint8_t)10     //Clear Counters and Diagnostic Register
#define MBRTU_SUBFUNC_12               (uint8_t)12     //Return Bus Communication Error Count
#define MBRTU_SUBFUNC_13               (uint8_t)13     //Return Bus Exception Error Count
#define MBRTU_SUBFUNC_15               (uint8_t)15     //Return Server No Response Count


/** @def Coils
 */
#define MBRTU_COIL_READ_NREGS_MIN      (uint16_t)1     //Minimum quantity of registers to read
#define MBRTU_COIL_READ_NREGS_MAX      (uint16_t)2000  //Maximum quantity of registers to read
#define MBRTU_COIL_READ_REQUEST_SZ     (uint16_t)8     //Size of request to read

#define MBRTU_COIL_WRITE_NREGS_MIN     (uint16_t)1     //Minimum quantity of registers to write
#define MBRTU_COIL_WRITE_NREGS_MAX     (uint16_t)1968  //Maximum quantity of registers to write
#define MBRTU_COIL_SWRITE_REQUEST_SZ   (uint16_t)8     //Minimum size of request to single write
#define MBRTU_COIL_MWRITE_REQUEST_SZ   (uint16_t)10    //Minimum size of request to multiple write

#define MBRTU_COIL_WRITE_NBYTES_MAX    (uint16_t)(MBRTU_COIL_WRITE_NREGS_MAX/8)   //Maximum bytes to write

//Table settints
#define MBRTU_COIL_READ_ALLOW          //Allow to read  (comment the define to disable)
#define MBRTU_COIL_WRITE_ALLOW         //Allow to write (comment the define to disable)


/** @def Dicrete inputs
 */
#define MBRTU_DISC_READ_NREGS_MIN      (uint16_t)1     //Minimum quantity of registers to read
#define MBRTU_DISC_READ_NREGS_MAX      (uint16_t)2000  //Maximum quantity of registers to read
#define MBRTU_DISC_READ_REQUEST_SZ     (uint16_t)8     //Size of request to read

//Table settints
#define MBRTU_DISC_READ_ALLOW          //Allow to read (comment the define to disable)


/** @def Holding Registers
 */
#define MBRTU_HOLD_READ_NREGS_MIN      (uint16_t)1     //Minimum quantity of registers to read
#define MBRTU_HOLD_READ_NREGS_MAX      (uint16_t)125   //Maximum quantity of registers to read
#define MBRTU_HOLD_READ_REQUEST_SZ     (uint16_t)8     //Size of request to read

#define MBRTU_HOLD_WRITE_NREGS_MIN     (uint16_t)1     //Minimum quantity of registers to write
#define MBRTU_HOLD_WRITE_NREGS_MAX     (uint16_t)123   //Maximum quantity of registers to write
#define MBRTU_HOLD_SWRITE_REQUEST_SZ   (uint16_t)8     //Minimum size of request to single write
#define MBRTU_HOLD_MWRITE_REQUEST_SZ   (uint16_t)11    //Minimum size of request to multiple write

#define MBRTU_HOLD_WRITE_NBYTES_MAX    (uint16_t)(MBRTU_HOLD_WRITE_NREGS_MAX*2)   //Maximum bytes to write

//Table settints
#define MBRTU_HOLD_READ_ALLOW          //Allow to read  (comment the define to disable)
#define MBRTU_HOLD_WRITE_ALLOW         //Allow to write (comment the define to disable)


/** @def Input Registers
 */
#define MBRTU_INPT_READ_NREGS_MIN      (uint16_t)1     //Minimum quantity of registers to read
#define MBRTU_INPT_READ_NREGS_MAX      (uint16_t)125   //Maximum quantity of registers to read
#define MBRTU_INPT_READ_REQUEST_SZ     (uint16_t)8     //Size of request to read

//Table settints
#define MBRTU_INPT_READ_ALLOW          //Allow to read (comment the define to disable)


/** @def Diagnostics
 */
#define MBRTU_DIAG_REQUEST_SZ          (uint16_t)6     //Minimum size of request
#define MBRTU_DIAG_REQUEST_WO_CRC_SZ   (uint16_t)(MBRTU_DIAG_REQUEST_SZ-MBRTU_ADU_CRC_SZ)  //Minimum size of request without CRC

#define MBRTU_DIAG_ALLOW                //Allow (comment the define to disable)

/** @def Maximum size of counters
 */
#define MBRTU_DIAG_COUNTER_MAX         (uint16_t)0xFFFF


/** @def Function code prefix
 *       exception response
 */
#define MBRTU_FUNC_ERR_PRE             (uint8_t)0x80


/** @def Response header
 *       exception modes
 */
#define MBRTU_RESPONSE_NORMAL          (uint8_t)0     //normal response
#define MBRTU_RESPONSE_EXC             (uint8_t)1     //exception response

/** @def Response types
 */
#define MBRTU_REQUEST_READ             (uint8_t)0     //read
#define MBRTU_REQUEST_WRITE            (uint8_t)1     //write

/** @def Types of register tables
 */
#define MBRTU_TABLE_COIL               (uint8_t)0    //coils
#define MBRTU_TABLE_DISC               (uint8_t)1    //dicrete inputs
#define MBRTU_TABLE_HOLD               (uint8_t)0    //holding registers
#define MBRTU_TABLE_INPT               (uint8_t)1    //input registers

/** @def Write modes
 */
#define MBRTU_WRITE_SINGLE             (uint8_t)0    //single
#define MBRTU_WRITE_MULTIPLE           (uint8_t)1    //multiple


/** @def Baudrate
 */
#define MBRTU_BAUDRATE_1200            (uint8_t)0    //1200
#define MBRTU_BAUDRATE_2400            (uint8_t)1    //2400
#define MBRTU_BAUDRATE_4800            (uint8_t)2    //4800
#define MBRTU_BAUDRATE_9600            (uint8_t)3    //9600
#define MBRTU_BAUDRATE_19200           (uint8_t)4    //19200
#define MBRTU_BAUDRATE_38400           (uint8_t)5    //38400
#define MBRTU_BAUDRATE_57600           (uint8_t)6    //57600
#define MBRTU_BAUDRATE_115200          (uint8_t)7    //115200

/** @def Data bits
 */
#define MBRTU_DATA_BITS_8              (uint8_t)0    //8 bits
#define MBRTU_DATA_BITS_9              (uint8_t)1    //9 bits

/** @def Parity
 */
#define MBRTU_PARITY_NONE              (uint8_t)0    //None
#define MBRTU_PARITY_ODD               (uint8_t)1    //Odd
#define MBRTU_PARITY_EVEN              (uint8_t)2    //Even

/** @def Stop bits
 */
#define MBRTU_STOP_BITS_1              (uint8_t)0    //1 bit
#define MBRTU_STOP_BITS_2              (uint8_t)1    //2 bits

/** @def Mode
 */
#define MBRTU_MODE_SLAVE               (uint8_t)0    //Slave
#define MBRTU_MODE_MASTER              (uint8_t)1    //Master

/** @def Byte order
 */
#define MBRTU_BYTE_ORDER_3210          TYPE_BYTE_ORDER_3210
#define MBRTU_BYTE_ORDER_0123          TYPE_BYTE_ORDER_0123
#define MBRTU_BYTE_ORDER_1032          TYPE_BYTE_ORDER_1032  //standard byte order for ModBus
#define MBRTU_BYTE_ORDER_2301          TYPE_BYTE_ORDER_2301


/** @typedef Com-port settings
 *           bit-fields
 */
typedef struct MBRTU_Set_t_
{
    uint16_t BaudRate:4;
    uint16_t DataBits:1;
    uint16_t Parity:2;
    uint16_t StopBits:1;
    uint16_t Mode:1;
    uint16_t ByteOrder:3;

} MBRTU_Set_t;

/** @typedef Com-port settings
 *           union of Raw-data and parsed bit-fields
 */
typedef union {

    MBRTU_Set_t Settings;
    uint16_t    Data;

} MBRTU_Set_ut;

/** @def Com-port settings
 *       Queue-data
 */
typedef struct MBRTU_Set_Q_t_
{
   uint8_t  SlaveID;  //slave ID
   uint16_t Data;     //packed settings

} MBRTU_Set_Q_t;


/** @def Rx-Tx Mode
 */
#define MBRTU_RX                       (uint8_t)0
#define MBRTU_RX_EXC                   (uint8_t)0xF0
#define MBRTU_TX                       (uint8_t)1
#define MBRTU_FREE                     (uint8_t)0xFF


/** @typedef MBRTU Context
 */
typedef struct MBRTU_t_
{
    //@var Settings
    MBRTU_Set_t Settings;

    //@var Slave ID
    uint8_t SlaveID;

    //@var Rx-buffer (ADU)
    uint8_t RxBuff[MBRTU_BUFF_SZ];
    //@var Rx-counter
    uint8_t RxCnt;
    //@var Function code
    uint8_t RxFunc;
    //@var FuncMask
    uint32_t RxFuncMask;
    //@var Address of start register
    uint16_t RxStartAddr;
    //@var Address of end register
    uint16_t RxEndAddr;
    //@var The number of registers
    uint16_t RxNumRegs;
    //@var The number of bytes to write
    uint16_t RxNumBytes;
    //@var Diagnostics sub-function code
    uint16_t RxSubFunc;

    //@var Exception code
    uint8_t RxExc;
    //@var Rx-buffer overflow
    uint8_t RxBuffOver;
    //@var Rx-queue overflow
    uint8_t RxQueueOver;

    //@var Bus Exception Error Count
    uint16_t cBusExcErr;
    //@var Bus Communication Error Count (CRC error)
    uint16_t cBusComErr;
    //@var Response Count
    uint16_t cRes;
    //@var No Response Count
    uint16_t cNoRes;

    //@var Rx-queue Error Count
    uint16_t cRxQueueErr;

    //@var Tx-buffer (ADU)
    uint8_t TxBuff[MBRTU_BUFF_SZ];
    //@var Tx-counter (sent bytes)
    uint8_t TxCnt;

    //@var Word-buffer (single value)
    uint16_t DataBuff[TYPE_DOUBLE_WSZ];

    //@var Rx-Tx Mode
    // 0 - RX
    // 1 - TX
    uint8_t RxTx;

} MBRTU_t;


/** @brief  Init. interface context by default.
 *  @param  MBRTUIn  - pointer to interface context.
 *  @param  SlaveIn  - slave ID.
 *  @return None.
 */
void MBRTU_InitDef(MBRTU_t *MBRTUIn, const uint8_t SlaveIn);


/** @brief  Calculate CRC16 for frame.
 *  @param  FrameIn   - pointer to frame-buffer.
 *  @param  FrameSzIn - size of frame-buffer (without CRC bytes).
 *  @return CRC16.
 */
uint16_t MBRTU_CalcCRC16(const uint8_t *FrameIn, uint8_t FrameSzIn);

/** @brief  Test Slave ID.
 *  @param  Slave1In - target slave ID.
 *  @param  Slave2In - correct slave ID.
 *  @return Result code:
 *  @arg     = 0 - target slave ID is incorrect
 *  @arg     = 1 - target slave ID is correct
 */
uint8_t MBRTU_TestSlaveID(uint8_t Slave1In, uint8_t Slave2In);

/** @brief  Test Table ID.
 *  @param  TableIn - table ID.
 *  @return Result code:
 *  @arg     =0 - table is not supported
 *  @arg    >=1 - table is supported (size of table)
 */
uint16_t MBRTU_TestTable(uint8_t TableIn);

/** @brief  Test Function code.
 *  @param  FuncIn - function code.
 *  @return Result code:
 *  @arg     = 0 - function is not supported
 *  @arg     = 1 - function is supported
 */
uint8_t MBRTU_TestFunc(uint8_t FuncIn);

/** @brief  Test CRC.
 *  @param  FrameIn   - pointer to frame-buffer.
 *  @param  FrameSzIn - size of frame-buffer.
 *  @param  HiIn - Hi-byte of target CRC.
 *  @param  LoIn - Lo-byte of target CRC.
 *  @return Result code:
 *  @arg     = 0 - CRC is incorrect
 *  @arg     = 1 - CRC is correct
 */
uint8_t MBRTU_TestCRC16(const uint8_t *FrameIn, uint8_t FrameSzIn, uint8_t HiIn, uint8_t LoIn);


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
uint8_t MBRTU_ParseReq(MBRTU_t *MBRTUIn);


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
uint8_t MBRTU_CreateResHeader(MBRTU_t *MBRTUIn, uint8_t ExcModeIn);

/** @brief  Create response CRC.
 *  @param  MBRTUIn - pointer to Data structure.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->TxCnt  (set)
 *           ~ MBRTUIn->TxBuff (set)
 */
uint8_t MBRTU_CreateResCRC(MBRTU_t *MBRTUIn);

/** @brief  Create exception response.
 *  @param  MBRTUIn - pointer to Data structure.
 *  @param  ExcIn   - exception code.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->TxCnt  (set)
 *           ~ MBRTUIn->TxBuff (set)
 */
uint8_t MBRTU_CreateResExc(MBRTU_t *MBRTUIn, uint8_t ExcIn);


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
uint8_t MBRTU_TestHoldReq(MBRTU_t *MBRTUIn, uint8_t ReqTyIn, uint8_t ModeIn);

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
uint8_t MBRTU_TestHoldNRegs(MBRTU_t *MBRTUIn, uint8_t ReqTyIn);

/** @brief  Test quantity of bytes data for multiple write (Holding).
 *  @param  MBRTUIn - pointer to Data structure.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->RxNumBytes (set, test)
 *           ~ MBRTUIn->RxExc      (set)
 *             MBRTUIn->RxBuff
 */
uint8_t MBRTU_TestHoldNBytes(MBRTU_t *MBRTUIn);

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
uint8_t MBRTU_TestHoldAddr(MBRTU_t *MBRTUIn);

/** @brief  Test request to table of Input registers.
 *  @param  MBRTUIn - pointer to Data structure.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *             MBRTUIn->RxCnt  (test)
 *           ~ MBRTUIn->RxExc  (set)
 */
uint8_t MBRTU_TestInptReq(MBRTU_t *MBRTUIn);

/** @brief  Test quantity of Input registers.
 *  @param  MBRTUIn - pointer to Data structure.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->RxNumRegs (set, test)
 *           ~ MBRTUIn->RxExc     (set)
 *             MBRTUIn->RxBuff
 */
uint8_t MBRTU_TestInptNRegs(MBRTU_t *MBRTUIn);

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
uint8_t MBRTU_TestInptAddr(MBRTU_t *MBRTUIn);


/** @brief  Handler of request to read numeric registers (Holding or Inputs).
 *  @param  MBRTUIn - pointer to Data structure.
 *  @param  TableIn - ModBus Table ID (mbrtu.h).
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->RxExc     (set)
 *           ~ MBRTUIn->TxCnt     (set, 0, ++)
 *           ~ MBRTUIn->TxBuff    (set)
 *             MBRTUIn->RxNumRegs
 *             MBRTUIn->RxStartAddr
 *             MBRTUIn->RxEndAddr
 */
uint8_t MBRTU_ReadRegs(MBRTU_t *MBRTUIn, uint8_t TableIn);


/** @brief  Handler of request to write Holding registers (single or multiple).
 *  @param  MBRTUIn - pointer to Data structure.
 *  @param  ModeIn  - write mode:
 *  @arg      = 0 - single register
 *  @arg      = 1 - multiple registers
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->RxExc       (set)
 *           ~ MBRTUIn->TxCnt       (set)
 *           ~ MBRTUIn->TxBuff      (set)
 *             MBRTUIn->RxNumRegs
 *             MBRTUIn->RxNumBytes
 */
uint8_t MBRTU_WriteHoldRegs(MBRTU_t *MBRTUIn, uint8_t ModeIn);


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
uint8_t MBRTU_TestCoilReq(MBRTU_t *MBRTUIn, uint8_t ReqTyIn, uint8_t ModeIn);

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
uint8_t MBRTU_TestCoilNRegs(MBRTU_t *MBRTUIn, uint8_t ReqTyIn);

/** @brief  Test quantity of bytes data for multiple write (Coils).
 *  @param  MBRTUIn - pointer to Data structure.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->RxNumBytes (set, test)
 *           ~ MBRTUIn->RxExc      (set)
 *             MBRTUIn->RxNumRegs
 *             MBRTUIn->RxBuff
 */
uint8_t MBRTU_TestCoilNBytes(MBRTU_t *MBRTUIn);

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
uint8_t MBRTU_TestCoilAddr(MBRTU_t *MBRTUIn);

/** @brief  Test request to table of Dicrete inputs.
 *  @param  MBRTUIn - pointer to Data structure.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *             MBRTUIn->RxCnt  (test)
 *           ~ MBRTUIn->RxExc  (set)
 */
uint8_t MBRTU_TestDiscReq(MBRTU_t *MBRTUIn);

/** @brief  Test quantity of Dicrete inputs.
 *  @param  MBRTUIn - pointer to Data structure.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->RxNumRegs (set, test)
 *           ~ MBRTUIn->RxExc     (set)
 *             MBRTUIn->RxBuff
 */
uint8_t MBRTU_TestDiscNRegs(MBRTU_t *MBRTUIn);

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
uint8_t MBRTU_TestDiscAddr(MBRTU_t *MBRTUIn);


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
uint8_t MBRTU_ReadDiscretes(MBRTU_t *MBRTUIn, uint8_t TableIn);


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
uint8_t MBRTU_WriteCoils(MBRTU_t *MBRTUIn, uint8_t ModeIn);


/** @brief  Test request to diagnostics.
 *  @param  MBRTUIn - pointer to Data structure.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *             MBRTUIn->RxCnt  (test)
 *           ~ MBRTUIn->RxExc  (change)
 */
uint8_t MBRTU_TestDiagReq(MBRTU_t *MBRTUIn);

/** @brief  Handler of diagnostics sub-function code (Echo).
 *  @param  MBRTUIn - pointer to Data structure.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->TxCnt  (change)
 *           ~ MBRTUIn->TxBuff (change)
 */
uint8_t MBRTU_DiagEcho(MBRTU_t *MBRTUIn);

/** @brief  Handler of diagnostics sub-function code (Return Counter).
 *  @param  MBRTUIn - pointer to Data structure.
 *  @param  CntIn   - counter value
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->TxCnt  (change)
 *           ~ MBRTUIn->TxBuff (change)
 *             MBRTUIn->SubFunc
 */
uint8_t MBRTU_DiagCount(MBRTU_t *MBRTUIn, uint16_t CntIn);

/** @brief  Handler of request to diagnostics.
 *  @param  MBRTUIn - pointer to Data structure.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->RxExc     (change)
 *           ~ MBRTUIn->TxCnt     (change)
 *           ~ MBRTUIn->TxBuff    (change)
 *             MBRTUIn->RxNumRegs
 *             MBRTUIn->RxStartAddr
 *             MBRTUIn->RxEndAddr
 */
uint8_t MBRTU_Diagnostics(MBRTU_t *MBRTUIn);


/** @brief  Create response.
 *  @param  MBRTUIn - pointer to Data structure.
 *  @return Exception code.
 *  @details Fields of MBRTUIn whose values will be used here:
 *           ~ MBRTUIn->RxExc  (set, test)
 *             MBRTUIn->RxFunc
 */
uint8_t MBRTU_CreateRes(MBRTU_t *MBRTUIn);


#endif //MBRTU_H
