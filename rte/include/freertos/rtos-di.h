/* @page rtos-di.h
 *       PLC411::RTE
 *       RTOS-task DI_T
 *       2022-2023, atgroup09@gmail.com
 */

#ifndef RTOS_TASK_DI_H
#define RTOS_TASK_DI_H

#include "di.h"

#include "reg.h"
#include "rtos.h"

#ifdef DEBUG
#include "debug-log.h"
#endif // DEBUG


#ifdef RTE_MOD_DI

/** @brief  Task DI_IRQ_T (blocked)
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return None.
 */
void RTOS_DI_IRQ_Task(void *ParamsIn);

/** @brief  Task DI_T (blocked)
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return None.
 */
void RTOS_DI_Task(void *ParamsIn);


/** @brief  DI_TACH_TIM Handler (one-shot)
 *  @param  TimerIn - timer.
 *  @return None.
 */
void RTOS_DI_TACH_TIM_Handler(TimerHandle_t TimerIn);

/** @brief  DI_FLTR_TIM Handler (one-shot)
 *  @param  TimerIn - timer.
 *  @return None.
 */
void RTOS_DI_FLTR_TIM_Handler(TimerHandle_t TimerIn);

#endif // RTE_MOD_DI

#endif //RTOS_TASK_DI_H
