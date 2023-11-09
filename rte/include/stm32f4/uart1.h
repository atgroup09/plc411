/* @page uart1.h
 *       PLC411::RTE
 *       UART1 driver
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022-2023, atgroup09@gmail.com
 */

/** @note
 * 		 UART1
 *
 *       PA09 <- DMA2.Stream7.Channel4 <- Tx
 *       PA10 -> DMA2.Stream2.Channel4 -> Rx
 *
 * 		 APP DEBUG LOG
 */

#ifndef PLC_UART1_H
#define PLC_UART1_H

#include "uart.h"


/** @def UART1 Settings
 */
#define PLC_UART1_BAUDRATE         (uint32_t)115200
#define PLC_UART1_DATABITS         (uint32_t)UART_WORDLENGTH_8B
#define PLC_UART1_STOPBITS         (uint32_t)UART_STOPBITS_1
#define PLC_UART1_PARITY           (uint32_t)UART_PARITY_NONE
#define PLC_UART1_FLOW_CTRL        (uint32_t)UART_HWCONTROL_NONE
#define PLC_UART1_MODE             (uint32_t)UART_MODE_TX_RX


/** @brief  Init UART1.
 *  @param  None.
 *  @return None.
 */
void PlcUart1_Init(void);

/** @brief  DeInit UART1.
 *  @param  None.
 *  @return None.
 */
void PlcUart1_DeInit(void);


#endif //PLC_UART1_H
