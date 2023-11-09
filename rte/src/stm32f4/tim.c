/* @page tim.c
 *       PLC411::RTE
 *       TIM Common Handlers and Callbacks
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022-2023, atgroup09@gmail.com
 */

#include "tim.h"


/** @var TIM Handlers
 */
TIM_HandleTypeDef PLC_TIM2;
TIM_HandleTypeDef PLC_TIM5;

/** @var TIM Callback user-functions
 */
PLC_TIM_UserFunc_t PLC_TIM2_USER_FUNC = { .Elapsed = NULL };
PLC_TIM_UserFunc_t PLC_TIM5_USER_FUNC = { .Elapsed = NULL };


/** @brief  Start TIM.Channel.
 *  @param  TimIn - pointer to handle.
 *  @param  TimChIn - channel:
 *  @arg    = TIM_CHANNEL_1 ... TIM_CHANNEL_4
 *  @return None
 */
void PlcTim_StartChannel(TIM_HandleTypeDef *TimIn, uint32_t TimChIn)
{
	if(TimIn == &PLC_TIM2 || TimIn == &PLC_TIM5)
	{
		HAL_TIM_PWM_Start(TimIn, TimChIn);
	}
}

/** @brief  Stop TIM.Channel.
 *  @param  TimIn - pointer to handle.
 *  @param  TimChIn - channel:
 *  @arg    = TIM_CHANNEL_1 ... TIM_CHANNEL_4
 *  @return None
 */
void PlcTim_StopChannel(TIM_HandleTypeDef *TimIn, uint32_t TimChIn)
{
	if(TimIn == &PLC_TIM2 || TimIn == &PLC_TIM5)
	{
		HAL_TIM_PWM_Stop(TimIn, TimChIn);
	}
}

/** @brief  Set period.
 *  @param  TimIn - pointer to handle.
 *  @param  PeriodIn - new value of period (32-bit register value)
 *  @return Set TIM.Period (ARR).
 */
void PlcTim_SetChannelPeriod(TIM_HandleTypeDef *TimIn, uint32_t PeriodIn)
{
	if(TimIn == &PLC_TIM2 || TimIn == &PLC_TIM5)
	{
		__HAL_TIM_SET_AUTORELOAD(TimIn, PeriodIn);
	}
}

/** @brief  Set pulse.
 *  @param  TimIn - pointer to handle.
 *  @param  TimChIn - channel:
 *  @arg    = TIM_CHANNEL_1 ... TIM_CHANNEL_4
 *  @param  PulseIn - new value of pulse (32-bit register value):
 *  @arg    = 0 ... TIM.Period.
 *  @return Set TIM.Channel.Pulse (CCR).
 */
void PlcTim_SetChannelPulse(TIM_HandleTypeDef *TimIn, uint32_t TimChIn, uint32_t PulseIn)
{
	if(TimIn == &PLC_TIM2 || TimIn == &PLC_TIM5)
	{
		__HAL_TIM_SET_COMPARE(TimIn, TimChIn, PulseIn);
	}
}

/** @brief  Start TIM.
 *  @param  TimIn - pointer to handle.
 *  @return None
 */
void PlcTim_Start(TIM_HandleTypeDef *TimIn)
{
	(void)TimIn;
}

/** @brief  Stop TIM.
 *  @param  TimIn - pointer to handle.
 *  @return None
 */
void PlcTim_Stop(TIM_HandleTypeDef *TimIn)
{
	(void)TimIn;
}

/** @brief  Set TIM.Counter.
 *  @param  TimIn - pointer to handle.
 *  @param  CntIn - counter value.
 *  @return None
 */
void PlcTim_SetCnt(TIM_HandleTypeDef *TimIn, uint32_t CntIn)
{
	if(TimIn == &PLC_TIM2 || TimIn == &PLC_TIM5)
	{
		__HAL_TIM_SET_COUNTER(TimIn, CntIn);
	}
}

/** @brief  Reset TIM.Counter.
 *  @param  TimIn - pointer to handle.
 *  @return None
 */
void PlcTim_RstCnt(TIM_HandleTypeDef *TimIn)
{
	PlcTim_SetCnt(TimIn, (uint32_t)0);
}
