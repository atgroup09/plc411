/* @page reg.h
 *       Register functions
 *       2020-2022
 */

#ifndef REG_H
#define REG_H

#include <stdio.h>
#include <stdint.h>
#include "type.h"
#include "reg-map-ext.h"
#include "reg-map.h"


/** @typedef Register
 *           associations
 */
typedef struct REG_t_
{
    //@var unique ID of group/subgroup
    uint16_t GID;

    //@var IDx (position in REGS)
    uint16_t iReg;

    //@var Address (position in group)
    uint16_t iGroup;

    //@var Data type ID (type.h)
    uint8_t Type;

    //@var Data Table ID (reg-map.h)
    uint8_t DataTable;

    //@var ModBus Table ID (mbrtu.h)
    uint8_t  MbTable;

    //@var ModBus Address
    uint16_t MbAddr;

    //@var Retain (EEPROM) flag
    uint8_t Retain;

} REG_t;


/** @def Number of registers
 */
#define REG_SZ                         REG_LAST_POS


/** @def Max. register address
 */
#define REG_ADDR_MAX                   (uint16_t)0xFFFF


FILE *fp;
extern FILE *FP_MB[5];
extern char  FN_MB[5][16];
extern char  STR_MB[5][12];


/** @brief  Get size (bytes) of data type.
 *  @param  TyIn - ID of data type.
 *  @return Size of data type.
 */
uint8_t Type_GetSz(const uint8_t TyIn);


/** @brief  Get size (words) of data type.
 *  @param  TyIn - ID of data type.
 *  @return Size of data type.
 */
uint8_t Type_GetWSz(const uint8_t TyIn);


/** @brief  Init. group of registers in REGS.
 *  @param  GIDIn     - Unique ID of group/subgroup.
 *  @param  ZoneIn    - Zone ID.
 *  @param  TypeSzIn  - Data Type Size ID.
 *  @param  GroupIn   - Group ID.
 *  @param  TypeIn    - Data Type ID.
 *  @param  PosIn     - Start position in REGS (offset).
 *  @param  SzIn      - Number of registers.
 *  @param  SaddrIn   - Start register address.
 *  @param  MbTableIn - ModBus Table ID.
 *  @param  MbPosIn   - Start position in ModBus table (offset).
 *  @param  A00In     - Value of a_data[0] (<0 - not used; ex. -10 - use calculated register address).
 *  @param  A01In     - Value of a_data[1] (<0 - not used; ex. -10 - use calculated register address).
 *  @param  A02In     - Value of a_data[2] (<0 - not used; ex. -10 - use calculated register address).
 *  @param  DataTableIn - Data Table ID.
 *  @param  DataPosIn   - Start position in Data table (offset).
 *  @param  RetainIn     - Retain (EEPROM) flag:
 *  @arg                   = 0 - not retain
 *  @arg                   = 1 - retain
 *  @param  TitleIn     - String title.
 *  @return The number of inited registers.
 */
uint16_t REG_InitRegs(uint16_t GIDIn, uint8_t ZoneIn, uint8_t TypeSzIn, uint16_t GroupIn, uint8_t TypeIn, uint16_t PosIn, uint16_t SzIn, uint16_t SaddrIn, uint8_t MbTableIn, uint16_t MbPosIn, int32_t A00In, int32_t A01In, int32_t A02In, uint8_t DataTableIn, uint16_t DataPosIn, uint16_t RetainIn, const char *TitleIn);


/** @brief  Init. registers.
 *  @param  None.
 *  @return The number of inited registers.
 */
uint16_t REG_Init(void);


#endif //REG_H
