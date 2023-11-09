/* @page uart2.c
 *       PLC411::RTE
 *       UART2 driver
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022, atgroup09@gmail.com
 */

#include "uart2.h"


/** @var UART2.DMA Handlers
 */
static DMA_HandleTypeDef  PLC_UART2_TX_DMA;
static DMA_HandleTypeDef  PLC_UART2_RX_DMA;


/** @brief  Init UART2.
 *  @param  None.
 *  @return None.
 */
void PlcUart2_Init(void)
{
	GPIO_InitTypeDef GpioDef;

	//Enable clock
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_DMA1_CLK_ENABLE();

	//GPIO Init.
	GpioDef.Pin       = (GPIO_PIN_2|GPIO_PIN_3);
	GpioDef.Mode      = GPIO_MODE_AF_PP;
	GpioDef.Pull      = GPIO_NOPULL;
	GpioDef.Speed     = GPIO_SPEED_FAST;
	GpioDef.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &GpioDef);

	//HAL Init.
	PLC_UART2.Instance          = USART2;
	PLC_UART2.Init.BaudRate     = PLC_UART2_BAUDRATE;
	PLC_UART2.Init.WordLength   = PLC_UART2_DATABITS;
	PLC_UART2.Init.StopBits     = PLC_UART2_STOPBITS;
	PLC_UART2.Init.Parity       = PLC_UART2_PARITY;
	PLC_UART2.Init.Mode         = PLC_UART2_MODE;
	PLC_UART2.Init.HwFlowCtl    = PLC_UART2_FLOW_CTRL;
	PLC_UART2.Init.OverSampling = UART_OVERSAMPLING_16;
	if(HAL_UART_Init(&PLC_UART2) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	//DMA(Tx) Init.
	PLC_UART2_TX_DMA.Instance                 = DMA1_Stream6;
	PLC_UART2_TX_DMA.Init.Channel             = DMA_CHANNEL_4;
	PLC_UART2_TX_DMA.Init.Direction           = DMA_MEMORY_TO_PERIPH;
	PLC_UART2_TX_DMA.Init.PeriphInc           = DMA_PINC_DISABLE;
	PLC_UART2_TX_DMA.Init.MemInc              = DMA_MINC_ENABLE;
	PLC_UART2_TX_DMA.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	PLC_UART2_TX_DMA.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	PLC_UART2_TX_DMA.Init.Mode                = DMA_NORMAL;
	PLC_UART2_TX_DMA.Init.Priority            = PLC_DMA_PRIO_COM2_TX;
	PLC_UART2_TX_DMA.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
	PLC_UART2_TX_DMA.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	PLC_UART2_TX_DMA.Init.MemBurst            = DMA_MBURST_INC4;
	PLC_UART2_TX_DMA.Init.PeriphBurst         = DMA_PBURST_INC4;
	HAL_DMA_Init(&PLC_UART2_TX_DMA);
	// Associate the initialized DMA handle to the the UART handle
	__HAL_LINKDMA(&PLC_UART2, hdmatx, PLC_UART2_TX_DMA);

	//DMA(Rx) Init.
	PLC_UART2_RX_DMA.Instance                 = DMA1_Stream5;
	PLC_UART2_RX_DMA.Init.Channel             = DMA_CHANNEL_4;
	PLC_UART2_RX_DMA.Init.Direction           = DMA_PERIPH_TO_MEMORY;
	PLC_UART2_RX_DMA.Init.PeriphInc           = DMA_PINC_DISABLE;
	PLC_UART2_RX_DMA.Init.MemInc              = DMA_MINC_ENABLE;
	PLC_UART2_RX_DMA.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	PLC_UART2_RX_DMA.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	PLC_UART2_RX_DMA.Init.Mode                = DMA_NORMAL;
	PLC_UART2_RX_DMA.Init.Priority            = PLC_DMA_PRIO_COM2_RX;
	PLC_UART2_RX_DMA.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
	PLC_UART2_RX_DMA.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	PLC_UART2_RX_DMA.Init.MemBurst            = DMA_MBURST_INC4;
	PLC_UART2_RX_DMA.Init.PeriphBurst         = DMA_PBURST_INC4;
	HAL_DMA_Init(&PLC_UART2_RX_DMA);
	// Associate the initialized DMA handle to the the UART handle
	__HAL_LINKDMA(&PLC_UART2, hdmarx, PLC_UART2_RX_DMA);

	//IRQ Init
	// .DMA.UART.Tx
	HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, PLC_NVIC_PPRIO_COM2_DMA_TX, PLC_NVIC_SPRIO_COM2_DMA_TX);
	HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);
	// .DMA.UART.Rx
	HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, PLC_NVIC_PPRIO_COM2_DMA_RX, PLC_NVIC_SPRIO_COM2_DMA_RX);
	HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
	// .UART
	HAL_NVIC_SetPriority(USART2_IRQn, PLC_NVIC_PPRIO_COM2_UART, PLC_NVIC_SPRIO_COM2_UART);
	HAL_NVIC_EnableIRQ(USART2_IRQn);
}

/** @brief  DeInit UART2.
 *  @param  None.
 *  @return None.
 */
void PlcUart2_DeInit(void)
{
	//Disable IRQ
	HAL_NVIC_DisableIRQ(DMA2_Stream5_IRQn);
	HAL_NVIC_DisableIRQ(DMA2_Stream6_IRQn);
	__HAL_UART_DISABLE_IT(&PLC_UART2, UART_IT_IDLE);

	//Disable clock
	__HAL_RCC_USART2_FORCE_RESET();
	__HAL_RCC_USART2_RELEASE_RESET();
	__HAL_RCC_USART2_CLK_DISABLE();

	//GPIO DeInit
	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

	//DMA DeInit
	HAL_DMA_DeInit(&PLC_UART2_TX_DMA);
	HAL_DMA_DeInit(&PLC_UART2_RX_DMA);
}


/** @brief  UART2 IRQ Handler.
 *  @param  None.
 *  @return None.
 */
void USART2_IRQHandler(void)
{
	//IDLE
	if(__HAL_UART_GET_FLAG(&PLC_UART2, UART_FLAG_IDLE) != RESET) PlcUart_IdleCallback(&PLC_UART2);
	HAL_UART_IRQHandler(&PLC_UART2);
	//callback functions are released in uart.c
}

/** @brief  DMA1.Stream5 IRQ Handler.
 *  @param  None.
 *  @return None.
 */
void DMA1_Stream5_IRQHandler(void)
{
	HAL_DMA_IRQHandler(PLC_UART2.hdmarx);
	//callback functions are released in uart.c
}

/** @brief  DMA1.Stream6 IRQ Handler.
 *  @param  None.
 *  @return None.
 */
void DMA1_Stream6_IRQHandler(void)
{
	HAL_DMA_IRQHandler(PLC_UART2.hdmatx);
	//callback functions are released in uart.c
}
