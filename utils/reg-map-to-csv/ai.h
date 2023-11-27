/* @page ai.h
 *       AI driver (+ MCU-temperature sensor)
 *       platform-dependent code
 *       stm32f1xx, SPL
 *       2020-2022
 */

#ifndef PLC_AI_H
#define PLC_AI_H

/** @def Channels
 */
#define PLC_AI_00                                0
#define PLC_AI_01                                1
#define PLC_AI_MCU_TEMP                          2

/** @def Quantity of channels
 */
#define PLC_AI_SZ                                (uint8_t)(PLC_AI_MCU_TEMP+1)


#endif //PLC_AI_H
