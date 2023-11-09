/* @page gpio.c
 *       PLC411::RTE
 *       GPIO
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022, atgroup09@gmail.com
 */

#include "gpio.h"


/** @brief  DO: Turn-On
 *  @param  PortIn - port
 *  @param  PinIn  - pin number
 *  @param  PinModeIn - pin mode:
 *  @arg    = PLC_GPIO_DO_PP
 *  @arg    = PLC_GPIO_DO_OD
 *  @return Current Pin-status:
 *  @arg    = PLC_GPIO_ON
 */
uint8_t PlcGpio_DO_On(GPIO_TypeDef *PortIn, uint16_t PinIn, uint8_t PinModeIn)
{
    if(PortIn)
    {
        if(PinModeIn)
        {
             HAL_GPIO_WritePin(PortIn, PinIn, GPIO_PIN_RESET);
        }
        else
        {
        	HAL_GPIO_WritePin(PortIn, PinIn, GPIO_PIN_SET);
        }
        return (PLC_GPIO_ON);
    }
    return (PLC_GPIO_ERR);
}

/** @brief  DO: Turn-Off
 *  @param  PortIn - port
 *  @param  PinIn  - pin number
 *  @param  PinModeIn - pin mode:
 *  @arg    = PLC_GPIO_DO_PP
 *  @arg    = PLC_GPIO_DO_OD
 *  @return Current Pin-status:
 *  @arg    = PLC_GPIO_OFF
 */
uint8_t PlcGpio_DO_Off(GPIO_TypeDef *PortIn, uint16_t PinIn, uint8_t PinModeIn)
{
    if(PortIn)
    {
        if(PinModeIn)
        {
             HAL_GPIO_WritePin(PortIn, PinIn, GPIO_PIN_SET);
        }
        else
        {
        	HAL_GPIO_WritePin(PortIn, PinIn, GPIO_PIN_RESET);
        }
        return (PLC_GPIO_OFF);
    }
    return (PLC_GPIO_ERR);
}

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
uint8_t PlcGpio_DO_Toggle(GPIO_TypeDef *PortIn, uint16_t PinIn, uint8_t PinModeIn)
{
    if(PortIn)
    {
        uint8_t State = PlcGpio_DO_Get(PortIn, PinIn, PinModeIn);
        return (State ? PlcGpio_DO_Off(PortIn, PinIn, PinModeIn) : PlcGpio_DO_On(PortIn, PinIn, PinModeIn));
    }
    return (PLC_GPIO_ERR);
}

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
uint8_t PlcGpio_DO_Set(GPIO_TypeDef *PortIn, uint16_t PinIn, uint8_t PinModeIn, uint8_t StateIn)
{
    if(PortIn)
    {
    	return (!StateIn ? PlcGpio_DO_Off(PortIn, PinIn, PinModeIn) : PlcGpio_DO_On(PortIn, PinIn, PinModeIn));
    }
    return (PLC_GPIO_ERR);
}

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
uint8_t PlcGpio_DO_Get(GPIO_TypeDef *PortIn, uint16_t PinIn, uint8_t PinModeIn)
{
    uint8_t Res = PLC_GPIO_ERR;

    if(PortIn)
    {
        assert_param(IS_GPIO_PIN(PinIn));
        Res = ((PortIn->ODR&PinIn) ? PLC_GPIO_ON : PLC_GPIO_OFF);
        if(PinModeIn) Res = !Res;
    }
    return (Res);
}

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
uint8_t PlcGpio_DI_Get(GPIO_TypeDef *PortIn, uint16_t PinIn, uint8_t PinModeIn)
{
    if(PortIn)
    {
    	GPIO_PinState Res = ((PinModeIn) ? !HAL_GPIO_ReadPin(PortIn, PinIn) : HAL_GPIO_ReadPin(PortIn, PinIn));
    	if(Res == GPIO_PIN_SET) return (BIT_TRUE);
    }
    return (BIT_FALSE);
}
