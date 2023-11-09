/* @page rtos-com1.h
 *       PLC411::RTE
 *       RTOS-task COM1_T
 *       2023, atgroup09@gmail.com
 */

#ifndef RTOS_COM1_H
#define RTOS_COM1_H

#include "proto-dbg-yaplc.h"
#include "rtos.h"

#ifdef DEBUG
#include "debug-log.h"
#endif // DEBUG

#include "rtos-led.h"


#ifdef RTE_MOD_COM1

/** @def RTOS_COM1_Q values
 */
#define RTOS_COM1_Q_RX_CPLT       	(uint8_t)1  	//Rx-transfer is completed
#define RTOS_COM1_Q_TX_CPLT      	(uint8_t)2  	//Tx-transfer is completed

/** @def Timeout for DeviceBusy-exception
 */
#define RTOS_COM1_DELAY_BUSY		(TickType_t)50	//RTOS-ticks


/** @brief  COM1_T (blocked)
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return None.
 */
void RTOS_COM1_Task(void *ParamsIn);

#endif //RTE_MOD_COM1

#endif //RTOS_COM1_H
