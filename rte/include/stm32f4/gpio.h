/* @page gpio.h
 *       PLC411::RTE
 *       GPIO
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022, atgroup09@gmail.com
 */

/* @note
 *       DI - discrete inputs
 *       DO - discrete outputs
 */

#ifndef PLC_GPIO_H
#define PLC_GPIO_H

#include "config.h"



/** @def GPIO states
 */
#define PLC_GPIO_OFF         (uint8_t)0  //off
#define PLC_GPIO_ON          (uint8_t)1  //on
#define PLC_GPIO_ERR         (uint8_t)2  //error

/** @def DO mode
 */
#define PLC_GPIO_DO_PP       (uint8_t)0  //push-pull
#define PLC_GPIO_DO_OD       (uint8_t)1  //open-drain (LoLevel to GND, HiLevel to Up or Down)

/** @def DI mode
 */
#define PLC_GPIO_DI_NORM     (uint8_t)0  //normal
#define PLC_GPIO_DI_REVERSE  (uint8_t)1  //reverse


/** @brief  DO: Turn-On
 *  @param  PortIn - port
 *  @param  PinIn  - pin number
 *  @param  PinModeIn - pin mode:
 *  @arg    = PLC_GPIO_DO_PP
 *  @arg    = PLC_GPIO_DO_OD
 *  @return Current Pin-status:
 *  @arg     = PLC_GPIO_ON
 */
uint8_t PlcGpio_DO_On(GPIO_TypeDef *PortIn, uint16_t PinIn, uint8_t PinModeIn);

/** @brief  DO: Turn-Off
 *  @param  PortIn - port
 *  @param  PinIn  - pin number
 *  @param  PinModeIn - pin mode:
 *  @arg    = PLC_GPIO_DO_PP
 *  @arg    = PLC_GPIO_DO_OD
 *  @return Current Pin-status:
 *  @arg    = PLC_GPIO_OFF
 */
uint8_t PlcGpio_DO_Off(GPIO_TypeDef *PortIn, uint16_t PinIn, uint8_t PinModeIn);

/** @brief  DO: Toggle.
 *  @param  PortIn - port
 *  @param  PinIn  - pin number
 *  @param  PinModeIn - pin mode:
 *  @arg    = PLC_GPIO_DO_PP
 *  @arg    = PLC_GPIO_DO_OD
 *  @return Current Pin-status:
 *  @arg    = PLC_GPIO_OFF
 *  @arg    = PLC_GPIO_ON
 */
uint8_t PlcGpio_DO_Toggle(GPIO_TypeDef *PortIn, uint16_t PinIn, uint8_t PinModeIn);

/** @brief  DO: Set state
 *  @param  PortIn - port;
 *  @param  PinIn  - pin number
 *  @param  PinModeIn - pin mode:
 *  @arg    = PLC_GPIO_DO_PP
 *  @arg    = PLC_GPIO_DO_OD
 *  @param  StateIn - state:
 *  @arg    = PLC_GPIO_OFF
 *  @arg    = PLC_GPIO_ON
 *  @return Current Pin-status:
 *  @arg    = PLC_GPIO_OFF
 *  @arg    = PLC_GPIO_ON
 */
uint8_t PlcGpio_DO_Set(GPIO_TypeDef *PortIn, uint16_t PinIn, uint8_t PinModeIn, uint8_t StateIn);

/** @brief  DO: Get current state
 *  @param  PortIn - port
 *  @param  PinIn  - pin number
 *  @param  PinModeIn - pin mode:
 *  @arg    = PLC_GPIO_DO_PP
 *  @arg    = PLC_GPIO_DO_OD
 *  @return Current state:
 *  @arg    = PLC_GPIO_OFF
 *  @arg    = PLC_GPIO_ON
 */
uint8_t PlcGpio_DO_Get(GPIO_TypeDef *PortIn, uint16_t PinIn, uint8_t PinModeIn);

/** @brief  DI: Get current state.
 *  @param  PortIn - port
 *  @param  PinIn  - pin number
 *  @param  PinModeIn - pin mode:
 *  @arg    = PLC_GPIO_DI_NORM
 *  @arg    = PLC_GPIO_DI_REVERSE
 *  @return Current state:
 *  @arg    = PLC_GPIO_OFF
 *  @arg    = PLC_GPIO_ON
 */
uint8_t PlcGpio_DI_Get(GPIO_TypeDef *PortIn, uint16_t PinIn, uint8_t PinModeIn);


#endif //PLC_GPIO_H
