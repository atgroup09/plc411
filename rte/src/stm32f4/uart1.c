/* @page uart1.c
 *       PLC411::RTE
 *       UART1 driver
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022, atgroup09@gmail.com
 */

#include "uart1.h"


/** @var UART1.DMA Handlers
 */
static DMA_HandleTypeDef  PLC_UART1_TX_DMA;
static DMA_HandleTypeDef  PLC_UART1_RX_DMA;


/** @brief  UART1 Init.
 *  @param  None.
 *  @return None.
 */
void PlcUart1_Init(void)
{
	GPIO_InitTypeDef GpioDef;

	//Enable clock
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_USART1_CLK_ENABLE();
	__HAL_RCC_DMA2_CLK_ENABLE();

	//GPIO Init.
	GpioDef.Pin       = (GPIO_PIN_9|GPIO_PIN_10);
	GpioDef.Mode      = GPIO_MODE_AF_PP;
	GpioDef.Pull      = GPIO_NOPULL;
	GpioDef.Speed     = GPIO_SPEED_FAST;
	GpioDef.Alternate = GPIO_AF7_USART1;
	HAL_GPIO_Init(GPIOA, &GpioDef);

	//HAL Init.
	PLC_UART1.Instance          = USART1;
	PLC_UART1.Init.BaudRate     = PLC_UART1_BAUDRATE;
	PLC_UART1.Init.WordLength   = PLC_UART1_DATABITS;
	PLC_UART1.Init.StopBits     = PLC_UART1_STOPBITS;
	PLC_UART1.Init.Parity       = PLC_UART1_PARITY;
	PLC_UART1.Init.Mode         = PLC_UART1_MODE;
	PLC_UART1.Init.HwFlowCtl    = PLC_UART1_FLOW_CTRL;
	PLC_UART1.Init.OverSampling = UART_OVERSAMPLING_16;
	if(HAL_UART_Init(&PLC_UART1) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	//DMA(Tx) Init.
	PLC_UART1_TX_DMA.Instance                 = DMA2_Stream7;
	PLC_UART1_TX_DMA.Init.Channel             = DMA_CHANNEL_4;
	PLC_UART1_TX_DMA.Init.Direction           = DMA_MEMORY_TO_PERIPH;
	PLC_UART1_TX_DMA.Init.PeriphInc           = DMA_PINC_DISABLE;
	PLC_UART1_TX_DMA.Init.MemInc              = DMA_MINC_ENABLE;
	PLC_UART1_TX_DMA.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	PLC_UART1_TX_DMA.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	PLC_UART1_TX_DMA.Init.Mode                = DMA_NORMAL;
	PLC_UART1_TX_DMA.Init.Priority            = PLC_DMA_PRIO_COM1_TX;
	PLC_UART1_TX_DMA.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
	PLC_UART1_TX_DMA.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	PLC_UART1_TX_DMA.Init.MemBurst            = DMA_MBURST_INC4;
	PLC_UART1_TX_DMA.Init.PeriphBurst         = DMA_PBURST_INC4;
	HAL_DMA_Init(&PLC_UART1_TX_DMA);
	// Associate the initialized DMA handle to the the UART handle
	__HAL_LINKDMA(&PLC_UART1, hdmatx, PLC_UART1_TX_DMA);

	//DMA(Rx) Init.
	PLC_UART1_RX_DMA.Instance                 = DMA2_Stream2;
	PLC_UART1_RX_DMA.Init.Channel             = DMA_CHANNEL_4;
	PLC_UART1_RX_DMA.Init.Direction           = DMA_PERIPH_TO_MEMORY;
	PLC_UART1_RX_DMA.Init.PeriphInc           = DMA_PINC_DISABLE;
	PLC_UART1_RX_DMA.Init.MemInc              = DMA_MINC_ENABLE;
	PLC_UART1_RX_DMA.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	PLC_UART1_RX_DMA.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	PLC_UART1_RX_DMA.Init.Mode                = DMA_NORMAL;
	PLC_UART1_RX_DMA.Init.Priority            = PLC_DMA_PRIO_COM1_RX;
	PLC_UART1_RX_DMA.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
	PLC_UART1_RX_DMA.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	PLC_UART1_RX_DMA.Init.MemBurst            = DMA_MBURST_INC4;
	PLC_UART1_RX_DMA.Init.PeriphBurst         = DMA_PBURST_INC4;
	HAL_DMA_Init(&PLC_UART1_RX_DMA);
	// Associate the initialized DMA handle to the the UART handle
	__HAL_LINKDMA(&PLC_UART1, hdmarx, PLC_UART1_RX_DMA);

	//IRQ Init.
	// .DMA.UART.Tx
	HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, PLC_NVIC_PPRIO_COM1_DMA_TX, PLC_NVIC_SPRIO_COM1_DMA_TX);
	HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);
	// .DMA.UART.Rx
	HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, PLC_NVIC_PPRIO_COM1_DMA_RX, PLC_NVIC_SPRIO_COM1_DMA_RX);
	HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
	// .UART
	HAL_NVIC_SetPriority(USART1_IRQn, PLC_NVIC_PPRIO_COM1_UART, PLC_NVIC_SPRIO_COM1_UART);
	HAL_NVIC_EnableIRQ(USART1_IRQn);
}

/** @brief  UART1 DeInit.
 *  @param  None.
 *  @return None.
 */
void PlcUart1_DeInit(void)
{
	//Disable IRQ
	HAL_NVIC_DisableIRQ(DMA2_Stream7_IRQn);
	HAL_NVIC_DisableIRQ(DMA2_Stream2_IRQn);
	HAL_NVIC_DisableIRQ(USART1_IRQn);

	//Disable clock
	__HAL_RCC_USART1_FORCE_RESET();
	__HAL_RCC_USART1_RELEASE_RESET();
	__HAL_RCC_USART1_CLK_DISABLE();

	//GPIO DeInit
	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

	//DMA DeInit
	HAL_DMA_DeInit(&PLC_UART1_TX_DMA);
	HAL_DMA_DeInit(&PLC_UART1_RX_DMA);
}


/** @brief  UART1 IRQ Handler.
 *  @param  None.
 *  @return None.
 */
void USART1_IRQHandler(void)
{
	if(__HAL_UART_GET_FLAG(&PLC_UART1, UART_FLAG_IDLE) != RESET) PlcUart_IdleCallback(&PLC_UART1);
	HAL_UART_IRQHandler(&PLC_UART1);
	//callback functions are released in uart.c
}

/** @brief  DMA2.Stream2 IRQ Handler.
 *  @param  None.
 *  @return None.
 */
void DMA2_Stream2_IRQHandler(void)
{
	HAL_DMA_IRQHandler(PLC_UART1.hdmarx);
	//callback functions are released in uart.c
}

/** @brief  DMA2.Stream7 IRQ Handler.
 *  @param  None.
 *  @return None.
 */
void DMA2_Stream7_IRQHandler(void)
{
	HAL_DMA_IRQHandler(PLC_UART1.hdmatx);
	//callback functions are released in uart.c
}
