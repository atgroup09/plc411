/* @page uart.h
 *       PLC411::RTE
 *       UART Common Handlers and Callbacks
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022, atgroup09@gmail.com
 */

#include "uart.h"


UART_HandleTypeDef  PLC_UART1;
UART_HandleTypeDef  PLC_UART2;

PLC_UART_UserFunc_t PLC_UART1_USER_FUNC = { .TxCplt = NULL, .RxCplt = NULL, .Err = NULL, .Idle = NULL };
PLC_UART_UserFunc_t PLC_UART2_USER_FUNC = { .TxCplt = NULL, .RxCplt = NULL, .Err = NULL, .Idle = NULL };


/** @brief  Start Transmit transfer.
 *  @param  HandleIn - pointer to UART-handle.
 *  @param  DataIn - pointer to Tx-buffer.
 *  @param  DataSzIn - amount of data elements to be sent.
 *  @return Result:
 *  @arg    = 0 - transfer is not started
 *  @arg    = 1 - transfer is started
 */
uint8_t PlcUart_StartTransmit(UART_HandleTypeDef *HandleIn, uint8_t *DataIn, uint16_t DataSzIn)
{
	if(DataIn && DataSzIn)
	{
		if(HandleIn == &PLC_UART1 || HandleIn == &PLC_UART2)
		{
			//DMA
			HAL_UART_Transmit_DMA(HandleIn, DataIn, DataSzIn);
			return (BIT_TRUE);
		}
	}
	return (BIT_FALSE);
}

/** @brief  Start Receive transfer.
 *  @param  HandleIn - pointer to UART-handle.
 *  @param  DataIn   - pointer to Rx-buffer.
 *  @param  DataSzIn - amount of data elements to be receive (maximum size of DataIn).
 *  @return Result:
 *  @arg    = 0 - transfer is not started
 *  @arg    = 1 - transfer is started
 */
uint8_t PlcUart_StartReceive(UART_HandleTypeDef *HandleIn, uint8_t *DataIn, uint16_t DataSzIn)
{
	if(DataIn && DataSzIn)
	{
		if(HandleIn == &PLC_UART1 || HandleIn == &PLC_UART2)
		{
			HAL_UART_Receive_DMA(HandleIn, DataIn, DataSzIn);
			__HAL_UART_ENABLE_IT(HandleIn, UART_IT_IDLE);
			return (BIT_TRUE);
		}
	}
	return (BIT_FALSE);
}

/** @brief  UART Idle Callback.
 *  @param  HandleIn - pointer to UART-handle.
 *  @return None.
 *  @note   USER Implementation.
 */
void PlcUart_IdleCallback(UART_HandleTypeDef *HandleIn)
{
	if(HandleIn)
	{
		__HAL_UART_DISABLE_IT(HandleIn, UART_IT_IDLE);
		__HAL_UART_CLEAR_IDLEFLAG(HandleIn);
		HAL_UART_AbortReceive(HandleIn);

		if(HandleIn == &PLC_UART1)
		{
			if(PLC_UART1_USER_FUNC.Idle != NULL) PLC_UART1_USER_FUNC.Idle(__HAL_DMA_GET_COUNTER(HandleIn->hdmarx));
		}
		else if(HandleIn == &PLC_UART2)
		{
			if(PLC_UART2_USER_FUNC.Idle != NULL) PLC_UART2_USER_FUNC.Idle(__HAL_DMA_GET_COUNTER(HandleIn->hdmarx));
		}
	}
}

/** @brief  UART Error Callback.
 *  @param  HandleIn - pointer to UART-handle.
 *  @return None.
 *  @note   HAL ReImplementation.
 */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *HandleIn)
{
	if(HandleIn == &PLC_UART1)
	{
		if(PLC_UART1_USER_FUNC.Err != NULL) PLC_UART1_USER_FUNC.Err();
	}
	else if(HandleIn == &PLC_UART2)
	{
		if(PLC_UART2_USER_FUNC.Err != NULL) PLC_UART2_USER_FUNC.Err();
	}
}

/** @brief  UART.DMA(Tx) Transfer completed Callback.
 *  @param  HandleIn - pointer to UART-handle.
 *  @return None.
 *  @note   HAL ReImplementation.
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *HandleIn)
{
	if(HandleIn == &PLC_UART1)
	{
		if(PLC_UART1_USER_FUNC.TxCplt != NULL) PLC_UART1_USER_FUNC.TxCplt();
	}
	else if(HandleIn == &PLC_UART2)
	{
		if(PLC_UART2_USER_FUNC.TxCplt != NULL) PLC_UART2_USER_FUNC.TxCplt();
	}
}

/** @brief  UART.DMA(Rx) Transfer completed Callback.
 *  @param  HandleIn - pointer to UART-handle.
 *  @return None.
 *  @note   HAL ReImplementation.
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *HandleIn)
{
	if(HandleIn == &PLC_UART1)
	{
		if(PLC_UART1_USER_FUNC.RxCplt != NULL) PLC_UART1_USER_FUNC.RxCplt();
	}
	else if(HandleIn == &PLC_UART2)
	{
		if(PLC_UART2_USER_FUNC.RxCplt != NULL) PLC_UART2_USER_FUNC.RxCplt();
	}
}
