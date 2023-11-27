/* @page reg-map-ext.h
 *       Registers map (extended defines)
 *       2020-2022
 */

#include <stdint.h>

#ifndef REG_MAP_EXT_H
#define REG_MAP_EXT_H


/** @def Located variables
 *       zones
 */
#define PLC_LT_I                       (uint8_t)0   //Inputs
#define PLC_LT_M                       (uint8_t)1   //Memory
#define PLC_LT_Q                       (uint8_t)2   //Outputs


/** @def Located variables
 *       types
 */
#define PLC_LSZ_X                      (uint8_t)0   //BOOL
#define PLC_LSZ_B                      (uint8_t)1   //SINT, USINT, BYTE, STRING  (CHAR*)
#define PLC_LSZ_W                      (uint8_t)2   //INT,  UINT,  WORD, WSTRING (WCHAR*)
#define PLC_LSZ_D                      (uint8_t)3   //DINT, UDINT, REAL, DWORD
#define PLC_LSZ_L                      (uint8_t)4   //LINT, ULINT, LREAL, LWORD

/** @def Located variables
 *       number bytes for types
 */
#define PLC_BSZ_X                      (uint8_t)1
#define PLC_BSZ_B                      (uint8_t)1
#define PLC_BSZ_W                      (uint8_t)2
#define PLC_BSZ_D                      (uint8_t)4
#define PLC_BSZ_L                      (uint8_t)8


#endif //REG_MAP_EXT_H
