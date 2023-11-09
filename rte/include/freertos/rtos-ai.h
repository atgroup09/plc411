/* @page rtos-ai.h
 *       PLC411::RTE
 *       RTOS-task AI_T
 *       2022-2023, atgroup09@gmail.com
 */

#ifndef RTOS_AI_H
#define RTOS_AI_H

#include "ai.h"
#include "tmp-mcu.h"
#include "tmp36.h"

#include "reg.h"
#include "rtos.h"

#ifdef DEBUG
#include "debug-log.h"
#endif // DEBUG


#ifdef RTE_MOD_AI

/** @brief  AI_TIM Handler (one-shot).
 *  @param  TimerIn - timer.
 *  @return None.
 *  @note   Delay of ADC conversion.
 */
void RTOS_AI_TIM_Handler(TimerHandle_t TimerIn);

/** @brief  Task AI_T (blocked)
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return None.
  */
void RTOS_AI_Task(void *ParamsIn);

#endif //RTE_MOD_AI

#endif //RTOS_AI_H
