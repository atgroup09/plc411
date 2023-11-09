/* @page tim5.c
 *       PLC411::RTE
 *       TIM5 driver
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022-2023, atgroup09@gmail.com
 */

#include <tim5.h>


#ifdef RTE_MOD_DO

#ifdef PLC_TIM5_DMA

/** @var ADC1.DMA Handler
 */
static DMA_HandleTypeDef PLC_TIM5_CH2_DMA;

/** @var DMA statuses
 */
static uint8_t PLC_TIM5_CH2_DMA_STATUS = BIT_FALSE;

#endif //PLC_TIM5_DMA



/** @brief  Init. TIM5
 *  @param  None.
 *  @return None.
 */
void PlcTim5_Init(void)
{
	TIM_ClockConfigTypeDef         TimClockCfg;
	TIM_MasterConfigTypeDef        TimMasterCfg;
	TIM_OC_InitTypeDef             TimOcCfg;

	//Enable clock
	__HAL_RCC_TIM5_CLK_ENABLE();

	//Counter settings
	PLC_TIM5.Instance				= TIM5;
	PLC_TIM5.Init.Prescaler         = PLC_TIM5_PRESCALER;
	PLC_TIM5.Init.CounterMode       = TIM_COUNTERMODE_UP;
	PLC_TIM5.Init.Period            = PLC_TIM5_PERIOD__1HZ;
	PLC_TIM5.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
	PLC_TIM5.Init.RepetitionCounter = 0;
	PLC_TIM5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if(HAL_TIM_Base_Init(&PLC_TIM5) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	//Clock source
	TimClockCfg.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if(HAL_TIM_ConfigClockSource(&PLC_TIM5, &TimClockCfg) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	//PWM init.
	if(HAL_TIM_PWM_Init(&PLC_TIM5) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	//Trigger settings
	TimMasterCfg.MasterOutputTrigger = TIM_TRGO_RESET;
	TimMasterCfg.MasterSlaveMode     = TIM_MASTERSLAVEMODE_DISABLE;
	if(HAL_TIMEx_MasterConfigSynchronization(&PLC_TIM5, &TimMasterCfg) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	//Channel settings
	TimOcCfg.OCMode       = TIM_OCMODE_PWM1;
	TimOcCfg.Pulse        = 0;
	TimOcCfg.OCPolarity   = TIM_OCPOLARITY_HIGH;
	TimOcCfg.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
	TimOcCfg.OCFastMode   = TIM_OCFAST_DISABLE;
	TimOcCfg.OCIdleState  = TIM_OCIDLESTATE_RESET;
	TimOcCfg.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	if(HAL_TIM_PWM_ConfigChannel(&PLC_TIM5, &TimOcCfg, PLC_TIM5_DO_CH) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

#ifdef PLC_TIM5_DMA

	//TIM2.CH1.DMA1 Init.
	PLC_TIM2_CH1_DMA.Instance                 = DMA1_Stream5;
	PLC_TIM2_CH1_DMA.Init.Channel   		  = DMA_CHANNEL_3;
	PLC_TIM2_CH1_DMA.Init.Direction 		  = DMA_MEMORY_TO_PERIPH;
	PLC_TIM2_CH1_DMA.Init.PeriphInc 		  = DMA_PINC_DISABLE;
	PLC_TIM2_CH1_DMA.Init.MemInc 			  = DMA_MINC_ENABLE;
	PLC_TIM2_CH1_DMA.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
	PLC_TIM2_CH1_DMA.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
	PLC_TIM2_CH1_DMA.Init.Mode				  = DMA_NORMAL;
	PLC_TIM2_CH1_DMA.Init.Priority			  = PLC_DMA_PRIO_DO;
	PLC_TIM2_CH1_DMA.Init.FIFOMode			  = DMA_FIFOMODE_DISABLE;
	PLC_TIM2_CH1_DMA.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	PLC_TIM2_CH1_DMA.Init.MemBurst            = DMA_MBURST_INC4;
	PLC_TIM2_CH1_DMA.Init.PeriphBurst         = DMA_PBURST_INC4;
    if(HAL_DMA_Init(&PLC_TIM2_CH1_DMA) != HAL_OK)
    {
    	_Error_Handler(__FILE__, __LINE__);
    }
    // Associate the initialized DMA handle to the the ADC handle
    __HAL_LINKDMA(&PLC_TIM2, hdma[TIM_DMA_ID_CC1], PLC_TIM2_CH1_DMA);

    //IRQ Init.
    // DMA1
    HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, PLC_NVIC_PPRIO_DO_DMA, PLC_NVIC_SPRIO_DO_DMA);
    HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
    HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, PLC_NVIC_PPRIO_DO_DMA, PLC_NVIC_SPRIO_DO_DMA);
    HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);


    HAL_TIM_PWM_Start_DMA(htim, Channel, pData, Length);
    HAL_TIM_DMABurst_WriteStart(htim, BurstBaseAddress, BurstRequestSrc, BurstBuffer, BurstLength)

#endif //PLC_TIM5_DMA
}

/** @brief  DeInit TIM5.
 *  @param  None.
 *  @return None.
 */
void PlcTim5_DeInit(void)
{
	PlcTim_StopChannel(&PLC_TIM5, PLC_TIM5_DO_CH);

#ifdef PLC_TIM2_DMA
    HAL_DMA_DeInit(PLC_TIM2->hdma[TIM_DMA_ID_CC1]);
#endif //PLC_TIM2_DMA

	__HAL_RCC_TIM5_CLK_DISABLE();
}

#endif //RTE_MOD_DO
