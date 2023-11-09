/* @page rtos-com2.h
 *       PLC411::RTE
 *       RTOS-task T_COM2
 *       2020-2022, atgroup09@gmail.com
 */

#ifndef RTOS_COM2_H
#define RTOS_COM2_H

#include "uart2.h"
#include "proto-mbrtu.h"
#include "rtos.h"

#ifdef DEBUG
#include "debug-log.h"
#endif // DEBUG

#include "rtos-led.h"


#ifdef RTE_MOD_COM2

/** @def RTOS_COM2_Q values
 */
#define RTOS_COM2_Q_RX_CPLT       	(uint8_t)1  	//Rx-transfer is completed
#define RTOS_COM2_Q_TX_CPLT      	(uint8_t)2  	//Tx-transfer is completed


/** @def Timeout for DeviceBusy-exception
 */
#define RTOS_COM2_DELAY_BUSY		(TickType_t)50	//RTOS-ticks


/** @brief  COM2_T (blocked)
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return None.
 */
void RTOS_COM2_Task(void *ParamsIn);

#endif //RTE_MOD_COM2

#endif //RTOS_COM2_H
