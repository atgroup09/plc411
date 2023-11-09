/* @page rtos-do.h
 *       PLC411::RTE
 *       RTOS-task DO_T
 *       2022-2023, atgroup09@gmail.com
 */

#ifndef RTOS_TASK_DO_H
#define RTOS_TASK_DO_H

#include "do.h"

#include "reg.h"
#include "rtos.h"

#ifdef DEBUG
#include "debug-log.h"
#endif // DEBUG


#ifdef RTE_MOD_DO

/** @brief  Task DO_T (blocked)
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return None.
 */
void RTOS_DO_Task(void *ParamsIn);


#endif // RTE_MOD_DO

#endif //RTOS_TASK_DO_H
