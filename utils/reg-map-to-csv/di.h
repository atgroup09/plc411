/* @page di.h
 *       Discrete Inputs
 *       platform-dependent code
 *       stm32f1xx, SPL
 *       2020-2022
 */

#ifndef PLC_DI_H
#define PLC_DI_H


/** @def Channel number
 */
#define PLC_DI_00                                (uint8_t)0
#define PLC_DI_01                                (uint8_t)1


/** @def Quantity of channels
 */
#define PLC_DI_SZ                                (uint16_t)(PLC_DI_01+1)


#endif //PLC_DI_H
