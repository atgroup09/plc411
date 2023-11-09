/* @page rtos-data.h
 *       PLC411::RTE
 *       RTOS-task T_DATA
 *       2022, atgroup09@gmail.com
 */

#ifndef RTOS_TASK_DATA_H
#define RTOS_TASK_DATA_H

#include "reg-init.h"
#include "rtos.h"

#ifdef RTE_MOD_DI
#include "di.h"
#endif //RTE_MOD_DI

#ifdef RTE_MOD_DO
#include "do.h"
#endif //RTE_MOD_DO

#ifdef RTE_MOD_AI
#include "ai.h"
#endif //RTE_MOD_AI

#include "rtos-led.h"


/** @brief  Task DATA_T
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return none.
 *  @details The task is blocked - wait for data in Queue.
 */
void RTOS_DATA_Task(void *ParamsIn);

#endif //RTOS_TASK_DATA_H
