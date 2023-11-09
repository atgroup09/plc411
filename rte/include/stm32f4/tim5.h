/* @page tim5.h
 *       PLC411::RTE
 *       TIM5 driver
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022-2023, atgroup09@gmail.com
 */

/** @note
 *
 *        PA1 <- TIM5.CH2.PWM <- DO.1 <- DMA1.STR4.CH6 (MemToPeriph) <- [.PSC, .ARR]
 *
 *        TIM settings
 *        - .FREQ.BUS = 100 MHz (1 bus-tick is 10 ns)
 *        - .PSC      = 100     (16 bit, 1 TIM-tick is 1000000 Hz)
 *        - .RCR      = 0       (8  bit)
 *        - .ARR      = T       (32 bit)
 *           where T is period  (10 ... 1000000000)
 *
 *        TIM5 is 32-bit timer
 */

#ifndef PLC_TIM5_H
#define PLC_TIM5_H

#include "tim.h"


#ifdef RTE_MOD_DO

/** @def GPIO references
 */
#define PLC_TIM5_DO_CH                           TIM_CHANNEL_2


/** @def TIM tick frequency
 */
#define PLC_TIM5_HZ                              (uint32_t)1000000  //Hz
#define PLC_TIM5_MS                              (float)0.001       //ms

/** #def TIM prescaler
 */
// (.PSC)
#define PLC_TIM5_PRESCALER                       (uint32_t)((PLC_APB1_TCLK_FREQ/PLC_TIM5_HZ)-1)	 //100 counts for 1 TIM-tick

/** @def TIM period (quantity of ticks to reload)
 */
// (.ARR)
#define PLC_TIM5_PERIOD__MIN                     (uint32_t)(10-1)
#define PLC_TIM5_PERIOD__1HZ                     (uint32_t)(1000000-1)
#define PLC_TIM5_PERIOD__10SEC                   (uint32_t)(10000000-1)
#define PLC_TIM5_PERIOD__MAX                     (uint32_t)(1000000000-1)

/** @def Use DMA
 */
//#define PLC_TIM5_DMA


/** @brief  Init. TIM5
 *  @param  None.
 *  @return None.
 */
void PlcTim5_Init(void);

/** @brief  DeInit. TIM5
 *  @param  None.
 *  @return None.
 */
void PlcTim5_DeInit(void);

#endif //RTE_MOD_DO

#endif //PLC_TIM5_H
