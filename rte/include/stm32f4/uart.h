/* @page uart.h
 *       PLC411::RTE
 *       UART Common Handlers and Callbacks
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022-2023, atgroup09@gmail.com
 */

#ifndef PLC_UART_H
#define PLC_UART_H

#include "config.h"
#include "error.h"

#ifdef DEBUG
#include "debug-log.h"
#endif // DEBUG


/** @typedef UART Callback user-functions
 */
typedef struct
{
    void (*TxCplt)(void);
    void (*RxCplt)(void);
    void (*Err)(void);
    void (*Idle)(uint32_t RxCntIn);

} PLC_UART_UserFunc_t;


/** @var UART Handlers
 */
extern UART_HandleTypeDef PLC_UART1;	//COM1
extern UART_HandleTypeDef PLC_UART2;	//COM2

/** @var UART Callback user-functions
 */
extern PLC_UART_UserFunc_t PLC_UART1_USER_FUNC;
extern PLC_UART_UserFunc_t PLC_UART2_USER_FUNC;


/** @brief  Start Transmit transfer.
 *  @param  HandleIn - pointer to UART-handle.
 *  @param  DataIn - pointer to Tx-buffer.
 *  @param  DataSzIn - amount of data elements to be sent.
 *  @return Result:
 *  @arg    = 0 - transfer is not started
 *  @arg    = 1 - transfer is started
 */
uint8_t PlcUart_StartTransmit(UART_HandleTypeDef *HandleIn, uint8_t *DataIn, uint16_t DataSzIn);

/** @brief  Start Receive transfer.
 *  @param  HandleIn - pointer to UART-handle.
 *  @param  DataIn   - pointer to Rx-buffer.
 *  @param  DataSzIn - amount of data elements to be receive (maximum size of DataIn).
 *  @return Result:
 *  @arg    = 0 - transfer is not started
 *  @arg    = 1 - transfer is started
 */
uint8_t PlcUart_StartReceive(UART_HandleTypeDef *HandleIn, uint8_t *DataIn, uint16_t DataSzIn);

/** @brief  UART Idle Callback.
 *  @param  HandleIn - pointer to UART-handle.
 *  @return None.
 *  @note   USER Implementation.
 */
void PlcUart_IdleCallback(UART_HandleTypeDef *HandleIn);


#endif //PLC_UART_H
