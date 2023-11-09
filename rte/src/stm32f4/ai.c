/* @page ai.c
 *       PLC411::RTE
 *       AI driver
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022, atgroup09@gmail.com
 */

#include "ai.h"


/** @var ADC Handler
 */
ADC_HandleTypeDef PLC_ADC1;

/** @var ADC Callback user-functions
 */
PLC_ADC_UserFunc_t PLC_ADC1_USER_FUNC;


/** @var ADC1.DMA Handler
 */
static DMA_HandleTypeDef PLC_ADC1_DMA;

/** @var DMA statuses
 */
static uint8_t PLC_AI_DMA_STATUS = BIT_FALSE;


/** @var ADC buffer by channels
 */
static volatile uint16_t PLC_AI_ADC_BUFF[PLC_AI_ADC_BUFF_SZ];


/** @brief  AI Init.
 *  @param  none.
 *  @return none.
 */
void PlcAI_Init(void)
{
	GPIO_InitTypeDef GpioDef;
	ADC_ChannelConfTypeDef AdcChannelCfg;

	//Enable clock
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_ADC1_CLK_ENABLE();
	__HAL_RCC_DMA2_CLK_ENABLE();

	//GPIO Init.
	GpioDef.Pin  = (PLC_AI_00__PIN|PLC_AI_01__PIN);
	GpioDef.Mode = GPIO_MODE_ANALOG;
	GpioDef.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GpioDef);

	//ADC settings
	PLC_ADC1.Instance                     = ADC1;
	PLC_ADC1.Init.ClockPrescaler          = ADC_CLOCK_SYNC_PCLK_DIV6;
	PLC_ADC1.Init.Resolution              = ADC_RESOLUTION_12B;
	PLC_ADC1.Init.DataAlign               = ADC_DATAALIGN_RIGHT;
	PLC_ADC1.Init.ScanConvMode            = ENABLE;
	PLC_ADC1.Init.ContinuousConvMode      = ENABLE;
	PLC_ADC1.Init.DiscontinuousConvMode   = DISABLE;
	PLC_ADC1.Init.DMAContinuousRequests   = ENABLE;
	PLC_ADC1.Init.EOCSelection			  = ADC_EOC_SINGLE_CONV;
	PLC_ADC1.Init.ExternalTrigConv        = ADC_SOFTWARE_START;
	PLC_ADC1.Init.ExternalTrigConvEdge    = ADC_EXTERNALTRIGCONVEDGE_RISING;
	PLC_ADC1.Init.NbrOfConversion         = PLC_AI_SZ;
	if(HAL_ADC_Init(&PLC_ADC1) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	//ADC channel settings
	AdcChannelCfg.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	// CH0
	AdcChannelCfg.Channel = PLC_AI_00__ADC_CH;
	AdcChannelCfg.Rank    = (PLC_AI_00+1);
	if(HAL_ADC_ConfigChannel(&PLC_ADC1, &AdcChannelCfg) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}
	// CH1
	AdcChannelCfg.Channel = PLC_AI_01__ADC_CH;
	AdcChannelCfg.Rank    = (PLC_AI_01+1);
	if(HAL_ADC_ConfigChannel(&PLC_ADC1, &AdcChannelCfg) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}
	// MCU_TEMP
	AdcChannelCfg.Channel = PLC_AI_MCU_TEMP__ADC_CH;
	AdcChannelCfg.Rank    = (PLC_AI_MCU_TEMP+1);
	if(HAL_ADC_ConfigChannel(&PLC_ADC1, &AdcChannelCfg) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	//ADC1.DMA2 Init.
	PLC_ADC1_DMA.Instance                 = DMA2_Stream0;
	PLC_ADC1_DMA.Init.Channel   		  = DMA_CHANNEL_0;
	PLC_ADC1_DMA.Init.Direction 		  = DMA_PERIPH_TO_MEMORY;
	PLC_ADC1_DMA.Init.PeriphInc 		  = DMA_PINC_DISABLE;
	PLC_ADC1_DMA.Init.MemInc 			  = DMA_MINC_ENABLE;
	PLC_ADC1_DMA.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
	PLC_ADC1_DMA.Init.MemDataAlignment    = DMA_MDATAALIGN_HALFWORD;
	PLC_ADC1_DMA.Init.Mode				  = DMA_NORMAL;
	PLC_ADC1_DMA.Init.Priority			  = PLC_DMA_PRIO_AI;
	PLC_ADC1_DMA.Init.FIFOMode			  = DMA_FIFOMODE_DISABLE;
	PLC_ADC1_DMA.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	PLC_ADC1_DMA.Init.MemBurst            = DMA_MBURST_INC4;
	PLC_ADC1_DMA.Init.PeriphBurst         = DMA_PBURST_INC4;
    if(HAL_DMA_Init(&PLC_ADC1_DMA) != HAL_OK)
    {
    	_Error_Handler(__FILE__, __LINE__);
    }
    // Associate the initialized DMA handle to the the ADC handle
    __HAL_LINKDMA(&PLC_ADC1, DMA_Handle, PLC_ADC1_DMA);

    //IRQ Init.
    // DMA2
    HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, PLC_NVIC_PPRIO_AI_DMA, PLC_NVIC_SPRIO_AI_DMA);
    HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
}

/** @brief  AI DeInit.
 *  @param  None.
 *  @return None.
 */
void PlcAI_DeInit(void)
{
	//Disable IRQ
	HAL_NVIC_DisableIRQ(ADC_IRQn);

	//Disable clock
	__HAL_RCC_ADC1_CLK_DISABLE();

	//GPIO DeInit
	HAL_GPIO_DeInit(GPIOA, PLC_AI_00__PIN|PLC_AI_01__PIN);

	//DMA DeInit
	HAL_DMA_DeInit(&PLC_ADC1_DMA);
}

/** @brief  Start AI.
 *  @param  None.
 *  @return None
 */
void PlcAI_Start(void)
{
	if(!PLC_AI_DMA_STATUS)
	{
#ifdef DEBUG_LOG_ADC
        DebugLog("PlcAI_Start\n");
#endif // DEBUG_LOG_ADC

        //Restarting the DMA automatically starts the ADC
        //HAL_ADC_Start(&PLC_ADC1);
        if(HAL_ADC_Start_DMA(&PLC_ADC1, (uint32_t*)PLC_AI_ADC_BUFF, PLC_AI_ADC_BUFF_SZ) == HAL_OK)
        {
        	PLC_AI_DMA_STATUS = BIT_TRUE;
        }
	}
}

/** @brief  Stop AI.
 *  @param  None.
 *  @return None
 */
void PlcAI_Stop(void)
{
	HAL_ADC_Stop(&PLC_ADC1);
	PLC_AI_DMA_STATUS = BIT_FALSE;
	//DMA works in normal mode, so its will stop automatically when the data is read
	//HAL_ADC_Stop_DMA(&PLC_ADC1);
}


/** @brief  ADC IRQ Handler.
 *  @param  None.
 *  @return None.
 */
void ADC_IRQHandler(void)
{
	HAL_ADC_IRQHandler(&PLC_ADC1);
}

/** @brief  DMA2.Stream0 IRQ Handler.
 *  @param  None.
 *  @return None.
 */
void DMA2_Stream0_IRQHandler(void)
{
	HAL_DMA_IRQHandler(PLC_ADC1.DMA_Handle);
}


/** @brief  DMA2.ADC(Tc) Transfer completed Callback.
 *  @param  HandleIn - pointer to ADC-handle.
 *  @return None.
 *  @note   HAL ReImplementation.
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *HandleIn)
{
	if(HandleIn == &PLC_ADC1)
	{
		if(PLC_ADC1_USER_FUNC.ConvCplt != NULL) PLC_ADC1_USER_FUNC.ConvCplt();
	}
}


/** @brief  Get ADC-code of AI-channel.
 *  @param  ChIn - channel number.
 *  @return Digital level:
 *  @arg    = PLC_AI_DIG_MIN ... PLC_AI_DIG_MAX
 *  @note   Current ADC-code
 */
uint16_t PlcAI_GetCode(uint8_t ChIn)
{
    uint16_t Res = PLC_AI_DIG_MIN;

    if(ChIn < PLC_AI_SZ)
    {
#if (PLC_AI_ADC_CHANNEL_MEASURES > 1)
        //summ of all measurements of the channel
        uint32_t Sum = 0;
        uint16_t iBuff;

        for(uint16_t i=0; i<PLC_AI_ADC_CHANNEL_MEASURES; i++)
        {
        	iBuff = ((PLC_AI_SZ*i)+ChIn);
            Sum += PLC_AI_ADC_BUFF[iBuff];
        }
        //average value
        Res = (uint16_t)(Sum/PLC_AI_ADC_CHANNEL_MEASURES);
#else
        //single value
        Res = PLC_AI_ADC_BUFF[ChIn];
#endif //PLC_AI_ADC_CHANNEL_MEASURES
    }

    return ((Res <= PLC_AI_DIG_MAX) ? Res : PLC_AI_DIG_MAX);
}

/** @brief  Get analog value of AI-channel.
 *  @param  ChIn - channel number.
 *  @return Analog value (V):
 *  @arg    = PLC_AI_ANA_MIN ... PLC_AI_ANA_MAX
 */
float PlcAI_GetAna(uint8_t ChIn)
{
    float Res = PLC_AI_ANA_DEF;

    if(ChIn < PLC_AI_SZ)
    {
        uint16_t Code = PlcAI_GetCode(ChIn);
        Res = ScaleA((float)Code, PLC_AI_KA_3V3, PLC_AI_KB_3V3);

#ifdef DEBUG_LOG_ADC
        DebugLog("ADC: Ch=%d Code=%d Ana=%f\n", ChIn, Code, Res);
#endif // DEBUG_LOG_ADC
    }

    return (Res);
}
