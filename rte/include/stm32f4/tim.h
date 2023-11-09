/* @page tim.h
 *       PLC411::RTE
 *       TIM Common Handlers and Callbacks
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022-2023, atgroup09@gmail.com
 */

#ifndef PLC_TIM_H
#define PLC_TIM_H

#include "config.h"
#include "error.h"


/** @typedef TIM Callback user-functions
 */
typedef struct
{
    void (*Elapsed)(void);

} PLC_TIM_UserFunc_t;


/** @var TIM Handlers
 */
extern TIM_HandleTypeDef PLC_TIM2;
extern TIM_HandleTypeDef PLC_TIM5;

/** @var TIM Callback user-functions
 */
extern PLC_TIM_UserFunc_t PLC_TIM2_USER_FUNC;
extern PLC_TIM_UserFunc_t PLC_TIM5_USER_FUNC;


/** @brief  Start TIM.Channel.
 *  @param  TimIn - pointer to handle.
 *  @param  TimChIn - channel:
 *  @arg    = TIM_CHANNEL_1 ... TIM_CHANNEL_4
 *  @return None.
 */
void PlcTim_StartChannel(TIM_HandleTypeDef *HandleIn, uint32_t ChIn);

/** @brief  Stop TIM.Channel.
 *  @param  TimIn - pointer to handle.
 *  @param  TimChIn - channel:
 *  @arg    = TIM_CHANNEL_1 ... TIM_CHANNEL_4
 *  @return None.
 */
void PlcTim_StopChannel(TIM_HandleTypeDef *HandleIn, uint32_t ChIn);

/** @brief  Set period.
 *  @param  TimIn - pointer to handle.
 *  @param  PeriodIn - new value of period (32-bit register value)
 *  @return Set TIM.Period (ARR).
 */
void PlcTim_SetChannelPeriod(TIM_HandleTypeDef *TimIn, uint32_t PeriodIn);

/** @brief  Set pulse.
 *  @param  TimIn - pointer to handle.
 *  @param  TimChIn - channel:
 *  @arg    = TIM_CHANNEL_1 ... TIM_CHANNEL_4
 *  @param  PulseIn - new value of pulse (32-bit register value):
 *  @arg    = 0 ... TIM.Period.
 *  @return Set TIM.Channel.Pulse (CCR).
 */
void PlcTim_SetChannelPulse(TIM_HandleTypeDef *TimIn, uint32_t TimChIn, uint32_t PulseIn);

/** @brief  Start TIM.
 *  @param  TimIn - pointer to handle.
 *  @return None.
 */
void PlcTim_Start(TIM_HandleTypeDef *HandleIn);

/** @brief  Stop TIM.
 *  @param  TimIn - pointer to handle.
 *  @return None.
 */
void PlcTim_Stop(TIM_HandleTypeDef *HandleIn);

/** @brief  Set TIM.Counter.
 *  @param  TimIn - pointer to handle.
 *  @param  CntIn - counter value.
 *  @return None
 */
void PlcTim_SetCnt(TIM_HandleTypeDef *TimIn, uint32_t CntIn);

/** @brief  Reset TIM.Counter.
 *  @param  TimIn - pointer to handle.
 *  @return None
 */
void PlcTim_RstCnt(TIM_HandleTypeDef *TimIn);

#endif //PLC_TIM_H
