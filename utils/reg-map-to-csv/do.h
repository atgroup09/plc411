/* @page do.h
 *       Discrete Outputs
 *       platform-dependent code
 *       stm32f1xx, SPL
 *       2020-2022
 */

#ifndef PLC_DO_H
#define PLC_DO_H


/** @def DO channel numbers
 */
#define PLC_DO_00                                (uint8_t)0
#define PLC_DO_01                                (uint8_t)1


/** @def Quantity of DO channels
 */
#define PLC_DO_SZ                                (uint16_t)(PLC_DO_01+1)


#endif //PLC_DO_H
