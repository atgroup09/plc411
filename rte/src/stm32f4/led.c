/* @page led.c
 *       PLC411::RTE
 *       LED driver
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022-2023, atgroup09@gmail.com
 */

#include "led.h"


/** @brief  Init LED.
 *  @param  LEDIn - channel.
 *  @return None.
 */
void PlcLed_Init(PlcLED_t *LEDIn)
{
	if(LEDIn)
	{
		GPIO_InitTypeDef GpioDef;

		//Enable clock
		__HAL_RCC_GPIOB_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();

		//GPIO configuration
		GpioDef.Speed = GPIO_SPEED_FREQ_LOW;

		//GPIO Init (individual settings by channel)
		switch(LEDIn->Ch)
		{
			case PLC_LED_USER:
				LEDIn->Port    = PLC_LED_USER_PORT;
				LEDIn->Pin     = PLC_LED_USER_PIN;
				LEDIn->DOMode  = PLC_LED_USER_DO_MODE;

				GpioDef.Pin    = LEDIn->Pin;
				GpioDef.Mode   = PLC_LED_USER_MODE;
				GpioDef.Pull   = PLC_LED_USER_PULL;
				break;

			case PLC_LED_NET:
				LEDIn->Port    = PLC_LED_NET_PORT;
				LEDIn->Pin     = PLC_LED_NET_PIN;
				LEDIn->DOMode  = PLC_LED_NET_DO_MODE;

				GpioDef.Pin    = LEDIn->Pin;
				GpioDef.Mode   = PLC_LED_NET_MODE;
				GpioDef.Pull   = PLC_LED_NET_PULL;
				break;

			case PLC_LED_ERR:
				LEDIn->Port    = PLC_LED_ERR_PORT;
				LEDIn->Pin     = PLC_LED_ERR_PIN;
				LEDIn->DOMode  = PLC_LED_ERR_DO_MODE;

				GpioDef.Pin    = LEDIn->Pin;
				GpioDef.Mode   = PLC_LED_ERR_MODE;
				GpioDef.Pull   = PLC_LED_ERR_PULL;
				break;

			case PLC_LED_RUN:
				LEDIn->Port    = PLC_LED_RUN_PORT;
				LEDIn->Pin     = PLC_LED_RUN_PIN;
				LEDIn->DOMode  = PLC_LED_RUN_DO_MODE;

				GpioDef.Pin    = LEDIn->Pin;
				GpioDef.Mode   = PLC_LED_RUN_MODE;
				GpioDef.Pull   = PLC_LED_RUN_PULL;
				break;
		}

		HAL_GPIO_Init(LEDIn->Port, &GpioDef);
		PlcGpio_DO_Off(LEDIn->Port, LEDIn->Pin, LEDIn->DOMode);
	}
}

/** @brief  DeInit LED.
 *  @param  LEDIn - channel.
 *  @return None.
 */
void PlcLed_DeInit(PlcLED_t *LEDIn)
{
	if(LEDIn)
	{
		HAL_GPIO_DeInit(LEDIn->Port, LEDIn->Pin);
	}
}
