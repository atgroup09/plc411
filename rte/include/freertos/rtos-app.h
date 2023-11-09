/* @page rtos-app.h
 *       PLC411::RTE
 *       RTOS-task APP_T
 *       2023, atgroup09@gmail.com
 */

#ifndef RTOS_TASK_APP_H
#define RTOS_TASK_APP_H

#include "reg-init.h"
#include "app.h"

#ifdef RTE_MOD_APP_DEBUG_HANDLER
#include "proto-dbg-yaplc.h"
#endif //RTE_MOD_APP_DEBUG_HANDLER

#include "rtos-led.h"

#ifdef DEBUG
#include "debug-log.h"
#endif // DEBUG


/** @brief  Task APP_T (non-blocking)
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return none.
 */
void RTOS_APP_Task(void *ParamsIn);

/** @brief  APP_TIM Handler (one-shot)
 *  @param  TimerIn - timer.
 *  @return none.
 */
void RTOS_APP_TIM_Handler(TimerHandle_t TimerIn);


#endif //RTOS_TASK_APP_H
