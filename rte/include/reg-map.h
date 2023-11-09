/* @page reg-map.h
 *       PLC411::RTE
 *       Registers :: Map
 *       2022-2023, atgroup09@gmail.com
 */

/** @note
 *        After update this RegMap:
 *
 *		  1) update reg.c::REG_GetByMbAddr()
 *		  2) update reg-init.c::REG_Init()
 *		  3) update reg-init.c::REG_CopyMbToApp()
 *		  4) update reg-init.c::REG_CopyAppToMb()
 *		  5) update reg-init.c::REG_SetDef()
 */

#ifndef REG_MAP_H
#define REG_MAP_H

#include <stdint.h>
#include "config.h"

#include "plc_abi.h"


/** @def    Calc. Register position (offset) from previous group of registers.
 *  @param  PrePosIn - start position (offset) of previous group.
 *  @param  PreSzIn  - quantity of registers in previous group.
 *  @return Start position (offset) of the register.
 */
#define REG_CALC_POS(PrePosIn, PreSzIn)                        (PrePosIn+PreSzIn)

/** @def    Calc. Register position in a group (iGroup) by ModBus address.
 *  @param  MbAddrIn - ModBus address.
 *  @param  SMbPosIn - start ModBus address of the register group.
 *  @param  NwIn     - quantity of words for the register.
 *  @return Register position in a group (iGroup) or -1. [int32_t]
 */
#define REG_CALC_POS_BY_MBADDR(MbAddrIn, SMbPosIn, NwIn)       ((NwIn > 0) ? (int32_t)((MbAddrIn-SMbPosIn)/NwIn) : (int32_t)-1)


/** @def    Calc. ModBus position (offset) from previous group of registers.
 *  @param  PrePosIn - ModBus position (offset) of previous group.
 *  @param  PreSzIn  - quantity of registers in previous group.
 *  @param  PreNwIn  - quantity of words for one register of previous group.
 *  @param  ResSzIn  - quantity of reserve registers.
 *  @return ModBus position (offset).
 */
#define REG_CALC_MBPOS(PrePosIn, PreSzIn, PreNwIn, ResSzIn)    (((PreSzIn*PreNwIn)+PrePosIn)+(ResSzIn*PreNwIn))

/** @def    Calc. ModBus address.
 *  @param  SaddrIn  - start address of register (0...N) in the group.
 *  @param  NwIn     - quantity of words for the register.
 *  @param  PosIn    - start ModBus position (offset) of the group.
 *  @return ModBus address.
 */
#define REG_CALC_MBADDR(SaddrIn, NwIn, MbPosIn)                ((SaddrIn*NwIn)+MbPosIn)


/** @note
 *       *__ZONE   - ID of memory     (plc_app.v_type)
 *       *__TYPESZ - ID of data type  (plc_app.v_size)
 *       *__GROUP  - ID of group      (plc_app.proto)
 *       *__A00    - ID of subgroup 0 (plc_app.a_data[0])
 *       *__A01    - ID of subgroup 1 (plc_app.a_data[1])
 *       *__A02    - ID of subgroup 2 (plc_app.a_data[2])
 */

/** @def Subgroup A00..02 is not used
 */
#define REG_AXX_NONE                   (int32_t)-1

/** @def Subgroup A00..02 is register address
 */
#define REG_AXX_ADDR                   (int32_t)-10

//=============================================================================

/** @def Data Table ID
 */
#define REG_DATA_BOOL_TABLE_ID         (uint8_t)1  //Boolean
#define REG_DATA_NUMB_TABLE_ID         (uint8_t)2  //Numeric

//=============================================================================

/** @def ModBus Table ID
 */
#define MBRTU_COIL_TABLE_ID            (uint8_t)1
#define MBRTU_DISC_TABLE_ID            (uint8_t)2
#define MBRTU_HOLD_TABLE_ID            (uint8_t)3
#define MBRTU_INPT_TABLE_ID            (uint8_t)4

//=============================================================================

/** @def Retain Values
 */
#define REG_RETAIN_ALL                (uint16_t)0xFFFF
#define REG_RETAIN_NONE               (uint16_t)0

//=============================================================================

/** @def Reserve space (the quantity of registers)
 */
#define REG_RESERVE                    (uint8_t)0


// REGMAP (START) =============================================================
//=============================================================================
//=============================================================================

//DI

#include "di.h"

#define REG_DI__GROUP                           (uint16_t)1

/** @def DI_NORM_VAL
 */
#define REG_DI_NORM_VAL__GID                     (uint16_t)10          //Unique ID
// located variable
#define REG_DI_NORM_VAL__ZONE                    PLC_LT_I              //ID of memory
#define REG_DI_NORM_VAL__TYPESZ                  PLC_LSZ_X             //ID of data type
#define REG_DI_NORM_VAL__GROUP                   REG_DI__GROUP         //ID of group
#define REG_DI_NORM_VAL__A00                     REG_AXX_ADDR
#define REG_DI_NORM_VAL__A01                     (int32_t)1            //ID of subgroup by mode
#define REG_DI_NORM_VAL__A02                     (int32_t)1            //ID of register
#define REG_DI_NORM_VAL__TYPE                    TYPE_BOOL             //Data type
#define REG_DI_NORM_VAL__TYPE_SZ                 TYPE_BOOL_SZ          //Size of data type in bytes
#define REG_DI_NORM_VAL__TYPE_WSZ                TYPE_BOOL_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DI_NORM_VAL__SZ                      (uint16_t)PLC_DI_SZ   //Number of registers
#define REG_DI_NORM_VAL__POS                     (uint16_t)0
#define REG_DI_NORM_VAL__SADDR                   (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DI_NORM_VAL__DPOS                    (uint16_t)0
#define REG_DI_NORM_VAL__DPOS_END                (uint16_t)REG_CALC_MBPOS(REG_DI_NORM_VAL__DPOS, REG_DI_NORM_VAL__SZ, REG_DI_NORM_VAL__TYPE_WSZ, 0)-1
#define REG_DI_NORM_VAL__DTABLE                  REG_DATA_BOOL_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DI_NORM_VAL__MBPOS                   (uint16_t)0
#define REG_DI_NORM_VAL__MBPOS_END               (uint16_t)REG_CALC_MBPOS(REG_DI_NORM_VAL__MBPOS, REG_DI_NORM_VAL__SZ, REG_DI_NORM_VAL__TYPE_WSZ, 0)-1
#define REG_DI_NORM_VAL__MBTABLE                 MBRTU_DISC_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DI_NORM_VAL__RETAIN                  REG_RETAIN_NONE
//STRING
#define REG_DI_NORM_VAL__STR                     "DI%d Norm: Value"

/** @def DI_TACH_VAL
 */
#define REG_DI_TACH_VAL__GID                     (uint16_t)11          //Unique ID
// located variable
#define REG_DI_TACH_VAL__ZONE                    PLC_LT_I              //ID of memory
#define REG_DI_TACH_VAL__TYPESZ                  PLC_LSZ_W             //ID of data type
#define REG_DI_TACH_VAL__GROUP                   REG_DI__GROUP         //ID of group
#define REG_DI_TACH_VAL__A00                     REG_AXX_ADDR
#define REG_DI_TACH_VAL__A01                     (int32_t)2            //ID of subgroup by mode
#define REG_DI_TACH_VAL__A02                     (int32_t)1            //ID of register
#define REG_DI_TACH_VAL__TYPE                    TYPE_WORD             //Data type
#define REG_DI_TACH_VAL__TYPE_SZ                 TYPE_WORD_SZ          //Size of data type in bytes
#define REG_DI_TACH_VAL__TYPE_WSZ                TYPE_WORD_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DI_TACH_VAL__SZ                      (uint16_t)PLC_DI_SZ   //Number of registers
#define REG_DI_TACH_VAL__POS                     (uint16_t)REG_CALC_POS(REG_DI_NORM_VAL__POS, REG_DI_NORM_VAL__SZ)
#define REG_DI_TACH_VAL__SADDR                   (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DI_TACH_VAL__DPOS                    (uint16_t)0
#define REG_DI_TACH_VAL__DPOS_END                (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_VAL__DPOS, REG_DI_TACH_VAL__SZ, REG_DI_TACH_VAL__TYPE_WSZ, 0)-1
#define REG_DI_TACH_VAL__DTABLE                  REG_DATA_NUMB_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DI_TACH_VAL__MBPOS                   (uint16_t)0
#define REG_DI_TACH_VAL__MBPOS_END               (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_VAL__MBPOS, REG_DI_TACH_VAL__SZ, REG_DI_TACH_VAL__TYPE_WSZ, 0)-1
#define REG_DI_TACH_VAL__MBTABLE                 MBRTU_INPT_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DI_TACH_VAL__RETAIN                  REG_RETAIN_NONE
//STRING
#define REG_DI_TACH_VAL__STR                     "DI%d Tach: Value"

/** @def DI_TACH_SETPOINT
 */
#define REG_DI_TACH_SETPOINT__GID                (uint16_t)111         //Unique ID
// located variable
#define REG_DI_TACH_SETPOINT__ZONE               PLC_LT_M              //ID of memory
#define REG_DI_TACH_SETPOINT__TYPESZ             PLC_LSZ_W             //ID of data type
#define REG_DI_TACH_SETPOINT__GROUP              REG_DI__GROUP         //ID of group
#define REG_DI_TACH_SETPOINT__A00                REG_AXX_ADDR
#define REG_DI_TACH_SETPOINT__A01                (int32_t)2            //ID of subgroup by mode
#define REG_DI_TACH_SETPOINT__A02                (int32_t)2            //ID of register
#define REG_DI_TACH_SETPOINT__TYPE               TYPE_WORD             //Data type
#define REG_DI_TACH_SETPOINT__TYPE_SZ            TYPE_WORD_SZ          //Size of data type in bytes
#define REG_DI_TACH_SETPOINT__TYPE_WSZ           TYPE_WORD_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DI_TACH_SETPOINT__SZ                 (uint16_t)PLC_DI_SZ   //Number of registers
#define REG_DI_TACH_SETPOINT__POS                (uint16_t)REG_CALC_POS(REG_DI_TACH_VAL__POS, REG_DI_TACH_VAL__SZ)
#define REG_DI_TACH_SETPOINT__SADDR              (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DI_TACH_SETPOINT__DPOS               (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_VAL__DPOS, REG_DI_TACH_VAL__SZ, REG_DI_TACH_VAL__TYPE_WSZ, 0)
#define REG_DI_TACH_SETPOINT__DPOS_END           (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_SETPOINT__DPOS, REG_DI_TACH_SETPOINT__SZ, REG_DI_TACH_SETPOINT__TYPE_WSZ, 0)-1
#define REG_DI_TACH_SETPOINT__DTABLE             REG_DATA_NUMB_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DI_TACH_SETPOINT__MBPOS              (uint16_t)0
#define REG_DI_TACH_SETPOINT__MBPOS_END          (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_SETPOINT__MBPOS, REG_DI_TACH_SETPOINT__SZ, REG_DI_TACH_SETPOINT__TYPE_WSZ, 0)-1
#define REG_DI_TACH_SETPOINT__MBTABLE            MBRTU_HOLD_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DI_TACH_SETPOINT__RETAIN             REG_RETAIN_ALL
//STRING
#define REG_DI_TACH_SETPOINT__STR                "DI%d Tach: Setpoint"

/** @def DI_TACH_SETPOINT_ALLOW
 */
#define REG_DI_TACH_SETPOINT_ALLOW__GID          (uint16_t)112         //Unique ID
// located variable
#define REG_DI_TACH_SETPOINT_ALLOW__ZONE         PLC_LT_M              //ID of memory
#define REG_DI_TACH_SETPOINT_ALLOW__TYPESZ       PLC_LSZ_X             //ID of data type
#define REG_DI_TACH_SETPOINT_ALLOW__GROUP        REG_DI__GROUP         //ID of group
#define REG_DI_TACH_SETPOINT_ALLOW__A00          REG_AXX_ADDR
#define REG_DI_TACH_SETPOINT_ALLOW__A01          (int32_t)2            //ID of subgroup by mode
#define REG_DI_TACH_SETPOINT_ALLOW__A02          (int32_t)3            //ID of register
#define REG_DI_TACH_SETPOINT_ALLOW__TYPE         TYPE_BOOL             //Data type
#define REG_DI_TACH_SETPOINT_ALLOW__TYPE_SZ      TYPE_BOOL_SZ          //Size of data type in bytes
#define REG_DI_TACH_SETPOINT_ALLOW__TYPE_WSZ     TYPE_BOOL_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DI_TACH_SETPOINT_ALLOW__SZ           (uint16_t)PLC_DI_SZ   //Number of registers
#define REG_DI_TACH_SETPOINT_ALLOW__POS          (uint16_t)REG_CALC_POS(REG_DI_TACH_SETPOINT__POS, REG_DI_TACH_SETPOINT__SZ)
#define REG_DI_TACH_SETPOINT_ALLOW__SADDR        (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DI_TACH_SETPOINT_ALLOW__DPOS         (uint16_t)REG_CALC_MBPOS(REG_DI_NORM_VAL__DPOS, REG_DI_NORM_VAL__SZ, REG_DI_NORM_VAL__TYPE_WSZ, 0)
#define REG_DI_TACH_SETPOINT_ALLOW__DPOS_END     (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_SETPOINT_ALLOW__DPOS, REG_DI_TACH_SETPOINT_ALLOW__SZ, REG_DI_TACH_SETPOINT_ALLOW__TYPE_WSZ, 0)-1
#define REG_DI_TACH_SETPOINT_ALLOW__DTABLE       REG_DATA_BOOL_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DI_TACH_SETPOINT_ALLOW__MBPOS        (uint16_t)0
#define REG_DI_TACH_SETPOINT_ALLOW__MBPOS_END    (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_SETPOINT_ALLOW__MBPOS, REG_DI_TACH_SETPOINT_ALLOW__SZ, REG_DI_TACH_SETPOINT_ALLOW__TYPE_WSZ, 0)-1
#define REG_DI_TACH_SETPOINT_ALLOW__MBTABLE      MBRTU_COIL_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DI_TACH_SETPOINT_ALLOW__RETAIN       REG_RETAIN_ALL
//STRING
#define REG_DI_TACH_SETPOINT_ALLOW__STR          "DI%d Tach: Allow to work by setpoint"

/** @def DI_TACH_SETPOINT_REACHED
 */
#define REG_DI_TACH_SETPOINT_REACHED__GID        (uint16_t)113         //Unique ID
// located variable
#define REG_DI_TACH_SETPOINT_REACHED__ZONE       PLC_LT_M              //ID of memory
#define REG_DI_TACH_SETPOINT_REACHED__TYPESZ     PLC_LSZ_X             //ID of data type
#define REG_DI_TACH_SETPOINT_REACHED__GROUP      REG_DI__GROUP         //ID of group
#define REG_DI_TACH_SETPOINT_REACHED__A00        REG_AXX_ADDR
#define REG_DI_TACH_SETPOINT_REACHED__A01        (int32_t)2            //ID of subgroup by mode
#define REG_DI_TACH_SETPOINT_REACHED__A02        (int32_t)4            //ID of register
#define REG_DI_TACH_SETPOINT_REACHED__TYPE       TYPE_BOOL             //Data type
#define REG_DI_TACH_SETPOINT_REACHED__TYPE_SZ    TYPE_BOOL_SZ          //Size of data type in bytes
#define REG_DI_TACH_SETPOINT_REACHED__TYPE_WSZ   TYPE_BOOL_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DI_TACH_SETPOINT_REACHED__SZ         (uint16_t)PLC_DI_SZ   //Number of registers
#define REG_DI_TACH_SETPOINT_REACHED__POS        (uint16_t)REG_CALC_POS(REG_DI_TACH_SETPOINT_ALLOW__POS, REG_DI_TACH_SETPOINT_ALLOW__SZ)
#define REG_DI_TACH_SETPOINT_REACHED__SADDR      (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DI_TACH_SETPOINT_REACHED__DPOS       (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_SETPOINT_ALLOW__DPOS, REG_DI_TACH_SETPOINT_ALLOW__SZ, REG_DI_TACH_SETPOINT_ALLOW__TYPE_WSZ, 0)
#define REG_DI_TACH_SETPOINT_REACHED__DPOS_END   (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_SETPOINT_REACHED__DPOS, REG_DI_TACH_SETPOINT_REACHED__SZ, REG_DI_TACH_SETPOINT_REACHED__TYPE_WSZ, 0)-1
#define REG_DI_TACH_SETPOINT_REACHED__DTABLE     REG_DATA_BOOL_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DI_TACH_SETPOINT_REACHED__MBPOS      (uint16_t)REG_CALC_MBPOS(REG_DI_NORM_VAL__MBPOS, REG_DI_NORM_VAL__SZ, REG_DI_NORM_VAL__TYPE_WSZ, REG_RESERVE)
#define REG_DI_TACH_SETPOINT_REACHED__MBPOS_END  (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_SETPOINT_REACHED__MBPOS, REG_DI_TACH_SETPOINT_REACHED__SZ, REG_DI_TACH_SETPOINT_REACHED__TYPE_WSZ, 0)-1
#define REG_DI_TACH_SETPOINT_REACHED__MBTABLE    MBRTU_DISC_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DI_TACH_SETPOINT_REACHED__RETAIN     REG_RETAIN_NONE
//STRING
#define REG_DI_TACH_SETPOINT_REACHED__STR        "DI%d Tach: Setpoint is reached"

/** @def DI_CNTR_VAL
 */
#define REG_DI_CNTR_VAL__GID                     (uint16_t)12          //Unique ID
// located variable
#define REG_DI_CNTR_VAL__ZONE                    PLC_LT_I              //ID of memory
#define REG_DI_CNTR_VAL__TYPESZ                  PLC_LSZ_D             //ID of data type
#define REG_DI_CNTR_VAL__GROUP                   REG_DI__GROUP         //ID of group
#define REG_DI_CNTR_VAL__A00                     REG_AXX_ADDR
#define REG_DI_CNTR_VAL__A01                     (int32_t)3            //ID of subgroup by mode
#define REG_DI_CNTR_VAL__A02                     (int32_t)1            //ID of register
#define REG_DI_CNTR_VAL__TYPE                    TYPE_DWORD            //Data type
#define REG_DI_CNTR_VAL__TYPE_SZ                 TYPE_DWORD_SZ         //Size of data type in bytes
#define REG_DI_CNTR_VAL__TYPE_WSZ                TYPE_DWORD_WSZ        //Size of data type in words
// position (offset) in REGS
#define REG_DI_CNTR_VAL__SZ                      (uint16_t)PLC_DI_SZ   //Number of registers
#define REG_DI_CNTR_VAL__POS                     (uint16_t)REG_CALC_POS(REG_DI_TACH_SETPOINT_REACHED__POS, REG_DI_TACH_SETPOINT_REACHED__SZ)
#define REG_DI_CNTR_VAL__SADDR                   (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DI_CNTR_VAL__DPOS                    (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_SETPOINT__DPOS, REG_DI_TACH_SETPOINT__SZ, REG_DI_TACH_SETPOINT__TYPE_WSZ, 0)
#define REG_DI_CNTR_VAL__DPOS_END                (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_VAL__DPOS, REG_DI_CNTR_VAL__SZ, REG_DI_CNTR_VAL__TYPE_WSZ, 0)-1
#define REG_DI_CNTR_VAL__DTABLE                  REG_DATA_NUMB_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DI_CNTR_VAL__MBPOS                   (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_VAL__MBPOS, REG_DI_TACH_VAL__SZ, REG_DI_TACH_VAL__TYPE_WSZ, REG_RESERVE)
#define REG_DI_CNTR_VAL__MBPOS_END               (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_VAL__MBPOS, REG_DI_CNTR_VAL__SZ, REG_DI_CNTR_VAL__TYPE_WSZ, 0)-1
#define REG_DI_CNTR_VAL__MBTABLE                 MBRTU_INPT_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DI_CNTR_VAL__RETAIN                  REG_RETAIN_NONE
//STRING
#define REG_DI_CNTR_VAL__STR                     "DI%d Cntr: Value"

/** @def DI_CNTR_SETPOINT
 */
#define REG_DI_CNTR_SETPOINT__GID                (uint16_t)121          //Unique ID
// located variable
#define REG_DI_CNTR_SETPOINT__ZONE               PLC_LT_M              //ID of memory
#define REG_DI_CNTR_SETPOINT__TYPESZ             PLC_LSZ_D             //ID of data type
#define REG_DI_CNTR_SETPOINT__GROUP              REG_DI__GROUP         //ID of group
#define REG_DI_CNTR_SETPOINT__A00                REG_AXX_ADDR
#define REG_DI_CNTR_SETPOINT__A01                (int32_t)3            //ID of subgroup by mode
#define REG_DI_CNTR_SETPOINT__A02                (int32_t)2            //ID of register
#define REG_DI_CNTR_SETPOINT__TYPE               TYPE_DWORD            //Data type
#define REG_DI_CNTR_SETPOINT__TYPE_SZ            TYPE_DWORD_SZ         //Size of data type in bytes
#define REG_DI_CNTR_SETPOINT__TYPE_WSZ           TYPE_DWORD_WSZ        //Size of data type in words
// position (offset) in REGS
#define REG_DI_CNTR_SETPOINT__SZ                 (uint16_t)PLC_DI_SZ   //Number of registers
#define REG_DI_CNTR_SETPOINT__POS                (uint16_t)REG_CALC_POS(REG_DI_CNTR_VAL__POS, REG_DI_CNTR_VAL__SZ)
#define REG_DI_CNTR_SETPOINT__SADDR              (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DI_CNTR_SETPOINT__DPOS               (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_VAL__DPOS, REG_DI_CNTR_VAL__SZ, REG_DI_CNTR_VAL__TYPE_WSZ, 0)
#define REG_DI_CNTR_SETPOINT__DPOS_END           (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_SETPOINT__DPOS, REG_DI_CNTR_SETPOINT__SZ, REG_DI_CNTR_SETPOINT__TYPE_WSZ, 0)-1
#define REG_DI_CNTR_SETPOINT__DTABLE             REG_DATA_NUMB_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DI_CNTR_SETPOINT__MBPOS              (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_SETPOINT__MBPOS, REG_DI_TACH_SETPOINT__SZ, REG_DI_TACH_SETPOINT__TYPE_WSZ, REG_RESERVE)
#define REG_DI_CNTR_SETPOINT__MBPOS_END          (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_SETPOINT__MBPOS, REG_DI_CNTR_SETPOINT__SZ, REG_DI_CNTR_SETPOINT__TYPE_WSZ, 0)-1
#define REG_DI_CNTR_SETPOINT__MBTABLE            MBRTU_HOLD_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DI_CNTR_SETPOINT__RETAIN             REG_RETAIN_ALL
//STRING
#define REG_DI_CNTR_SETPOINT__STR                "DI%d Cntr: Setpoint"

/** @def DI_CNTR_SETPOINT_ALLOW
 */
#define REG_DI_CNTR_SETPOINT_ALLOW__GID          (uint16_t)122         //Unique ID
// located variable
#define REG_DI_CNTR_SETPOINT_ALLOW__ZONE         PLC_LT_M              //ID of memory
#define REG_DI_CNTR_SETPOINT_ALLOW__TYPESZ       PLC_LSZ_X             //ID of data type
#define REG_DI_CNTR_SETPOINT_ALLOW__GROUP        REG_DI__GROUP         //ID of group
#define REG_DI_CNTR_SETPOINT_ALLOW__A00          REG_AXX_ADDR
#define REG_DI_CNTR_SETPOINT_ALLOW__A01          (int32_t)3            //ID of subgroup by mode
#define REG_DI_CNTR_SETPOINT_ALLOW__A02          (int32_t)3            //ID of register
#define REG_DI_CNTR_SETPOINT_ALLOW__TYPE         TYPE_BOOL             //Data type
#define REG_DI_CNTR_SETPOINT_ALLOW__TYPE_SZ      TYPE_BOOL_SZ          //Size of data type in bytes
#define REG_DI_CNTR_SETPOINT_ALLOW__TYPE_WSZ     TYPE_BOOL_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DI_CNTR_SETPOINT_ALLOW__SZ           (uint16_t)PLC_DI_SZ   //Number of registers
#define REG_DI_CNTR_SETPOINT_ALLOW__POS          (uint16_t)REG_CALC_POS(REG_DI_CNTR_SETPOINT__POS, REG_DI_CNTR_SETPOINT__SZ)
#define REG_DI_CNTR_SETPOINT_ALLOW__SADDR        (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DI_CNTR_SETPOINT_ALLOW__DPOS         (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_SETPOINT_REACHED__DPOS, REG_DI_TACH_SETPOINT_REACHED__SZ, REG_DI_TACH_SETPOINT_REACHED__TYPE_WSZ, 0)
#define REG_DI_CNTR_SETPOINT_ALLOW__DPOS_END     (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_SETPOINT_ALLOW__DPOS, REG_DI_CNTR_SETPOINT_ALLOW__SZ, REG_DI_CNTR_SETPOINT_ALLOW__TYPE_WSZ, 0)-1
#define REG_DI_CNTR_SETPOINT_ALLOW__DTABLE       REG_DATA_BOOL_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DI_CNTR_SETPOINT_ALLOW__MBPOS        (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_SETPOINT_ALLOW__MBPOS, REG_DI_TACH_SETPOINT_ALLOW__SZ, REG_DI_TACH_SETPOINT_ALLOW__TYPE_WSZ, REG_RESERVE)
#define REG_DI_CNTR_SETPOINT_ALLOW__MBPOS_END    (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_SETPOINT_ALLOW__MBPOS, REG_DI_CNTR_SETPOINT_ALLOW__SZ, REG_DI_CNTR_SETPOINT_ALLOW__TYPE_WSZ, 0)-1
#define REG_DI_CNTR_SETPOINT_ALLOW__MBTABLE      MBRTU_COIL_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DI_CNTR_SETPOINT_ALLOW__RETAIN       REG_RETAIN_ALL
//STRING
#define REG_DI_CNTR_SETPOINT_ALLOW__STR          "DI%d Cntr: Allow to work by setpoint"

/** @def DI_CNTR_SETPOINT_REACHED
 */
#define REG_DI_CNTR_SETPOINT_REACHED__GID        (uint16_t)123         //Unique ID
// located variable
#define REG_DI_CNTR_SETPOINT_REACHED__ZONE       PLC_LT_M              //ID of memory
#define REG_DI_CNTR_SETPOINT_REACHED__TYPESZ     PLC_LSZ_X             //ID of data type
#define REG_DI_CNTR_SETPOINT_REACHED__GROUP      REG_DI__GROUP         //ID of group
#define REG_DI_CNTR_SETPOINT_REACHED__A00        REG_AXX_ADDR
#define REG_DI_CNTR_SETPOINT_REACHED__A01        (int32_t)3            //ID of subgroup by mode
#define REG_DI_CNTR_SETPOINT_REACHED__A02        (int32_t)4            //ID of register
#define REG_DI_CNTR_SETPOINT_REACHED__TYPE       TYPE_BOOL             //Data type
#define REG_DI_CNTR_SETPOINT_REACHED__TYPE_SZ    TYPE_BOOL_SZ          //Size of data type in bytes
#define REG_DI_CNTR_SETPOINT_REACHED__TYPE_WSZ   TYPE_BOOL_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DI_CNTR_SETPOINT_REACHED__SZ         (uint16_t)PLC_DI_SZ   //Number of registers
#define REG_DI_CNTR_SETPOINT_REACHED__POS        (uint16_t)REG_CALC_POS(REG_DI_CNTR_SETPOINT_ALLOW__POS, REG_DI_CNTR_SETPOINT_ALLOW__SZ)
#define REG_DI_CNTR_SETPOINT_REACHED__SADDR      (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DI_CNTR_SETPOINT_REACHED__DPOS       (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_SETPOINT_ALLOW__DPOS, REG_DI_CNTR_SETPOINT_ALLOW__SZ, REG_DI_CNTR_SETPOINT_ALLOW__TYPE_WSZ, 0)
#define REG_DI_CNTR_SETPOINT_REACHED__DPOS_END   (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_SETPOINT_REACHED__DPOS, REG_DI_CNTR_SETPOINT_REACHED__SZ, REG_DI_CNTR_SETPOINT_REACHED__TYPE_WSZ, 0)-1
#define REG_DI_CNTR_SETPOINT_REACHED__DTABLE     REG_DATA_BOOL_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DI_CNTR_SETPOINT_REACHED__MBPOS      (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_SETPOINT_REACHED__MBPOS, REG_DI_TACH_SETPOINT_REACHED__SZ, REG_DI_TACH_SETPOINT_REACHED__TYPE_WSZ, REG_RESERVE)
#define REG_DI_CNTR_SETPOINT_REACHED__MBPOS_END  (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_SETPOINT_REACHED__MBPOS, REG_DI_CNTR_SETPOINT_REACHED__SZ, REG_DI_CNTR_SETPOINT_REACHED__TYPE_WSZ, 0)-1
#define REG_DI_CNTR_SETPOINT_REACHED__MBTABLE    MBRTU_DISC_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DI_CNTR_SETPOINT_REACHED__RETAIN     REG_RETAIN_NONE
//STRING
#define REG_DI_CNTR_SETPOINT_REACHED__STR        "DI%d Cntr: Setpoint is reached"

/** @def DI_MODE
 */
#define REG_DI_MODE__GID                         (uint16_t)13           //Unique ID
// located variable
#define REG_DI_MODE__ZONE                        PLC_LT_M              //ID of memory
#define REG_DI_MODE__TYPESZ                      PLC_LSZ_B             //ID of data type
#define REG_DI_MODE__GROUP                       REG_DI__GROUP         //ID of group
#define REG_DI_MODE__A00                         REG_AXX_ADDR
#define REG_DI_MODE__A01                         (int32_t)4            //ID of register
#define REG_DI_MODE__A02                         REG_AXX_NONE
#define REG_DI_MODE__TYPE                        TYPE_BYTE             //Data type
#define REG_DI_MODE__TYPE_SZ                     TYPE_BYTE_SZ          //Size of data type in bytes
#define REG_DI_MODE__TYPE_WSZ                    TYPE_BYTE_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DI_MODE__SZ                          (uint16_t)PLC_DI_SZ   //Number of registers
#define REG_DI_MODE__POS                         (uint16_t)REG_CALC_POS(REG_DI_CNTR_SETPOINT_REACHED__POS, REG_DI_CNTR_SETPOINT_REACHED__SZ)
#define REG_DI_MODE__SADDR                       (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DI_MODE__DPOS                        (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_SETPOINT__DPOS, REG_DI_CNTR_SETPOINT__SZ, REG_DI_CNTR_SETPOINT__TYPE_WSZ, 0)
#define REG_DI_MODE__DPOS_END                    (uint16_t)REG_CALC_MBPOS(REG_DI_MODE__DPOS, REG_DI_MODE__SZ, REG_DI_MODE__TYPE_WSZ, 0)-1
#define REG_DI_MODE__DTABLE                      REG_DATA_NUMB_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DI_MODE__MBPOS                       (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_SETPOINT__MBPOS, REG_DI_CNTR_SETPOINT__SZ, REG_DI_CNTR_SETPOINT__TYPE_WSZ, REG_RESERVE)
#define REG_DI_MODE__MBPOS_END                   (uint16_t)REG_CALC_MBPOS(REG_DI_MODE__MBPOS, REG_DI_MODE__SZ, REG_DI_MODE__TYPE_WSZ, 0)-1
#define REG_DI_MODE__MBTABLE                     MBRTU_HOLD_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DI_MODE__RETAIN                      REG_RETAIN_ALL
//STRING
#define REG_DI_MODE__STR                         "DI%d: Mode"

/** @def DI_RESET
 */
#define REG_DI_RESET__GID                        (uint16_t)14          //Unique ID
// located variable
#define REG_DI_RESET__ZONE                       PLC_LT_M              //ID of memory
#define REG_DI_RESET__TYPESZ                     PLC_LSZ_X             //ID of data type
#define REG_DI_RESET__GROUP                      REG_DI__GROUP         //ID of group
#define REG_DI_RESET__A00                        REG_AXX_ADDR
#define REG_DI_RESET__A01                        (int32_t)5            //ID of register
#define REG_DI_RESET__A02                        REG_AXX_NONE
#define REG_DI_RESET__TYPE                       TYPE_BOOL             //Data type
#define REG_DI_RESET__TYPE_SZ                    TYPE_BOOL_SZ          //Size of data type in bytes
#define REG_DI_RESET__TYPE_WSZ                   TYPE_BOOL_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DI_RESET__SZ                         (uint16_t)PLC_DI_SZ   //Number of registers
#define REG_DI_RESET__POS                        (uint16_t)REG_CALC_POS(REG_DI_MODE__POS, REG_DI_MODE__SZ)
#define REG_DI_RESET__SADDR                      (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DI_RESET__DPOS                       (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_SETPOINT_REACHED__DPOS, REG_DI_CNTR_SETPOINT_REACHED__SZ, REG_DI_CNTR_SETPOINT_REACHED__TYPE_WSZ, 0)
#define REG_DI_RESET__DPOS_END                   (uint16_t)REG_CALC_MBPOS(REG_DI_RESET__DPOS, REG_DI_RESET__SZ, REG_DI_RESET__TYPE_WSZ, 0)-1
#define REG_DI_RESET__DTABLE                     REG_DATA_BOOL_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DI_RESET__MBPOS                      (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_SETPOINT_ALLOW__MBPOS, REG_DI_CNTR_SETPOINT_ALLOW__SZ, REG_DI_CNTR_SETPOINT_ALLOW__TYPE_WSZ, REG_RESERVE)
#define REG_DI_RESET__MBPOS_END                  (uint16_t)REG_CALC_MBPOS(REG_DI_RESET__MBPOS, REG_DI_RESET__SZ, REG_DI_RESET__TYPE_WSZ, 0)-1
#define REG_DI_RESET__MBTABLE                    MBRTU_COIL_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DI_RESET__RETAIN                     REG_RETAIN_ALL
//STRING
#define REG_DI_RESET__STR                        "DI%d: Reset all counters"

/** @def DI_STATUS
 */
#define REG_DI_STATUS__GID                       (uint16_t)15          //unique ID
// located variable
#define REG_DI_STATUS__ZONE                      PLC_LT_M              //memory zone ID
#define REG_DI_STATUS__TYPESZ                    PLC_LSZ_B             //data type ID
#define REG_DI_STATUS__GROUP                     REG_DI__GROUP
#define REG_DI_STATUS__A00                       REG_AXX_ADDR          //arg0: ID of subgroup
#define REG_DI_STATUS__A01                       (int32_t)6            //arg1: ID of subgroup
#define REG_DI_STATUS__A02                       REG_AXX_NONE          //arg2: ID of subgroup
#define REG_DI_STATUS__TYPE                      TYPE_BYTE             //data type
#define REG_DI_STATUS__TYPE_SZ                   TYPE_BYTE_SZ          //size of data type (bytes)
#define REG_DI_STATUS__TYPE_WSZ                  TYPE_BYTE_WSZ         //size of data type (words)
// position (offset) in REGS
#define REG_DI_STATUS__SZ                        PLC_DI_SZ   		   //number of registers
#define REG_DI_STATUS__POS                       (uint16_t)REG_CALC_POS(REG_DI_RESET__POS, REG_DI_RESET__SZ)
#define REG_DI_STATUS__SADDR                     (uint16_t)0           //start register address
// position (offset) in Data Table
#define REG_DI_STATUS__DPOS                      (uint16_t)REG_CALC_MBPOS(REG_DI_MODE__DPOS, REG_DI_MODE__SZ, REG_DI_MODE__TYPE_WSZ, 0)
#define REG_DI_STATUS__DPOS_END                  (uint16_t)REG_CALC_MBPOS(REG_DI_STATUS__DPOS, REG_DI_STATUS__SZ, REG_DI_STATUS__TYPE_WSZ, 0)-1
#define REG_DI_STATUS__DTABLE                    REG_DATA_NUMB_TABLE_ID //data table ID
// position (offset) in ModBus Table
#define REG_DI_STATUS__MBPOS                     (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_VAL__MBPOS, REG_DI_CNTR_VAL__SZ, REG_DI_CNTR_VAL__TYPE_WSZ, REG_RESERVE)
#define REG_DI_STATUS__MBPOS_END                 (uint16_t)REG_CALC_MBPOS(REG_DI_STATUS__MBPOS, REG_DI_STATUS__SZ, REG_DI_STATUS__TYPE_WSZ, 0)-1
#define REG_DI_STATUS__MBTABLE                   MBRTU_INPT_TABLE_ID   //modbus table ID
// EEPROM
#define REG_DI_STATUS__RETAIN                    REG_RETAIN_NONE
// STRING
#define REG_DI_STATUS__STR                       "DI%d: Status"

/** @def DI_FILTER_DELAY
 */
#define REG_DI_FILTER_DELAY__GID                 (uint16_t)16          //unique ID
// located variable
#define REG_DI_FILTER_DELAY__ZONE                PLC_LT_M              //memory zone ID
#define REG_DI_FILTER_DELAY__TYPESZ              PLC_LSZ_D             //data type ID
#define REG_DI_FILTER_DELAY__GROUP               REG_DI__GROUP
#define REG_DI_FILTER_DELAY__A00                 REG_AXX_ADDR          //arg0: ID of subgroup
#define REG_DI_FILTER_DELAY__A01                 (int32_t)7            //arg1: ID of subgroup
#define REG_DI_FILTER_DELAY__A02                 REG_AXX_NONE          //arg2: ID of subgroup
#define REG_DI_FILTER_DELAY__TYPE                TYPE_DWORD            //data type
#define REG_DI_FILTER_DELAY__TYPE_SZ             TYPE_DWORD_SZ         //size of data type (bytes)
#define REG_DI_FILTER_DELAY__TYPE_WSZ            TYPE_DWORD_WSZ        //size of data type (words)
// position (offset) in REGS
#define REG_DI_FILTER_DELAY__SZ                  PLC_DI_SZ   		   //number of registers
#define REG_DI_FILTER_DELAY__POS                 (uint16_t)REG_CALC_POS(REG_DI_STATUS__POS, REG_DI_STATUS__SZ)
#define REG_DI_FILTER_DELAY__SADDR               (uint16_t)0           //start register address
// position (offset) in Data Table
#define REG_DI_FILTER_DELAY__DPOS                (uint16_t)REG_CALC_MBPOS(REG_DI_STATUS__DPOS, REG_DI_STATUS__SZ, REG_DI_STATUS__TYPE_WSZ, 0)
#define REG_DI_FILTER_DELAY__DPOS_END            (uint16_t)REG_CALC_MBPOS(REG_DI_FILTER_DELAY__DPOS, REG_DI_FILTER_DELAY__SZ, REG_DI_FILTER_DELAY__TYPE_WSZ, 0)-1
#define REG_DI_FILTER_DELAY__DTABLE              REG_DATA_NUMB_TABLE_ID //data table ID
// position (offset) in ModBus Table
#define REG_DI_FILTER_DELAY__MBPOS               (uint16_t)REG_CALC_MBPOS(REG_DI_MODE__MBPOS, REG_DI_MODE__SZ, REG_DI_MODE__TYPE_WSZ, REG_RESERVE)
#define REG_DI_FILTER_DELAY__MBPOS_END           (uint16_t)REG_CALC_MBPOS(REG_DI_FILTER_DELAY__MBPOS, REG_DI_FILTER_DELAY__SZ, REG_DI_FILTER_DELAY__TYPE_WSZ, 0)-1
#define REG_DI_FILTER_DELAY__MBTABLE             MBRTU_HOLD_TABLE_ID   //modbus table ID
// EEPROM
#define REG_DI_FILTER_DELAY__RETAIN              REG_RETAIN_ALL
// STRING
#define REG_DI_FILTER_DELAY__STR                 "DI%d: Filter delay"


//DO

#include "do.h"

#define REG_DO__GROUP                            (uint16_t)2

/** @def DO_NORM_VAL
 */
#define REG_DO_NORM_VAL__GID                     (uint16_t)20          //Unique ID
// located variable
#define REG_DO_NORM_VAL__ZONE                    PLC_LT_Q              //ID of memory
#define REG_DO_NORM_VAL__TYPESZ                  PLC_LSZ_X             //ID of data type
#define REG_DO_NORM_VAL__GROUP                   REG_DO__GROUP         //ID of group
#define REG_DO_NORM_VAL__A00                     REG_AXX_ADDR          //arg0: channel number (auto)
#define REG_DO_NORM_VAL__A01                     (int32_t)1            //arg1: ID of subgroup by mode
#define REG_DO_NORM_VAL__A02                     (int32_t)1            //arg2: ID of register
#define REG_DO_NORM_VAL__TYPE                    TYPE_BOOL             //Data type
#define REG_DO_NORM_VAL__TYPE_SZ                 TYPE_BOOL_SZ          //Size of data type in bytes
#define REG_DO_NORM_VAL__TYPE_WSZ                TYPE_BOOL_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DO_NORM_VAL__SZ                      PLC_DO_SZ
#define REG_DO_NORM_VAL__POS                     (uint16_t)REG_CALC_POS(REG_DI_FILTER_DELAY__POS, REG_DI_FILTER_DELAY__SZ)
#define REG_DO_NORM_VAL__SADDR                   (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DO_NORM_VAL__DPOS                    (uint16_t)REG_CALC_MBPOS(REG_DI_RESET__DPOS, REG_DI_RESET__SZ, REG_DI_RESET__TYPE_WSZ, 0)
#define REG_DO_NORM_VAL__DPOS_END                (uint16_t)REG_CALC_MBPOS(REG_DO_NORM_VAL__DPOS, REG_DO_NORM_VAL__SZ, REG_DO_NORM_VAL__TYPE_WSZ, 0)-1
#define REG_DO_NORM_VAL__DTABLE                  REG_DATA_BOOL_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DO_NORM_VAL__MBPOS                   (uint16_t)REG_CALC_MBPOS(REG_DI_RESET__MBPOS, REG_DI_RESET__SZ, REG_DI_RESET__TYPE_WSZ, REG_RESERVE)
#define REG_DO_NORM_VAL__MBPOS_END               (uint16_t)REG_CALC_MBPOS(REG_DO_NORM_VAL__MBPOS, REG_DO_NORM_VAL__SZ, REG_DO_NORM_VAL__TYPE_WSZ, 0)-1
#define REG_DO_NORM_VAL__MBTABLE                 MBRTU_COIL_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DO_NORM_VAL__RETAIN                  REG_RETAIN_NONE
//STRING
#define REG_DO_NORM_VAL__STR                     "DO%d Norm: Value"

/** @def DO_FAST_VAL
 */
#define REG_DO_FAST_VAL__GID                     (uint16_t)21          //Unique ID
// located variable
#define REG_DO_FAST_VAL__ZONE                    PLC_LT_Q              //ID of memory
#define REG_DO_FAST_VAL__TYPESZ                  PLC_LSZ_X             //ID of data type
#define REG_DO_FAST_VAL__GROUP                   REG_DO__GROUP         //ID of group
#define REG_DO_FAST_VAL__A00                     REG_AXX_ADDR          //arg0: channel number (auto)
#define REG_DO_FAST_VAL__A01                     (int32_t)2            //arg1: ID of subgroup by mode
#define REG_DO_FAST_VAL__A02                     (int32_t)1            //arg2: ID of register
#define REG_DO_FAST_VAL__TYPE                    TYPE_BOOL             //Data type
#define REG_DO_FAST_VAL__TYPE_SZ                 TYPE_BOOL_SZ          //Size of data type in bytes
#define REG_DO_FAST_VAL__TYPE_WSZ                TYPE_BOOL_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DO_FAST_VAL__SZ                      (uint16_t)PLC_DO_SZ   //Number of registers
#define REG_DO_FAST_VAL__POS                     (uint16_t)REG_CALC_POS(REG_DO_NORM_VAL__POS, REG_DO_NORM_VAL__SZ)
#define REG_DO_FAST_VAL__SADDR                   (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DO_FAST_VAL__DPOS                    (uint16_t)REG_CALC_MBPOS(REG_DO_NORM_VAL__DPOS, REG_DO_NORM_VAL__SZ, REG_DO_NORM_VAL__TYPE_WSZ, 0)
#define REG_DO_FAST_VAL__DPOS_END                (uint16_t)REG_CALC_MBPOS(REG_DO_FAST_VAL__DPOS, REG_DO_FAST_VAL__SZ, REG_DO_FAST_VAL__TYPE_WSZ, 0)-1
#define REG_DO_FAST_VAL__DTABLE                  REG_DATA_BOOL_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DO_FAST_VAL__MBPOS                   (uint16_t)REG_CALC_MBPOS(REG_DO_NORM_VAL__MBPOS, REG_DO_NORM_VAL__SZ, REG_DO_NORM_VAL__TYPE_WSZ, REG_RESERVE)
#define REG_DO_FAST_VAL__MBPOS_END               (uint16_t)REG_CALC_MBPOS(REG_DO_FAST_VAL__MBPOS, REG_DO_FAST_VAL__SZ, REG_DO_FAST_VAL__TYPE_WSZ, 0)-1
#define REG_DO_FAST_VAL__MBTABLE                 MBRTU_COIL_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DO_FAST_VAL__RETAIN                  REG_RETAIN_NONE
//STRING
#define REG_DO_FAST_VAL__STR                     "DO%d Fast: Value"

/** @def DO_PWM_VAL (fill factor)
 */
#define REG_DO_PWM_VAL__GID                      (uint16_t)22          //Unique ID
// located variable
#define REG_DO_PWM_VAL__ZONE                     PLC_LT_Q              //ID of memory
#define REG_DO_PWM_VAL__TYPESZ                   PLC_LSZ_D             //ID of data type
#define REG_DO_PWM_VAL__GROUP                    REG_DO__GROUP         //ID of group
#define REG_DO_PWM_VAL__A00                      REG_AXX_ADDR          //arg0: channel number (auto)
#define REG_DO_PWM_VAL__A01                      (int32_t)3            //arg1: ID of subgroup by mode
#define REG_DO_PWM_VAL__A02                      (int32_t)1            //arg2: ID of register
#define REG_DO_PWM_VAL__TYPE                     TYPE_REAL             //Data type
#define REG_DO_PWM_VAL__TYPE_SZ                  TYPE_REAL_SZ          //Size of data type in bytes
#define REG_DO_PWM_VAL__TYPE_WSZ                 TYPE_REAL_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DO_PWM_VAL__SZ                       (uint16_t)PLC_DO_SZ   //Number of registers
#define REG_DO_PWM_VAL__POS                      (uint16_t)REG_CALC_POS(REG_DO_FAST_VAL__POS, REG_DO_FAST_VAL__SZ)
#define REG_DO_PWM_VAL__SADDR                    (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DO_PWM_VAL__DPOS                     (uint16_t)REG_CALC_MBPOS(REG_DI_FILTER_DELAY__DPOS, REG_DI_FILTER_DELAY__SZ, REG_DI_FILTER_DELAY__TYPE_WSZ, 0)
#define REG_DO_PWM_VAL__DPOS_END                 (uint16_t)REG_CALC_MBPOS(REG_DO_PWM_VAL__DPOS, REG_DO_PWM_VAL__SZ, REG_DO_PWM_VAL__TYPE_WSZ, 0)-1
#define REG_DO_PWM_VAL__DTABLE                   REG_DATA_NUMB_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DO_PWM_VAL__MBPOS                    (uint16_t)REG_CALC_MBPOS(REG_DI_FILTER_DELAY__MBPOS, REG_DI_FILTER_DELAY__SZ, REG_DI_FILTER_DELAY__TYPE_WSZ, REG_RESERVE)
#define REG_DO_PWM_VAL__MBPOS_END                (uint16_t)REG_CALC_MBPOS(REG_DO_PWM_VAL__MBPOS, REG_DO_PWM_VAL__SZ, REG_DO_PWM_VAL__TYPE_WSZ, 0)-1
#define REG_DO_PWM_VAL__MBTABLE                  MBRTU_HOLD_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DO_PWM_VAL__RETAIN                   REG_RETAIN_NONE
//STRING
#define REG_DO_PWM_VAL__STR                     "DO%d PWM: Fill Factor, %"

/** @def DO_PWM_ALLOW
 */
#define REG_DO_PWM_ALLOW__GID                    (uint16_t)23          //Unique ID
// located variable
#define REG_DO_PWM_ALLOW__ZONE                   PLC_LT_M              //ID of memory
#define REG_DO_PWM_ALLOW__TYPESZ                 PLC_LSZ_X             //ID of data type
#define REG_DO_PWM_ALLOW__GROUP                  REG_DO__GROUP         //ID of group
#define REG_DO_PWM_ALLOW__A00                    REG_AXX_ADDR          //arg0: channel number (auto)
#define REG_DO_PWM_ALLOW__A01                    (int32_t)3            //arg1: ID of subgroup by mode
#define REG_DO_PWM_ALLOW__A02                    (int32_t)2            //arg2: ID of register
#define REG_DO_PWM_ALLOW__TYPE                   TYPE_BOOL             //Data type
#define REG_DO_PWM_ALLOW__TYPE_SZ                TYPE_BOOL_SZ          //Size of data type in bytes
#define REG_DO_PWM_ALLOW__TYPE_WSZ               TYPE_BOOL_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DO_PWM_ALLOW__SZ                     (uint16_t)PLC_DO_SZ   //Number of registers
#define REG_DO_PWM_ALLOW__POS                    (uint16_t)REG_CALC_POS(REG_DO_PWM_VAL__POS, REG_DO_PWM_VAL__SZ)
#define REG_DO_PWM_ALLOW__SADDR                  (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DO_PWM_ALLOW__DPOS                   (uint16_t)REG_CALC_MBPOS(REG_DO_FAST_VAL__DPOS, REG_DO_FAST_VAL__SZ, REG_DO_FAST_VAL__TYPE_WSZ, 0)
#define REG_DO_PWM_ALLOW__DPOS_END               (uint16_t)REG_CALC_MBPOS(REG_DO_PWM_ALLOW__DPOS, REG_DO_PWM_ALLOW__SZ, REG_DO_PWM_ALLOW__TYPE_WSZ, 0)-1
#define REG_DO_PWM_ALLOW__DTABLE                 REG_DATA_BOOL_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DO_PWM_ALLOW__MBPOS                  (uint16_t)REG_CALC_MBPOS(REG_DO_FAST_VAL__MBPOS, REG_DO_FAST_VAL__SZ, REG_DO_FAST_VAL__TYPE_WSZ, REG_RESERVE)
#define REG_DO_PWM_ALLOW__MBPOS_END              (uint16_t)REG_CALC_MBPOS(REG_DO_PWM_ALLOW__MBPOS, REG_DO_PWM_ALLOW__SZ, REG_DO_PWM_ALLOW__TYPE_WSZ, 0)-1
#define REG_DO_PWM_ALLOW__MBTABLE                MBRTU_COIL_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DO_PWM_ALLOW__RETAIN                 REG_RETAIN_ALL
//STRING
#define REG_DO_PWM_ALLOW__STR                    "DO%d PWM: Allow to work"

/** @def DO_PWM_PERIOD (ms)
 */
#define REG_DO_PWM_PERIOD__GID                   (uint16_t)24          //Unique ID
// located variable
#define REG_DO_PWM_PERIOD__ZONE                  PLC_LT_M              //ID of memory
#define REG_DO_PWM_PERIOD__TYPESZ                PLC_LSZ_D             //ID of data type
#define REG_DO_PWM_PERIOD__GROUP                 REG_DO__GROUP         //ID of group
#define REG_DO_PWM_PERIOD__A00                   REG_AXX_ADDR          //arg0: channel number (auto)
#define REG_DO_PWM_PERIOD__A01                   (int32_t)3            //arg1: ID of subgroup by mode
#define REG_DO_PWM_PERIOD__A02                   (int32_t)3            //arg2: ID of register
#define REG_DO_PWM_PERIOD__TYPE                  TYPE_REAL             //Data type
#define REG_DO_PWM_PERIOD__TYPE_SZ               TYPE_REAL_SZ          //Size of data type in bytes
#define REG_DO_PWM_PERIOD__TYPE_WSZ              TYPE_REAL_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DO_PWM_PERIOD__SZ                    (uint16_t)PLC_DO_SZ   //Number of registers
#define REG_DO_PWM_PERIOD__POS                   (uint16_t)REG_CALC_POS(REG_DO_PWM_ALLOW__POS, REG_DO_PWM_ALLOW__SZ)
#define REG_DO_PWM_PERIOD__SADDR                 (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DO_PWM_PERIOD__DPOS                  (uint16_t)REG_CALC_MBPOS(REG_DO_PWM_VAL__DPOS, REG_DO_PWM_VAL__SZ, REG_DO_PWM_VAL__TYPE_WSZ, 0)
#define REG_DO_PWM_PERIOD__DPOS_END              (uint16_t)REG_CALC_MBPOS(REG_DO_PWM_PERIOD__DPOS, REG_DO_PWM_PERIOD__SZ, REG_DO_PWM_PERIOD__TYPE_WSZ, 0)-1
#define REG_DO_PWM_PERIOD__DTABLE                REG_DATA_NUMB_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DO_PWM_PERIOD__MBPOS                 (uint16_t)REG_CALC_MBPOS(REG_DO_PWM_VAL__MBPOS, REG_DO_PWM_VAL__SZ, REG_DO_PWM_VAL__TYPE_WSZ, REG_RESERVE)
#define REG_DO_PWM_PERIOD__MBPOS_END             (uint16_t)REG_CALC_MBPOS(REG_DO_PWM_PERIOD__MBPOS, REG_DO_PWM_PERIOD__SZ, REG_DO_PWM_PERIOD__TYPE_WSZ, 0)-1
#define REG_DO_PWM_PERIOD__MBTABLE               MBRTU_HOLD_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DO_PWM_PERIOD__RETAIN                REG_RETAIN_ALL
//STRING
#define REG_DO_PWM_PERIOD__STR                   "DO%d PWM: Period, ms"

/** @def DO_MODE
 */
#define REG_DO_MODE__GID                         (uint16_t)25          //Unique ID
// located variable
#define REG_DO_MODE__ZONE                        PLC_LT_M              //ID of memory
#define REG_DO_MODE__TYPESZ                      PLC_LSZ_B             //ID of data type
#define REG_DO_MODE__GROUP                       REG_DO__GROUP         //ID of group
#define REG_DO_MODE__A00                         REG_AXX_ADDR          //arg0: channel number (auto)
#define REG_DO_MODE__A01                         (int32_t)4            //arg1: ID of subgroup by mode
#define REG_DO_MODE__A02                         REG_AXX_NONE          //arg2: none
#define REG_DO_MODE__TYPE                        TYPE_BYTE             //Data type
#define REG_DO_MODE__TYPE_SZ                     TYPE_BYTE_SZ          //Size of data type in bytes
#define REG_DO_MODE__TYPE_WSZ                    TYPE_BYTE_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DO_MODE__SZ                          (uint16_t)PLC_DO_SZ   //Number of registers
#define REG_DO_MODE__POS                         (uint16_t)REG_CALC_POS(REG_DO_PWM_PERIOD__POS, REG_DO_PWM_PERIOD__SZ)
#define REG_DO_MODE__SADDR                       (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DO_MODE__DPOS                        (uint16_t)REG_CALC_MBPOS(REG_DO_PWM_PERIOD__DPOS, REG_DO_PWM_PERIOD__SZ, REG_DO_PWM_PERIOD__TYPE_WSZ, 0)
#define REG_DO_MODE__DPOS_END                    (uint16_t)REG_CALC_MBPOS(REG_DO_MODE__DPOS, REG_DO_MODE__SZ, REG_DO_MODE__TYPE_WSZ, 0)-1
#define REG_DO_MODE__DTABLE                      REG_DATA_NUMB_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DO_MODE__MBPOS                       (uint16_t)REG_CALC_MBPOS(REG_DO_PWM_PERIOD__MBPOS, REG_DO_PWM_PERIOD__SZ, REG_DO_PWM_PERIOD__TYPE_WSZ, REG_RESERVE)
#define REG_DO_MODE__MBPOS_END                   (uint16_t)REG_CALC_MBPOS(REG_DO_MODE__MBPOS, REG_DO_MODE__SZ, REG_DO_MODE__TYPE_WSZ, 0)-1
#define REG_DO_MODE__MBTABLE                     MBRTU_HOLD_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DO_MODE__RETAIN                      REG_RETAIN_ALL
//STRING
#define REG_DO_MODE__STR                         "DO%d: Mode"

/** @def DO_STATUS
 */
#define REG_DO_STATUS__GID                       (uint16_t)26          //unique ID
// located variable
#define REG_DO_STATUS__ZONE                      PLC_LT_M              //memory zone ID
#define REG_DO_STATUS__TYPESZ                    PLC_LSZ_B             //data type ID
#define REG_DO_STATUS__GROUP                     REG_DO__GROUP
#define REG_DO_STATUS__A00                       REG_AXX_ADDR          //arg0: ID of subgroup
#define REG_DO_STATUS__A01                       (int32_t)5            //arg1: ID of subgroup
#define REG_DO_STATUS__A02                       REG_AXX_NONE          //arg2: ID of subgroup
#define REG_DO_STATUS__TYPE                      TYPE_BYTE             //data type
#define REG_DO_STATUS__TYPE_SZ                   TYPE_BYTE_SZ          //size of data type (bytes)
#define REG_DO_STATUS__TYPE_WSZ                  TYPE_BYTE_WSZ         //size of data type (words)
// position (offset) in REGS
#define REG_DO_STATUS__SZ                        PLC_DO_SZ   		   //number of registers
#define REG_DO_STATUS__POS                       (uint16_t)REG_CALC_POS(REG_DO_MODE__POS, REG_DO_MODE__SZ)
#define REG_DO_STATUS__SADDR                     (uint16_t)0           //start register address
// position (offset) in Data Table
#define REG_DO_STATUS__DPOS                      (uint16_t)REG_CALC_MBPOS(REG_DO_MODE__DPOS, REG_DO_MODE__SZ, REG_DO_MODE__TYPE_WSZ, 0)
#define REG_DO_STATUS__DPOS_END                  (uint16_t)REG_CALC_MBPOS(REG_DO_STATUS__DPOS, REG_DO_STATUS__SZ, REG_DO_STATUS__TYPE_WSZ, 0)-1
#define REG_DO_STATUS__DTABLE                    REG_DATA_NUMB_TABLE_ID //data table ID
// position (offset) in ModBus Table
#define REG_DO_STATUS__MBPOS                     (uint16_t)REG_CALC_MBPOS(REG_DI_STATUS__MBPOS, REG_DI_STATUS__SZ, REG_DI_STATUS__TYPE_WSZ, REG_RESERVE)
#define REG_DO_STATUS__MBPOS_END                 (uint16_t)REG_CALC_MBPOS(REG_DO_STATUS__MBPOS, REG_DO_STATUS__SZ, REG_DO_STATUS__TYPE_WSZ, 0)-1
#define REG_DO_STATUS__MBTABLE                   MBRTU_INPT_TABLE_ID   //modbus table ID
// EEPROM
#define REG_DO_STATUS__RETAIN                    REG_RETAIN_NONE
// STRING
#define REG_DO_STATUS__STR                       "DO%d: Status"


//AI

#include "ai.h"

//group ID
#define REG_AI__GROUP                            (uint16_t)3

/** @def AI_VAL
 */
#define REG_AI_VAL__GID                          (uint16_t)30          //unique ID
// located variable
#define REG_AI_VAL__ZONE                         PLC_LT_I              //memory zone ID
#define REG_AI_VAL__TYPESZ                       PLC_LSZ_D             //data type ID
#define REG_AI_VAL__GROUP                        REG_AI__GROUP
#define REG_AI_VAL__A00                          REG_AXX_ADDR          //arg0: ID of subgroup
#define REG_AI_VAL__A01                          (int32_t)1            //arg1: ID of subgroup
#define REG_AI_VAL__A02                          REG_AXX_NONE          //arg2: ID of subgroup
#define REG_AI_VAL__TYPE                         TYPE_REAL             //data type
#define REG_AI_VAL__TYPE_SZ                      TYPE_REAL_SZ          //size of data type (bytes)
#define REG_AI_VAL__TYPE_WSZ                     TYPE_REAL_WSZ         //size of data type (words)
// position (offset) in REGS
#define REG_AI_VAL__SZ                           PLC_AI_SZ   		   //number of registers
#define REG_AI_VAL__POS                          (uint16_t)REG_CALC_POS(REG_DO_STATUS__POS, REG_DO_STATUS__SZ)
#define REG_AI_VAL__SADDR                        (uint16_t)0           //start register address
// position (offset) in Data Table
#define REG_AI_VAL__DPOS                         (uint16_t)REG_CALC_MBPOS(REG_DO_STATUS__DPOS, REG_DO_STATUS__SZ, REG_DO_STATUS__TYPE_WSZ, 0)
#define REG_AI_VAL__DPOS_END                     (uint16_t)REG_CALC_MBPOS(REG_AI_VAL__DPOS, REG_AI_VAL__SZ, REG_AI_VAL__TYPE_WSZ, 0)-1
#define REG_AI_VAL__DTABLE                       REG_DATA_NUMB_TABLE_ID //data table ID
// position (offset) in ModBus Table
#define REG_AI_VAL__MBPOS                        (uint16_t)REG_CALC_MBPOS(REG_DO_STATUS__MBPOS, REG_DO_STATUS__SZ, REG_DO_STATUS__TYPE_WSZ, REG_RESERVE)
#define REG_AI_VAL__MBPOS_END                    (uint16_t)REG_CALC_MBPOS(REG_AI_VAL__MBPOS, REG_AI_VAL__SZ, REG_AI_VAL__TYPE_WSZ, 0)-1
#define REG_AI_VAL__MBTABLE                      MBRTU_INPT_TABLE_ID   //modbus table ID
// EEPROM
#define REG_AI_VAL__RETAIN                       REG_RETAIN_NONE
// STRING
#define REG_AI_VAL__STR                       	 "AI%d: Val"

/** @def AI_MODE
 */
#define REG_AI_MODE__GID                         (uint16_t)31          //unique ID
// located variable
#define REG_AI_MODE__ZONE                        PLC_LT_M              //memory zone ID
#define REG_AI_MODE__TYPESZ                      PLC_LSZ_B             //data type ID
#define REG_AI_MODE__GROUP                       REG_AI__GROUP
#define REG_AI_MODE__A00                         REG_AXX_ADDR          //arg0: ID of subgroup
#define REG_AI_MODE__A01                         (int32_t)2            //arg1: ID of subgroup
#define REG_AI_MODE__A02                         REG_AXX_NONE          //arg2: ID of subgroup
#define REG_AI_MODE__TYPE                        TYPE_BYTE             //data type
#define REG_AI_MODE__TYPE_SZ                     TYPE_BYTE_SZ          //size of data type (bytes)
#define REG_AI_MODE__TYPE_WSZ                    TYPE_BYTE_WSZ         //size of data type (bytes)
// position (offset) in REGS
#define REG_AI_MODE__SZ                          PLC_AI_SZ   		   //number of registers
#define REG_AI_MODE__POS                         (uint16_t)REG_CALC_POS(REG_AI_VAL__POS, REG_AI_VAL__SZ)
#define REG_AI_MODE__SADDR                       (uint16_t)0           //start register address
// position (offset) in Data Table
#define REG_AI_MODE__DPOS                        (uint16_t)REG_CALC_MBPOS(REG_AI_VAL__DPOS, REG_AI_VAL__SZ, REG_AI_VAL__TYPE_WSZ, 0)
#define REG_AI_MODE__DPOS_END                    (uint16_t)REG_CALC_MBPOS(REG_AI_MODE__DPOS, REG_AI_MODE__SZ, REG_AI_MODE__TYPE_WSZ, 0)-1
#define REG_AI_MODE__DTABLE                      REG_DATA_NUMB_TABLE_ID  //data table ID
// position (offset) in ModBus Table
#define REG_AI_MODE__MBPOS                       (uint16_t)REG_CALC_MBPOS(REG_DO_MODE__MBPOS, REG_DO_MODE__SZ, REG_DO_MODE__TYPE_WSZ, REG_RESERVE)
#define REG_AI_MODE__MBPOS_END                   (uint16_t)REG_CALC_MBPOS(REG_AI_MODE__MBPOS, REG_AI_MODE__SZ, REG_AI_MODE__TYPE_WSZ, 0)-1
#define REG_AI_MODE__MBTABLE                     MBRTU_HOLD_TABLE_ID   //modbus table ID
// EEPROM
#define REG_AI_MODE__RETAIN                      REG_RETAIN_ALL
// STRING
#define REG_AI_MODE__STR                       	 "AI%d: Mode"

/** @def AI_STATUS
 */
#define REG_AI_STATUS__GID                       (uint16_t)32          //unique ID
// located variable
#define REG_AI_STATUS__ZONE                      PLC_LT_M              //memory zone ID
#define REG_AI_STATUS__TYPESZ                    PLC_LSZ_B             //data type ID
#define REG_AI_STATUS__GROUP                     REG_AI__GROUP
#define REG_AI_STATUS__A00                       REG_AXX_ADDR          //arg0: ID of subgroup
#define REG_AI_STATUS__A01                       (int32_t)3            //arg1: ID of subgroup
#define REG_AI_STATUS__A02                       REG_AXX_NONE          //arg2: ID of subgroup
#define REG_AI_STATUS__TYPE                      TYPE_BYTE             //data type
#define REG_AI_STATUS__TYPE_SZ                   TYPE_BYTE_SZ          //size of data type (bytes)
#define REG_AI_STATUS__TYPE_WSZ                  TYPE_BYTE_WSZ         //size of data type (words)
// position (offset) in REGS
#define REG_AI_STATUS__SZ                        PLC_AI_SZ   		   //number of registers
#define REG_AI_STATUS__POS                       (uint16_t)REG_CALC_POS(REG_AI_MODE__POS, REG_AI_MODE__SZ)
#define REG_AI_STATUS__SADDR                     (uint16_t)0           //start register address
// position (offset) in Data Table
#define REG_AI_STATUS__DPOS                      (uint16_t)REG_CALC_MBPOS(REG_AI_MODE__DPOS, REG_AI_MODE__SZ, REG_AI_MODE__TYPE_WSZ, 0)
#define REG_AI_STATUS__DPOS_END                  (uint16_t)REG_CALC_MBPOS(REG_AI_STATUS__DPOS, REG_AI_STATUS__SZ, REG_AI_STATUS__TYPE_WSZ, 0)-1
#define REG_AI_STATUS__DTABLE                    REG_DATA_NUMB_TABLE_ID //data table ID
// position (offset) in ModBus Table
#define REG_AI_STATUS__MBPOS                     (uint16_t)REG_CALC_MBPOS(REG_AI_VAL__MBPOS, REG_AI_VAL__SZ, REG_AI_VAL__TYPE_WSZ, REG_RESERVE)
#define REG_AI_STATUS__MBPOS_END                 (uint16_t)REG_CALC_MBPOS(REG_AI_STATUS__MBPOS, REG_AI_STATUS__SZ, REG_AI_STATUS__TYPE_WSZ, 0)-1
#define REG_AI_STATUS__MBTABLE                   MBRTU_INPT_TABLE_ID   //modbus table ID
// EEPROM
#define REG_AI_STATUS__RETAIN                    REG_RETAIN_NONE
// STRING
#define REG_AI_STATUS__STR                       "AI%d: Status"

/** @def AI_KA
 */
#define REG_AI_KA__GID                           (uint16_t)33          //unique ID
// located variable
#define REG_AI_KA__ZONE                          PLC_LT_M              //memory zone ID
#define REG_AI_KA__TYPESZ                        PLC_LSZ_D             //data type ID
#define REG_AI_KA__GROUP                         REG_AI__GROUP
#define REG_AI_KA__A00                           REG_AXX_ADDR          //arg0: ID of subgroup
#define REG_AI_KA__A01                           (int32_t)4            //arg1: ID of subgroup
#define REG_AI_KA__A02                           REG_AXX_NONE          //arg2: ID of subgroup
#define REG_AI_KA__TYPE                          TYPE_REAL             //data type
#define REG_AI_KA__TYPE_SZ                       TYPE_REAL_SZ          //size of data type (bytes)
#define REG_AI_KA__TYPE_WSZ                      TYPE_REAL_WSZ         //size of data type (words)
// position (offset) in REGS
#define REG_AI_KA__SZ                            PLC_AI_SZ   		   //number of registers
#define REG_AI_KA__POS                           (uint16_t)REG_CALC_POS(REG_AI_STATUS__POS, REG_AI_STATUS__SZ)
#define REG_AI_KA__SADDR                         (uint16_t)0           //start register address
// position (offset) in Data Table
#define REG_AI_KA__DPOS                          (uint16_t)REG_CALC_MBPOS(REG_AI_STATUS__DPOS, REG_AI_STATUS__SZ, REG_AI_STATUS__TYPE_WSZ, 0)
#define REG_AI_KA__DPOS_END                      (uint16_t)REG_CALC_MBPOS(REG_AI_KA__DPOS, REG_AI_KA__SZ, REG_AI_KA__TYPE_WSZ, 0)-1
#define REG_AI_KA__DTABLE                        REG_DATA_NUMB_TABLE_ID //data table ID
// position (offset) in ModBus Table
#define REG_AI_KA__MBPOS                         (uint16_t)REG_CALC_MBPOS(REG_AI_MODE__MBPOS, REG_AI_MODE__SZ, REG_AI_MODE__TYPE_WSZ, REG_RESERVE)
#define REG_AI_KA__MBPOS_END                     (uint16_t)REG_CALC_MBPOS(REG_AI_KA__MBPOS, REG_AI_KA__SZ, REG_AI_KA__TYPE_WSZ, 0)-1
#define REG_AI_KA__MBTABLE                       MBRTU_HOLD_TABLE_ID   //modbus table ID
// EEPROM
#define REG_AI_KA__RETAIN                        REG_RETAIN_ALL
// STRING
#define REG_AI_KA__STR                           "AI%d: Custom scale factor Ka"

/** @def AI_KB
 */
#define REG_AI_KB__GID                           (uint16_t)34          //unique ID
// located variable
#define REG_AI_KB__ZONE                          PLC_LT_M              //memory zone ID
#define REG_AI_KB__TYPESZ                        PLC_LSZ_D             //data type ID
#define REG_AI_KB__GROUP                         REG_AI__GROUP
#define REG_AI_KB__A00                           REG_AXX_ADDR          //arg0: ID of subgroup
#define REG_AI_KB__A01                           (int32_t)5            //arg1: ID of subgroup
#define REG_AI_KB__A02                           REG_AXX_NONE          //arg2: ID of subgroup
#define REG_AI_KB__TYPE                          TYPE_REAL             //data type
#define REG_AI_KB__TYPE_SZ                       TYPE_REAL_SZ          //size of data type (bytes)
#define REG_AI_KB__TYPE_WSZ                      TYPE_REAL_WSZ         //size of data type (words)
// position (offset) in REGS
#define REG_AI_KB__SZ                            PLC_AI_SZ   		   //number of registers
#define REG_AI_KB__POS                           (uint16_t)REG_CALC_POS(REG_AI_KA__POS, REG_AI_KA__SZ)
#define REG_AI_KB__SADDR                         (uint16_t)0           //start register address
// position (offset) in Data Table
#define REG_AI_KB__DPOS                          (uint16_t)REG_CALC_MBPOS(REG_AI_KA__DPOS, REG_AI_KA__SZ, REG_AI_KA__TYPE_WSZ, 0)
#define REG_AI_KB__DPOS_END                      (uint16_t)REG_CALC_MBPOS(REG_AI_KB__DPOS, REG_AI_KB__SZ, REG_AI_KB__TYPE_WSZ, 0)-1
#define REG_AI_KB__DTABLE                        REG_DATA_NUMB_TABLE_ID //data table ID
// position (offset) in ModBus Table
#define REG_AI_KB__MBPOS                         (uint16_t)REG_CALC_MBPOS(REG_AI_KA__MBPOS, REG_AI_KA__SZ, REG_AI_KA__TYPE_WSZ, REG_RESERVE)
#define REG_AI_KB__MBPOS_END                     (uint16_t)REG_CALC_MBPOS(REG_AI_KB__MBPOS, REG_AI_KB__SZ, REG_AI_KB__TYPE_WSZ, 0)-1
#define REG_AI_KB__MBTABLE                       MBRTU_HOLD_TABLE_ID   //modbus table ID
// EEPROM
#define REG_AI_KB__RETAIN                        REG_RETAIN_ALL
// STRING
#define REG_AI_KB__STR                           "AI%d: Custom scale factor Kb"


//SYSTEM

//group ID
#define REG_SYS__GROUP                           (uint16_t)7
//quantity of registers
#define REG_SYS_STAT_SZ                          (uint16_t)7
#define REG_SYS_SET_SZ                           (uint16_t)2
#define REG_SYS_CMD_SZ                           (uint16_t)3

/** @def SYSTEM STATUSES
 */
#define REG_SYS_STAT__GID                        (uint16_t)70               //unique ID
// located variable
#define REG_SYS_STAT__ZONE                       PLC_LT_M                   //memory zone ID
#define REG_SYS_STAT__TYPESZ                     PLC_LSZ_W                  //data type ID
#define REG_SYS_STAT__GROUP                      REG_SYS__GROUP
#define REG_SYS_STAT__A00                        (int32_t)1                 //arg0: ID of subgroup
#define REG_SYS_STAT__A01                        REG_AXX_ADDR               //arg1: ID of subgroup
#define REG_SYS_STAT__A02                        REG_AXX_NONE               //arg2: ID of subgroup
#define REG_SYS_STAT__TYPE                       TYPE_WORD                  //data type
#define REG_SYS_STAT__TYPE_SZ                    TYPE_WORD_SZ               //size of data type (bytes)
#define REG_SYS_STAT__TYPE_WSZ                   TYPE_WORD_WSZ              //size of data type (words)
// position (offset) in REGS
#define REG_SYS_STAT__SZ                         REG_SYS_STAT_SZ            //number of registers
#define REG_SYS_STAT__POS                        (uint16_t)REG_CALC_POS(REG_AI_KB__POS, REG_AI_KB__SZ)
#define REG_SYS_STAT__SADDR                      (uint16_t)0                //start register address
// position (offset) in Data Table
#define REG_SYS_STAT__DPOS                       (uint16_t)REG_CALC_MBPOS(REG_AI_KB__DPOS, REG_AI_KB__SZ, REG_AI_KB__TYPE_WSZ, 0)
#define REG_SYS_STAT__DPOS_END                   (uint16_t)REG_CALC_MBPOS(REG_SYS_STAT__DPOS, REG_SYS_STAT__SZ, REG_SYS_STAT__TYPE_WSZ, 0)-1
#define REG_SYS_STAT__DTABLE                     REG_DATA_NUMB_TABLE_ID     //data table ID
// position (offset) in ModBus Table
#define REG_SYS_STAT__MBPOS                      (uint16_t)REG_CALC_MBPOS(REG_AI_STATUS__MBPOS, REG_AI_STATUS__SZ, REG_AI_STATUS__TYPE_WSZ, REG_RESERVE)
#define REG_SYS_STAT__MBPOS_END                  (uint16_t)REG_CALC_MBPOS(REG_SYS_STAT__MBPOS, REG_SYS_STAT__SZ, REG_SYS_STAT__TYPE_WSZ, 0)-1
#define REG_SYS_STAT__MBTABLE                    MBRTU_INPT_TABLE_ID        //modbus table ID
// EEPROM
#define REG_SYS_STAT__RETAIN                     REG_RETAIN_NONE
//
// REGS Positions
#define REG_SYS_STAT__POS_HW_CODE                (REG_SYS_STAT__POS+0)      //Hardware code
#define REG_SYS_STAT__POS_HW_VAR                 (REG_SYS_STAT__POS+1)      //Hardware variant
#define REG_SYS_STAT__POS_RTE_VER                (REG_SYS_STAT__POS+2)      //RTE version (minor major)
#define REG_SYS_STAT__POS_RTE_YYYY               (REG_SYS_STAT__POS+3)      //RTE YYYY (year)
#define REG_SYS_STAT__POS_RTE_DDMM               (REG_SYS_STAT__POS+4)      //RTE DDMM (day month)
#define REG_SYS_STAT__POS_STAT1                  (REG_SYS_STAT__POS+5)      //System statuses (1), (packed)
#define REG_SYS_STAT__POS_STAT2                  (REG_SYS_STAT__POS+6)      //System statuses (2), (packed)
// ModBus Addresses
#define REG_SYS_STAT__MBPOS_HW_CODE              (REG_SYS_STAT__MBPOS+0)    //Hardware code
#define REG_SYS_STAT__MBPOS_HW_VAR               (REG_SYS_STAT__MBPOS+1)    //Hardware variant
#define REG_SYS_STAT__MBPOS_RTE_VER              (REG_SYS_STAT__MBPOS+2)    //RTE version (minor major)
#define REG_SYS_STAT__MBPOS_RTE_YYYY             (REG_SYS_STAT__MBPOS+3)    //RTE YYYY (year)
#define REG_SYS_STAT__MBPOS_RTE_DDMM             (REG_SYS_STAT__MBPOS+4)    //RTE DDMM (day month)
#define REG_SYS_STAT__MBPOS_STAT1                (REG_SYS_STAT__MBPOS+5)    //System statuses (1), (packed)
#define REG_SYS_STAT__MBPOS_STAT2                (REG_SYS_STAT__MBPOS+6)    //System statuses (2), (packed)
// STRING
#define REG_SYS_STAT__STR_HW_CODE                "PLC Hardware code"
#define REG_SYS_STAT__STR_HW_VAR                 "PLC Hardware variant"
#define REG_SYS_STAT__STR_RTE_VER                "RTE version"
#define REG_SYS_STAT__STR_RTE_YYYY               "RTE version (year)"
#define REG_SYS_STAT__STR_RTE_DDMM               "RTE version (day month)"
#define REG_SYS_STAT__STR_STAT1                  "System statuses (1), packed"
#define REG_SYS_STAT__STR_STAT2                  "System statuses (2), packed"

/** @def SYSTEM SETTINGS
 */
#define REG_SYS_SET__GID                         (uint16_t)71                //unique ID
// located variable
#define REG_SYS_SET__ZONE                        PLC_LT_M                    //memory ID
#define REG_SYS_SET__TYPESZ                      PLC_LSZ_W                   //data type ID
#define REG_SYS_SET__GROUP                       REG_SYS__GROUP
#define REG_SYS_SET__A00                         (int32_t)2                  //arg0: ID of subgroup
#define REG_SYS_SET__A01                         REG_AXX_ADDR                //arg1: ID of subgroup
#define REG_SYS_SET__A02                         REG_AXX_NONE                //arg2: ID of subgroup
#define REG_SYS_SET__TYPE                        TYPE_WORD                   //sata type
#define REG_SYS_SET__TYPE_SZ                     TYPE_WORD_SZ                //size of data type (bytes)
#define REG_SYS_SET__TYPE_WSZ                    TYPE_WORD_WSZ               //size of data type (words)
// position (offset) in REGS
#define REG_SYS_SET__SZ                          REG_SYS_SET_SZ              //number of registers
#define REG_SYS_SET__POS                         (uint16_t)REG_CALC_POS(REG_SYS_STAT__POS, REG_SYS_STAT__SZ)
#define REG_SYS_SET__SADDR                       (uint16_t)0                 //start register address
// position (offset) in Data Table
#define REG_SYS_SET__DPOS                        (uint16_t)REG_CALC_MBPOS(REG_SYS_STAT__DPOS, REG_SYS_STAT__SZ, REG_SYS_STAT__TYPE_WSZ, 0)
#define REG_SYS_SET__DPOS_END                    (uint16_t)REG_CALC_MBPOS(REG_SYS_SET__DPOS, REG_SYS_SET__SZ, REG_SYS_SET__TYPE_WSZ, 0)-1
#define REG_SYS_SET__DTABLE                      REG_DATA_NUMB_TABLE_ID      //data table ID
// position (offset) in ModBus Table
#define REG_SYS_SET__MBPOS                       (uint16_t)REG_CALC_MBPOS(REG_AI_KB__MBPOS, REG_AI_KB__SZ, REG_AI_KB__TYPE_WSZ, REG_RESERVE)
#define REG_SYS_SET__MBPOS_END                   (uint16_t)REG_CALC_MBPOS(REG_SYS_SET__MBPOS, REG_SYS_SET__SZ, REG_SYS_SET__TYPE_WSZ, 0)-1
#define REG_SYS_SET__MBTABLE                     MBRTU_HOLD_TABLE_ID         //modbus table ID
// EEPROM
#define REG_SYS_SET__RETAIN                      REG_RETAIN_ALL
//
// REGS Positions
#define REG_SYS_SET__POS_SFTY_TIM_TM             (REG_SYS_SET__POS+0)         //SFTY_TIM_TM
#define REG_SYS_SET__POS_WD_TIM_TM               (REG_SYS_SET__POS+1)         //WD_TIM_TM
// ModBus Addresses
#define REG_SYS_SET__MBPOS_SFTY_TIM_TM           (REG_SYS_SET__MBPOS+0)       //WD_TIM_TM
#define REG_SYS_SET__MBPOS_WD_TIM_TM             (REG_SYS_SET__MBPOS+1)       //WD_TIM_TM
// STRING
#define REG_SYS_SET__STR_SFTY_TIM_TM             "SFTY_TIM_TM"
#define REG_SYS_SET__STR_WD_TIM_TM               "WD_TIM_TM"

/** @def SYSTEM COMMANDS
 */
#define REG_SYS_CMD__GID                         (uint16_t)72                //unique ID
// located variable
#define REG_SYS_CMD__ZONE                        PLC_LT_M                    //memory ID
#define REG_SYS_CMD__TYPESZ                      PLC_LSZ_X                   //data type ID
#define REG_SYS_CMD__GROUP                       REG_SYS__GROUP
#define REG_SYS_CMD__A00                         (int32_t)3                  //arg0: ID of subgroup
#define REG_SYS_CMD__A01                         REG_AXX_ADDR                //arg1: ID of subgroup
#define REG_SYS_CMD__A02                         REG_AXX_NONE                //arg2: ID of subgroup
#define REG_SYS_CMD__TYPE                        TYPE_BOOL                   //sata type
#define REG_SYS_CMD__TYPE_SZ                     TYPE_BOOL_SZ                //size of data type (bytes)
#define REG_SYS_CMD__TYPE_WSZ                    TYPE_BOOL_WSZ               //size of data type (words)
// position (offset) in REGS
#define REG_SYS_CMD__SZ                          REG_SYS_CMD_SZ              //number of registers
#define REG_SYS_CMD__POS                         (uint16_t)REG_CALC_POS(REG_SYS_STAT__POS, REG_SYS_STAT__SZ)
#define REG_SYS_CMD__SADDR                       (uint16_t)0                 //start register address
// position (offset) in Data Table
#define REG_SYS_CMD__DPOS                        (uint16_t)REG_CALC_MBPOS(REG_DO_PWM_ALLOW__DPOS, REG_DO_PWM_ALLOW__SZ, REG_DO_PWM_ALLOW__TYPE_WSZ, 0)
#define REG_SYS_CMD__DPOS_END                    (uint16_t)REG_CALC_MBPOS(REG_SYS_CMD__DPOS, REG_SYS_CMD__SZ, REG_SYS_CMD__TYPE_WSZ, 0)-1
#define REG_SYS_CMD__DTABLE                      REG_DATA_BOOL_TABLE_ID      //data table ID
// position (offset) in ModBus Table
#define REG_SYS_CMD__MBPOS                       (uint16_t)REG_CALC_MBPOS(REG_DO_PWM_ALLOW__MBPOS, REG_DO_PWM_ALLOW__SZ, REG_DO_PWM_ALLOW__TYPE_WSZ, REG_RESERVE)
#define REG_SYS_CMD__MBPOS_END                   (uint16_t)REG_CALC_MBPOS(REG_SYS_CMD__MBPOS, REG_SYS_CMD__SZ, REG_SYS_CMD__TYPE_WSZ, 0)-1
#define REG_SYS_CMD__MBTABLE                     MBRTU_COIL_TABLE_ID         //modbus table ID
// EEPROM
#define REG_SYS_CMD__RETAIN                      REG_RETAIN_NONE
//
// REGS Positions
#define REG_SYS_CMD__POS_LED_USER                (REG_SYS_CMD__POS+0)         //LED_USER
#define REG_SYS_CMD__POS_SFTY_TIM_RST            (REG_SYS_CMD__POS+1)         //SFTY_TIM_RST
#define REG_SYS_CMD__POS_WD_TIM_RST              (REG_SYS_CMD__POS+2)         //WD_TIM_RST
// ModBus Addresses
#define REG_SYS_CMD__MBPOS_LED_USER              (REG_SYS_CMD__MBPOS+0)       //LED_USER
#define REG_SYS_CMD__MBPOS_SFTY_TIM_RST          (REG_SYS_CMD__MBPOS+1)       //SFTY_TIM_RST
#define REG_SYS_CMD__MBPOS_WD_TIM_RST            (REG_SYS_CMD__MBPOS+2)       //WD_TIM_RST
// STRING
#define REG_SYS_CMD__STR_LED_USER                "LED_USER"
#define REG_SYS_CMD__STR_SFTY_TIM_RST            "SFTY_TIM_RST"
#define REG_SYS_CMD__STR_WD_TIM_RST              "WD_TIM_RST"


//USER DATA

//group ID
#define REG_USER_DATA__GROUP                     (uint16_t)8
//quantity of registers
#define REG_USER_DATA1_SZ                        (uint16_t)32
#define REG_USER_DATA2_SZ                        (uint16_t)64

/** @def USER DATA 1 (BOOL)
 */
#define REG_USER_DATA1__GID                      (uint16_t)80               //unique ID
// located variable
#define REG_USER_DATA1__ZONE                     PLC_LT_M                   //memory ID
#define REG_USER_DATA1__TYPESZ                   PLC_LSZ_X                  //data type ID
#define REG_USER_DATA1__GROUP                    REG_USER_DATA__GROUP       //group ID
#define REG_USER_DATA1__A00                      (int32_t)1                 //subgroup ID
#define REG_USER_DATA1__A01                      REG_AXX_ADDR
#define REG_USER_DATA1__A02                      REG_AXX_NONE
#define REG_USER_DATA1__TYPE                     TYPE_BOOL                  //sata type
#define REG_USER_DATA1__TYPE_SZ                  TYPE_BOOL_SZ               //size of data type in bytes
#define REG_USER_DATA1__TYPE_WSZ                 TYPE_BOOL_WSZ              //size of data type in words
// position (offset) in REGS
#define REG_USER_DATA1__SZ                       REG_USER_DATA1_SZ          //number of registers
#define REG_USER_DATA1__POS                      (uint16_t)REG_CALC_POS(REG_SYS_CMD__POS, REG_SYS_CMD__SZ)
#define REG_USER_DATA1__SADDR                    (uint16_t)0                //start register address
// position (offset) in Data Table
#define REG_USER_DATA1__DPOS                     (uint16_t)REG_CALC_MBPOS(REG_SYS_CMD__DPOS, REG_SYS_CMD__SZ, REG_SYS_CMD__TYPE_WSZ, 0)
#define REG_USER_DATA1__DPOS_END                 (uint16_t)REG_CALC_MBPOS(REG_USER_DATA1__DPOS, REG_USER_DATA1__SZ, REG_USER_DATA1__TYPE_WSZ, 0)-1
#define REG_USER_DATA1__DTABLE                   REG_DATA_BOOL_TABLE_ID     //data table ID
// position (offset) in ModBus Table
#define REG_USER_DATA1__MBPOS                    (uint16_t)REG_CALC_MBPOS(REG_SYS_CMD__MBPOS, REG_SYS_CMD__SZ, REG_SYS_CMD__TYPE_WSZ, REG_RESERVE)
#define REG_USER_DATA1__MBPOS_END                (uint16_t)REG_CALC_MBPOS(REG_USER_DATA1__MBPOS, REG_USER_DATA1__SZ, REG_USER_DATA1__TYPE_WSZ, 0)-1
#define REG_USER_DATA1__MBTABLE                  MBRTU_COIL_TABLE_ID        //modbus table ID
// EEPROM2
#define REG_USER_DATA1__RETAIN                   (int8_t)16
// STRING
#define REG_USER_DATA1__STR                      "User Data %d"

/** @def USER DATA 2 (WORD)
 */
#define REG_USER_DATA2__GID                      (uint16_t)81               //unique ID
// located variable
#define REG_USER_DATA2__ZONE                     PLC_LT_M                   //memory ID
#define REG_USER_DATA2__TYPESZ                   PLC_LSZ_W                  //data type ID
#define REG_USER_DATA2__GROUP                    REG_USER_DATA__GROUP       //group ID
#define REG_USER_DATA2__A00                      (int32_t)2                 //subgroup ID
#define REG_USER_DATA2__A01                      REG_AXX_ADDR
#define REG_USER_DATA2__A02                      REG_AXX_NONE
#define REG_USER_DATA2__TYPE                     TYPE_WORD                  //data type
#define REG_USER_DATA2__TYPE_SZ                  TYPE_WORD_SZ               //size of data type in bytes
#define REG_USER_DATA2__TYPE_WSZ                 TYPE_WORD_WSZ              //size of data type in words
// position (offset) in REGS
#define REG_USER_DATA2__SZ                       REG_USER_DATA2_SZ          //number of registers
#define REG_USER_DATA2__POS                      (uint16_t)REG_CALC_POS(REG_USER_DATA1__POS, REG_USER_DATA1__SZ)
#define REG_USER_DATA2__SADDR                    (uint16_t)0                //start register address
// position (offset) in Data Table
#define REG_USER_DATA2__DPOS                     (uint16_t)REG_CALC_MBPOS(REG_SYS_SET__DPOS, REG_SYS_SET__SZ, REG_SYS_SET__TYPE_WSZ, 0)
#define REG_USER_DATA2__DPOS_END                 (uint16_t)REG_CALC_MBPOS(REG_USER_DATA2__DPOS, REG_USER_DATA2__SZ, REG_USER_DATA2__TYPE_WSZ, 0)-1
#define REG_USER_DATA2__DTABLE                   REG_DATA_NUMB_TABLE_ID     //data table ID
// position (offset) in ModBus Table
#define REG_USER_DATA2__MBPOS                    (uint16_t)REG_CALC_MBPOS(REG_SYS_SET__MBPOS, REG_SYS_SET__SZ, REG_SYS_SET__TYPE_WSZ, 0)
#define REG_USER_DATA2__MBPOS_END                (uint16_t)REG_CALC_MBPOS(REG_USER_DATA2__MBPOS, REG_USER_DATA2__SZ, REG_USER_DATA2__TYPE_WSZ, 0)-1
#define REG_USER_DATA2__MBTABLE                  MBRTU_HOLD_TABLE_ID        //modus table ID
// EEPROM
#define REG_USER_DATA2__RETAIN                   (int8_t)32
// STRING
#define REG_USER_DATA2__STR                      "User Data %d"

//=============================================================================

/** @def Position of last register in REGS
 */
#define REG_LAST_POS                             (uint16_t)REG_CALC_POS(REG_USER_DATA2__POS, REG_USER_DATA2__SZ)

/** @def Position of last register in Data-table
 */
#define REG_DATA_BOOL_LAST_POS                   (uint16_t)(REG_USER_DATA1__DPOS_END+1)
#define REG_DATA_NUMB_LAST_POS                   (uint16_t)(REG_USER_DATA2__DPOS_END+1)

/** @def Position of last register in ModBus Table
 */
#define REG_LAST_COIL_POS                        (uint16_t)(REG_USER_DATA1__MBPOS_END+1)
#define REG_LAST_HOLD_POS                        (uint16_t)(REG_USER_DATA2__MBPOS_END+1)
#define REG_LAST_DISC_POS                        (uint16_t)(REG_DI_CNTR_SETPOINT_REACHED__MBPOS_END+1)
#define REG_LAST_INPT_POS                        (uint16_t)(REG_SYS_STAT__MBPOS_END+1)

//=============================================================================

/** @def Max. register address
 */
#define REG_ADDR_MAX                             (uint16_t)0xFFFF

/** @def Quantity of registers
 */
#define REG_SZ                                   REG_LAST_POS

/** @def Quantity of registers
 *       (Data Table)
 */
#define REG_DATA_BOOL_SZ                         REG_DATA_BOOL_LAST_POS
#define REG_DATA_NUMB_SZ                         REG_DATA_NUMB_LAST_POS

/** @def Quantity of registers
 *       (ModBus Table)
 */
#define MBRTU_COIL_SZ                            REG_LAST_COIL_POS
#define MBRTU_DISC_SZ                            REG_LAST_DISC_POS
#define MBRTU_HOLD_SZ                            REG_LAST_HOLD_POS
#define MBRTU_INPT_SZ                            REG_LAST_INPT_POS
//
/** @def Start-End address
 *       (ModBus Table)
 */
#define MBRTU_COIL_START                        (uint16_t)0
#define MBRTU_COIL_END                          (uint16_t)(MBRTU_COIL_START+MBRTU_COIL_SZ-1)
#define MBRTU_DISC_START                        (uint16_t)0
#define MBRTU_DISC_END                          (uint16_t)(MBRTU_DISC_START+MBRTU_DISC_SZ-1)
#define MBRTU_HOLD_START                        (uint16_t)0
#define MBRTU_HOLD_END                          (uint16_t)(MBRTU_HOLD_START+MBRTU_HOLD_SZ-1)
#define MBRTU_INPT_START                        (uint16_t)0
#define MBRTU_INPT_END                          (uint16_t)(MBRTU_INPT_START+MBRTU_INPT_SZ-1)

// REGMAP (END) =============================================================
//=============================================================================
//=============================================================================

#endif //REG_MAP_H
