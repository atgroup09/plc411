/* @page rtos-led.h
 *       PLC411::RTE
 *       RTOS-task LED_T
 *       2022-2023, atgroup09@gmail.com
 */

#ifndef RTOS_LED_H
#define RTOS_LED_H

#include "led.h"
#include "rtos.h"

#ifdef DEBUG
#include "debug-log.h"
#endif // DEBUG


/** @brief  Send mode into RTOS_LED_Q
 *  @param  ChIn - channel
 *  @param  ModeIn - mode
 *  @return None.
 */
void RTOS_LED_Q_SendMode(uint8_t ChIn, uint8_t ModeIn);


/** @brief  Task LED_T (non-blocked)
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return None.
 */
void RTOS_LED_Task(void *ParamsIn);

#endif //RTOS_LED_H
