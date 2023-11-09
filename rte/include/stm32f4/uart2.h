/* @page uart2.h
 *       PLC411::RTE
 *       UART2 driver
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022, atgroup09@gmail.com
 */

/** @note
 * 		 MODBUS RTU (SLAVE)
 *
 *       UART2
 *
 *       PA02 <- DMA1.Stream6.Channel4 <- Tx
 *       PA03 -> DMA1.Stream5.Channel4 -> Rx
 */

#ifndef PLC_UART2_H
#define PLC_UART2_H

#include "uart.h"


/** @def UART2 Settings
 */
#define PLC_UART2_BAUDRATE         (uint32_t)115200
#define PLC_UART2_DATABITS         (uint32_t)UART_WORDLENGTH_8B
#define PLC_UART2_STOPBITS         (uint32_t)UART_STOPBITS_1
#define PLC_UART2_PARITY           (uint32_t)UART_PARITY_NONE
#define PLC_UART2_FLOW_CTRL        (uint32_t)UART_HWCONTROL_NONE
#define PLC_UART2_MODE             (uint32_t)UART_MODE_TX_RX


/** @brief  Init UART2.
 *  @param  None.
 *  @return None.
 */
void PlcUart2_Init(void);

/** @brief  DeInit UART2.
 *  @param  None.
 *  @return None.
 */
void PlcUart2_DeInit(void);


#endif //PLC_UART2_H
