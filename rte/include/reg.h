/* @page reg.h
 *       PLC411::RTE
 *       Registers :: API (Common)
 *       2022, atgroup09@gmail.com
 */

#ifndef REG_H
#define REG_H

#include "config.h"

#include "reg-map.h"
#include "rtos.h"

#ifdef RTE_MOD_APP
#include "plc_app.h"
#endif // RTE_MOD_APP

#ifdef DEBUG
#include "debug-log.h"
#endif // DEBUG


/** @typedef Register
 */
typedef struct REG_t_
{
	//@var Group ID
	uint8_t GroupID;

    //@var Unique ID of group/subgroup
    uint8_t GID;

    //@var Position in group/subgroup (channel number)
    uint8_t iGroup;

    //@var Position in REGS
    uint16_t iReg;

    //@var Data type ID (type.h)
    uint8_t Type;

    //@var Get size (words) of data type (type.h)
    uint8_t Wsz;

    //@var Data Table ID (reg-map.h)
    uint8_t  DataTable;

    //@var Pointer to ModBus (Data) table
    void *pMbVar;

#ifdef RTE_MOD_APP
    //@var Pointer to Application located variable
    plc_loc_dsc_t *pAppVar;
#endif //RTE_MOD_APP

    //@var ModBus Table ID (mbrtu.h)
    uint8_t  MbTable;

    //@var ModBus Address
    uint16_t MbAddr;

    //@var Retain Address (FLASH/EEPROM)
    uint16_t Retain;

    //@var Use Change-monitoring (0 - off, 1 - on)
    uint8_t Monitor;

} REG_t;


/** @def Destination of copy
 *       *_TO_MB, *_TO_APP, *_TO_ALL - with change-monitoring
 *       *_NO_MON                    - without change-monitoring
 */
#define REG_COPY_APP_TO_MB              0  //copy Located variable into Data Table
#define REG_COPY_APP_TO_MB__NO_MON      10
#define REG_COPY_MB_TO_APP              1  //copy Data Table into Located variable
#define REG_COPY_VAR_TO_APP             3  //copy Variable into Located variable
#define REG_COPY_MB_TO_VAR              2  //copy Data Table into Variable
#define REG_COPY_VAR_TO_MB              4  //copy Variable into Data Table
#define REG_COPY_VAR_TO_MB__NO_MON      14
#define REG_COPY_VAR_TO_ALL             5  //copy Variable into Located variable, Data Table
#define REG_COPY_VAR_TO_ALL__NO_MON     15


/** @brief  Get pointer to register by position in REGS.
 *  @param  IDxIn - position in REGS.
 *  @return Pointer to register or 0 if error.
 */
REG_t *REG_GetByIDx(uint16_t IDxIn);

/** @brief  Get pointer to register by start position.
 *  @param  SPosIn   - start position of register group in REGS (ex.: REG_DI_NORM_VAL__POS).
 *  @param  iGroupIn - position of register in the group (>= 0) (iGroup).
 *  @return Pointer to register or 0 if error.
 */
REG_t *REG_GetByPos(uint16_t SPosIn, int32_t iGroupIn);

/** @brief  Get pointer to register by ModBus address.
 *  @param  MbTableIn - ModBus Table ID (mbrtu.h).
 *  @param  MbAddrIn  - ModBus Register address.
 *  @return Pointer to register or 0 if error.
 */
REG_t *REG_GetByMbAddr(uint8_t MbTableIn, uint16_t MbAddrIn);


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
uint8_t REG_CopyWords(uint16_t *FromIn, uint16_t FromSzIn, uint16_t *ToIn, uint8_t MbTableIn, uint16_t MbAddrIn);

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
uint8_t REG_CopyValueToMb(uint8_t TypeIn, uint8_t *ValueBitIn, uint16_t *ValueWordIn, uint8_t MbTableIn, uint16_t MbAddrIn, void *MbVarIn, uint8_t MonIn);

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
uint8_t REG_CopyWordsToMb(REG_t *RegIn, uint16_t *FromIn, uint8_t FromSzIn, uint8_t FromOrdIn, uint8_t ZeroedIn, uint8_t MonIn);

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
uint8_t REG_CopyValueFromMb(uint8_t TypeIn, uint8_t *ValueBitIn, uint16_t *ValueWordIn, uint8_t MbTableIn, void *MbVarIn);

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
uint8_t REG_CopyWordsFromMb(REG_t *RegIn, uint16_t *ToIn, uint8_t ToSzIn, uint8_t ToOrdIn, uint8_t ZeroedIn);

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
uint8_t REG_CopyUnsignedAppToMb(REG_t *RegIn);
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
uint8_t REG_CopyUnsignedMbToVar(REG_t *RegIn, void *VarIn);

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
uint8_t REG_CopyUnsignedMbToApp(REG_t *RegIn);
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
uint8_t REG_CopyUnsignedVarToMb(REG_t *RegIn, const void *VarIn);

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
uint8_t REG_CopyUnsignedVarToApp(REG_t *RegIn, const void *VarIn);
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
uint8_t REG_CopyUnsigned(REG_t *RegIn, uint8_t DstIn, void *VarIn);

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
uint8_t REG_CopySignedAppToMb(REG_t *RegIn);
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
uint8_t REG_CopySignedMbToVar(REG_t *RegIn, void *VarIn);

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
uint8_t REG_CopySignedMbToApp(REG_t *RegIn);
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
uint8_t REG_CopySignedVarToMb(REG_t *RegIn, const void *VarIn);

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
uint8_t REG_CopySignedVarToApp(REG_t *RegIn, const void *VarIn);
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
uint8_t REG_CopySigned(REG_t *RegIn, uint8_t DstIn, void *VarIn);

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
uint8_t REG_CopyFloatAppToMb(REG_t *RegIn);
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
uint8_t REG_CopyFloatMbToVar(REG_t *RegIn, void *VarIn);

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
uint8_t REG_CopyFloatMbToApp(REG_t *RegIn);
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
uint8_t REG_CopyFloatVarToMb(REG_t *RegIn, const void *VarIn);

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
uint8_t REG_CopyFloatVarToApp(REG_t *RegIn, const void *VarIn);
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
uint8_t REG_CopyFloat(REG_t *RegIn, uint8_t DstIn, void *VarIn);

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
uint8_t REG_CopyDoubleAppToMb(REG_t *RegIn);
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
uint8_t REG_CopyDoubleMbToVar(REG_t *RegIn, void *VarIn);

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
uint8_t REG_CopyDoubleMbToApp(REG_t *RegIn);
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
uint8_t REG_CopyDoubleVarToMb(REG_t *RegIn, const void *VarIn);

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
uint8_t REG_CopyDoubleVarToApp(REG_t *RegIn, const void *VarIn);
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
uint8_t REG_CopyDouble(REG_t *RegIn, uint8_t DstIn, void *VarIn);

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
uint8_t REG_CopyReg(REG_t *RegIn, uint8_t DstIn, void *VarIn);

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
uint8_t REG_CopyVar(REG_t *RegIn, uint8_t DstIn, const void *VarIn, uint8_t VarTypeIn);

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
uint8_t REG_CopyRegByPos(uint16_t RegPosIn, uint8_t DstIn, void *VarIn);

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
uint16_t REG_CopyRegs(uint16_t PosIn, uint16_t SzIn, uint8_t DstIn, void *VarIn);


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
uint16_t REG_InitRegs(uint16_t GIDIn, uint8_t ZoneIn, uint8_t TypeSzIn, uint16_t GroupIn, uint8_t TypeIn, uint16_t PosIn, uint16_t SzIn, uint16_t SaddrIn, uint8_t MbTableIn, uint16_t MbPosIn, int32_t A00In, int32_t A01In, int32_t A02In, uint8_t DataTableIn, uint16_t DataPosIn, uint16_t RetainIn, const char *TitleIn);


/** @brief  Clear Data Tables.
 *  @param  None.
 *  @return None.
 */
void REG_Clear(void);


#endif //REG_H
