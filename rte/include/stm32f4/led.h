/* @page led.h
 *       PLC411::RTE
 *       LED driver
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022-2023, atgroup09@gmail.com
 */

/** @note
 *        PC13 <- LED_USER (OFF/ON)
 *        PB12 <- LED_NET  (OFF/ON)
 *        PB13 <- LED_ERR  (OFF/ON)
 *        PB14 <- LED_RUN  (OFF/ON)
 */

#ifndef PLC_LED_H
#define PLC_LED_H

#include "gpio.h"


/** @def Channel number
 */
#define PLC_LED_USER            0
#define PLC_LED_NET             1
#define PLC_LED_ERR             2
#define PLC_LED_RUN             3

/** @def Quantity of channels
 */
#define PLC_LED_SZ              (uint8_t)(PLC_LED_RUN+1)


/** @def LED_USER
 */
#define PLC_LED_USER_PORT        GPIOC
#define PLC_LED_USER_PIN         GPIO_PIN_13
#define PLC_LED_USER_MODE		 GPIO_MODE_OUTPUT_OD
#define PLC_LED_USER_PULL        GPIO_NOPULL
#define PLC_LED_USER_DO_MODE     PLC_GPIO_DO_OD

/** @def LED_NET
 */
#define PLC_LED_NET_PORT         GPIOB
#define PLC_LED_NET_PIN          GPIO_PIN_12
#define PLC_LED_NET_MODE		 GPIO_MODE_OUTPUT_PP
#define PLC_LED_NET_PULL         GPIO_PULLDOWN
#define PLC_LED_NET_DO_MODE      PLC_GPIO_DO_PP

/** @def LED_ERR
 */
#define PLC_LED_ERR_PORT         GPIOB
#define PLC_LED_ERR_PIN          GPIO_PIN_13
#define PLC_LED_ERR_MODE		 GPIO_MODE_OUTPUT_PP
#define PLC_LED_ERR_PULL         GPIO_PULLDOWN
#define PLC_LED_ERR_DO_MODE      PLC_GPIO_DO_PP

/** @def LED_RUN
 */
#define PLC_LED_RUN_PORT         GPIOB
#define PLC_LED_RUN_PIN          GPIO_PIN_14
#define PLC_LED_RUN_MODE		 GPIO_MODE_OUTPUT_PP
#define PLC_LED_RUN_PULL         GPIO_PULLDOWN
#define PLC_LED_RUN_DO_MODE      PLC_GPIO_DO_PP


/** @typedef LED-channel settings
 *           main type
 */
typedef struct PlcLED_t_
{
	//CONSTANTS

	//@var Channel number
	//@arg = 0..15
	uint8_t Ch;

	//SETTINGS

    //@var Channel mode
   	//@arg = 0..1
   	uint8_t Mode;

	//GPIO

	//@var PORT
	GPIO_TypeDef *Port;

	//@var PIN
	uint16_t Pin;

	//@var DO MODE
	uint8_t DOMode;

} PlcLED_t;


/** @def Modes
 */
#define PLC_LED_MODE_OFF         (uint8_t)0  //off
#define PLC_LED_MODE_ON          (uint8_t)1  //on


/** @def Settings by default
 */
#define PLC_LED_MODE_DEF      	 PLC_LED_MODE_OFF


/** @def Queue item
 *       main settings
 */
typedef struct PlcLED_Q_t_
{
    //@var Channel number
    uint8_t Ch;
    //@var Item ID
    uint8_t ID;
    //@var Value
    uint8_t Val;

} PlcLED_Q_t;

/** @def Queue IDs
 */
#define PLC_LED_Q_ID_NONE        (uint8_t)0
#define PLC_LED_Q_ID_MODE        (uint8_t)1   //mode


/** @brief  Init LED.
 *  @param  LEDIn - channel.
 *  @return None.
 */
void PlcLed_Init(PlcLED_t *LEDIn);

/** @brief  DeInit LED.
 *  @param  LEDIn - channel.
 *  @return None.
 */
void PlcLed_DeInit(PlcLED_t *LEDIn);

#endif //PLC_LED_H
