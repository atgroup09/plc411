/* @page do.c
 *       PLC411::RTE
 *       DO driver
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022-2023, atgroup09@gmail.com
 */

#include "do.h"


uint8_t PLC_DO_POSTPONED = BIT_FALSE;


/** @brief  Init. DO.
 *  @param  DOIn - channel.
 *  @return None.
 */
void PlcDO_Init(PlcDO_t *DOIn)
{
	if(DOIn)
	{
		GPIO_InitTypeDef GpioDef;

		//Enable clock
		__HAL_RCC_GPIOA_CLK_ENABLE();

		//GPIO Init (common settings)
		GpioDef.Mode  = GPIO_MODE_AF_PP;
		GpioDef.Pull  = GPIO_NOPULL;
		GpioDef.Speed = GPIO_SPEED_FREQ_LOW;

		//GPIO Init (individual settings by channel)
		switch(DOIn->Ch)
		{
			case PLC_DO_00:
				GpioDef.Pin       = PLC_DO_00__PIN;
				GpioDef.Alternate = GPIO_AF1_TIM2;
				PlcTim2_Init();
				DOIn->Port        = GPIOA;
				DOIn->Pin         = GPIO_PIN_0;
				DOIn->Tim         = &PLC_TIM2;
				DOIn->TimCh       = PLC_TIM2_DO_CH;
				break;

			case PLC_DO_01:
				GpioDef.Pin       = PLC_DO_01__PIN;
				GpioDef.Alternate = GPIO_AF2_TIM5;
				PlcTim5_Init();
				DOIn->Port        = GPIOA;
				DOIn->Pin         = GPIO_PIN_1;
				DOIn->Tim         = &PLC_TIM5;
				DOIn->TimCh       = PLC_TIM5_DO_CH;
				break;
		}

		//GPIO Init
		HAL_GPIO_Init(GPIOA, &GpioDef);
	}
}

/** @brief  DeInit. DO.
 *  @param  DOIn - channel.
 *  @return None.
 */
void PlcDO_DeInit(PlcDO_t *DOIn)
{
	if(DOIn)
	{
		PlcDO_Stop(DOIn);
		//GPIO DeInit
		HAL_GPIO_DeInit(DOIn->Port, DOIn->Pin);
	}
}

/** @brief  Start DO.
 *  @param  DOIn - channel.
 *  @return None.
 */
inline void PlcDO_Start(PlcDO_t *DOIn)
{
	if(DOIn)
	{
		PlcTim_StartChannel(DOIn->Tim, DOIn->TimCh);
	}
}

/** @brief  Stop DO.
 *  @param  DOIn - channel.
 *  @return None.
 */
inline void PlcDO_Stop(PlcDO_t *DOIn)
{
	if(DOIn)
	{
		PlcTim_RstCnt(DOIn->Tim);
		PlcTim_StopChannel(DOIn->Tim, DOIn->TimCh);
	}
}

/** @brief  Convert Period (ms) into 32-bit register value (ARR).
 *  @param  PeriodIn - period (ms).
 *  @return 32-bit register value (ARR).
 */
static uint32_t PlcDO_ConvPeriodMsToArr(float PeriodIn)
{
	return ((uint32_t)(PeriodIn/PLC_TIM2_MS));
}

/** @brief  Convert Pulse (%) into 32-bit register value (CCR).
 *  @param  PulseIn - pulse (%).
 *  @param  KaIn - scale factor.
 *  @param  KbIn - scale factor.
 *  @return 32-bit register value (CCR).
 */
static uint32_t PlcDO_ConvPulsePercToCcr(float PulseIn, float KaIn, float KbIn)
{
	return ((uint32_t)ScaleA(PulseIn, KaIn, KbIn));
}

/** @brief  Set new period value into TIM.PWM.
 *  @param  DOIn - channel.
 *  @param  PeriodIn - new period value (ms):
 *  @arg    = PLC_DO_PWM_T__MIN ... PLC_DO_PWM_T__MAX
 *  @return New period value (ms).
 */
float PlcDO_SetPeriod(PlcDO_t *DOIn, float PeriodIn)
{
	float Period = PeriodIn;

	if(PeriodIn < PLC_DO_PWM_T__MIN)
	{
		Period = PLC_DO_PWM_T__MIN;
	}
	else if(PeriodIn > PLC_DO_PWM_T__MAX)
	{
		Period = PLC_DO_PWM_T__MAX;
	}

	if(DOIn)
	{
		//recalculate ARR
		DOIn->Arr = PlcDO_ConvPeriodMsToArr(Period);

		//recalculate scale factors
		DOIn->Ka = ScaleA_Ka(0.0, DOIn->Arr, PLC_DO_PWM_D__MIN, PLC_DO_PWM_D__MAX);
		DOIn->Kb = ScaleA_Kb(0.0, DOIn->Arr, PLC_DO_PWM_D__MIN, PLC_DO_PWM_D__MAX);

		PlcTim_SetChannelPeriod(DOIn->Tim, DOIn->Arr);
	}

	return (Period);
}

/** @brief  Set new pulse value (fill factor) into TIM.PWM.
 *  @param  DOIn - channel.
 *  @param  PulseIn - new pulse value (%):
 *  @arg    = PLC_DO_PWM_D__MIN ... PLC_DO_PWM_D__MAX
 *  @return New pulse value (%).
 */
float PlcDO_SetPulse(PlcDO_t *DOIn, float PulseIn)
{
	float Pulse = PulseIn;

	if(PulseIn < PLC_DO_PWM_D__MIN)
	{
		Pulse = PLC_DO_PWM_D__MIN;
	}
	else if(PulseIn > PLC_DO_PWM_D__MAX)
	{
		Pulse = PLC_DO_PWM_D__MAX;
	}

	if(DOIn)
	{
		//recalculate CCR
		DOIn->Ccr = PlcDO_ConvPulsePercToCcr(Pulse, DOIn->Ka, DOIn->Kb);
		PlcTim_SetChannelPulse(DOIn->Tim, DOIn->TimCh, DOIn->Ccr);
	}

	return (Pulse);
}

/** @brief  Set new normal value into TIM.PWM.
 *  @param  DOIn - channel.
 *  @param  ValIn - new normal value:
 *  @arg    = 0 - low output level
 *  @arg    = 1 - high output level
 *  @return None.
 */
void PlcDO_SetNormVal(PlcDO_t *DOIn, uint8_t ValIn)
{
	if(!ValIn)
	{
		PlcDO_SetPulse(DOIn, PLC_DO_PWM_D__MIN);
	}
	else
	{
		PlcDO_SetPulse(DOIn, PLC_DO_PWM_D__MAX);
	}
}
