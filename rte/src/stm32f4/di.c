/* @page di.c
 *       PLC411::RTE
 *       DI driver
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022, atgroup09@gmail.com
 */

#include "di.h"


/** @var DI Callback user-functions
 */
PLC_DI_UserFunc_t PLC_DI00_USER_FUNC;
PLC_DI_UserFunc_t PLC_DI01_USER_FUNC;


/** @brief  Init. DI.
 *  @param  None.
 *  @return None.
 */
void PlcDI_Init(void)
{
	GPIO_InitTypeDef GpioDef;

	//Enable clock
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	//GPIO Init.
	GpioDef.Pin  = PLC_DI_00__PIN;
	GpioDef.Mode = GPIO_MODE_IT_RISING_FALLING;
	GpioDef.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(PLC_DI_00__PORT, &GpioDef);

	GpioDef.Pin  = PLC_DI_01__PIN;
	GpioDef.Mode = GPIO_MODE_IT_RISING_FALLING;
	GpioDef.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(PLC_DI_01__PORT, &GpioDef);

	//IRQ Init.
    // EXTI
    HAL_NVIC_SetPriority(EXTI9_5_IRQn, PLC_NVIC_PPRIO_DI_EXTI, PLC_NVIC_SPRIO_DI_EXTI);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, PLC_NVIC_PPRIO_DI_EXTI, PLC_NVIC_SPRIO_DI_EXTI);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

/** @brief  DeInit. DI.
 *  @param  None.
 *  @return None.
 */
void PlcDI_DeInit(void)
{
	//Disable IRQ
	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
	HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);

	//GPIO DeInit
	HAL_GPIO_DeInit(PLC_DI_00__PORT, PLC_DI_00__PIN);
	HAL_GPIO_DeInit(PLC_DI_01__PORT, PLC_DI_01__PIN);
}


/** @brief  Read channel normal value.
 *  @param  ChIn - channel number.
 *  @return Normal value.
 */
uint8_t PlcDI_ReadNormVal(uint8_t ChIn)
{
	switch(ChIn)
	{
		case PLC_DI_00:
			return (PlcGpio_DI_Get(PLC_DI_00__PORT, PLC_DI_00__PIN, PLC_GPIO_DI_NORM));
		case PLC_DI_01:
			return (PlcGpio_DI_Get(PLC_DI_01__PORT, PLC_DI_01__PIN, PLC_GPIO_DI_NORM));
	}

	return (BIT_FALSE);
}


/** @brief  EXTI9-5 IRQ Handler.
 *  @param  None.
 *  @return None.
 */
void EXTI9_5_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(PLC_DI_00__PIN);
}

/** @brief  EXTI15-10 IRQ Handler.
 *  @param  None.
 *  @return None.
 */
void EXTI15_10_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(PLC_DI_01__PIN);
}


/** @brief  EXTI line detection callbacks.
  * @param  PinIn - specifies the pins connected EXTI line.
  * @return None.
  */
void HAL_GPIO_EXTI_Callback(uint16_t PinIn)
{
	PlcDI_IRQ_Q_t Data;

	if(PinIn == PLC_DI_00__PIN)
	{
		if(PLC_DI00_USER_FUNC.Exti != NULL)
		{
			Data.Ch  = PLC_DI_00;
			Data.Val = PlcDI_ReadNormVal(Data.Ch);
			PLC_DI00_USER_FUNC.Exti(Data);
		}
	}
	else if(PinIn == PLC_DI_01__PIN)
	{
		if(PLC_DI01_USER_FUNC.Exti != NULL)
		{
			Data.Ch  = PLC_DI_01;
			Data.Val = PlcDI_ReadNormVal(Data.Ch);
			PLC_DI01_USER_FUNC.Exti(Data);
		}
	}
}
