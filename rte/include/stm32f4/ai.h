/* @page ai.h
 *       PLC411::RTE
 *       AI driver
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022, atgroup09@gmail.com
 */

/** @note
 * 		  PB0      -> ADC1.IN8  -> DMA2.STR0.CH0 -> AI.0
 * 		  PB1      -> ADC1.I98  -> DMA2.STR0.CH0 -> AI.1
 * 		  MCU_TEMP -> ADC1.IN16 -> DMA2.STR0.CH0 -> MCU_TEMP
 *
 * 		  ADC
 *        + 12 bit
 *        + 0 ... 4095 (0 ... 3.3 V)
 *
 *        ADC conversion is started by software timer (RTOS)
 *        + survey period = PLC_AI_SURVEY_PERIOD_MS (100 ms)
 *
 *        ADC-code of a channel is a average of all its measurements
 *        + measurements = PLC_AI_ADC_CHANNEL_MEASURES (25)
 */

#ifndef PLC_AI_H
#define PLC_AI_H

#include <math.h>
#include "config.h"
#include "error.h"
#include "scale.h"

#ifdef DEBUG_LOG_ADC
#include "debug-log.h"
#endif //DEBUG_LOG_ADC


/** @def Channels
 */
#define PLC_AI_00                                0
#define PLC_AI_01                                1
#define PLC_AI_MCU_TEMP                          2

/** @def Quantity of channels
 */
#define PLC_AI_SZ                                (uint8_t)(PLC_AI_MCU_TEMP+1)

/** @def AI-channel
 *       GPIO reference
 */
#define PLC_AI_00__PORT                          GPIOB
#define PLC_AI_00__PIN                           GPIO_PIN_0
#define PLC_AI_00__ADC_CH                        ADC_CHANNEL_8

#define PLC_AI_01__PORT                          GPIOB
#define PLC_AI_01__PIN                           GPIO_PIN_1
#define PLC_AI_01__ADC_CH                        ADC_CHANNEL_9

#define PLC_AI_MCU_TEMP__ADC_CH                  ADC_CHANNEL_TEMPSENSOR


/** @def Quantity of measurements per a ADC-channel
 *  @note ADC-code of a channel is a average of all its measurements
 */
#define PLC_AI_ADC_CHANNEL_MEASURES              100

/** @var Size of ADC buffer by channels
 */
#define PLC_AI_ADC_BUFF_SZ                       (uint16_t)(PLC_AI_SZ*PLC_AI_ADC_CHANNEL_MEASURES)

/** @def Digital levels (ADC-code)
 *       0 .. 12bit
 */
#define PLC_AI_DIG_MIN                           (uint16_t)0     //minumum
#define PLC_AI_DIG_MAX                           (uint16_t)4095  //maximum

/** @def Analog levels (V)
 */
#define PLC_AI_ANA_MIN                           (float)0.0      //minumum
#define PLC_AI_ANA_MAX                           (float)3.3      //maximum
#define PLC_AI_ANA_DEF                           PLC_AI_ANA_MIN  //by default

/** @def Scale factors by default
 */
// 0...4095 (ADCcode) > 0...3,3 (V)
#define PLC_AI_KA_3V3                            (float)0.000805861
#define PLC_AI_KB_3V3                            (float)0.0
// UserScale
#define PLC_AI_KA_DEF                            (float)1.0
#define PLC_AI_KB_DEF                            (float)0.0

/** @def Survey period (ms)
 */
#define PLC_AI_SURVEY_PERIOD_MS                  100


/** @typedef ADC Callback user-functions
 */
typedef struct
{
    void (*ConvCplt)(void);

} PLC_ADC_UserFunc_t;


/** @typedef AI-channel settings
 *           main type
 */
typedef struct PlcAI_t_
{
	//CONSTANTS

	//@var Channel number
	//@arg = 0..15
	uint8_t Ch;

	//SETTINGS

	//@var Channel mode
	//@arg = 0..15
	uint8_t Mode;

    //@var Scale factors
    float Ka;
    float Kb;

	//VALUES

    //@var Channel value (V)
    float Val;

    //STATUSES

    //@var Status code
    //@arg = 0..255
	uint8_t Status;

} PlcAI_t;

/** @def Modes
 */
#define PLC_AI_MODE_OFF                          (uint8_t)0  //off
#define PLC_AI_MODE_SURVEY                       (uint8_t)1  //survey + autoScale(Ka,Kb)
#define PLC_AI_MODE_SURVEY_TMP36                 (uint8_t)11 //survey + autoScale(TMP36)
#define PLC_AI_MODE_SURVEY_TMP_MCU               (uint8_t)12 //survey + autoScale(MCU_TEMP)
//by default
#define PLC_AI_MODE_DEF      	                 PLC_AI_MODE_OFF

/** @def Status codes
 */
#define PLC_AI_STATUS_OFF                        PLC_AI_MODE_OFF
#define PLC_AI_STATUS_SURVEY                     PLC_AI_MODE_SURVEY
#define PLC_AI_STATUS_SURVEY_TMP36               PLC_AI_MODE_SURVEY_TMP36
#define PLC_AI_STATUS_SURVEY_TMP_MCU             PLC_AI_MODE_SURVEY_TMP_MCU


/** @def Queue item
 *       main structure
 */
typedef struct PlcAI_Q_t_
{
    //@var Channel number
    uint8_t Ch;
    //@var Item ID
    uint8_t ID;
    //@var Value
    float Val;

} PlcAI_Q_t;

/** @def Queue IDs
 */
#define PLC_AI_Q_ID_NONE       					 (uint8_t)0
#define PLC_AI_Q_ID_MODE       					 (uint8_t)1   //mode
#define PLC_AI_Q_ID_VAL       					 (uint8_t)2   //value
#define PLC_AI_Q_ID_KA        					 (uint8_t)3   //Ka
#define PLC_AI_Q_ID_KB        					 (uint8_t)4   //Kb
#define PLC_AI_Q_ID_STATUS     					 (uint8_t)5   //status


/** @var ADC Handler
 */
extern ADC_HandleTypeDef PLC_ADC1;

/** @var ADC Callback user-functions
 */
extern PLC_ADC_UserFunc_t PLC_ADC1_USER_FUNC;


/** @brief  Init AI.
 *  @param  none.
 *  @return none.
 */
void PlcAI_Init(void);

/** @brief  DeInit DeInit.
 *  @param  None.
 *  @return None.
 */
void PlcAI_DeInit(void);

/** @brief  Start AI.
 *  @param  None.
 *  @return None
 */
void PlcAI_Start(void);

/** @brief  Stop AI.
 *  @param  None.
 *  @return None
 */
void PlcAI_Stop(void);


/** @brief  Get ADC-code of AI-channel.
 *  @param  ChIn - channel number:
 *  @arg    = PLC_AI_00
 *  @arg    = PLC_AI_01
 *  @arg    = PLC_AI_MCU_TEMP
 *  @return Digital level:
 *  @arg    = PLC_AI_DIG_MIN ... PLC_AI_DIG_MAX
 *  @note   Current ADC-code
 */
uint16_t PlcAI_GetCode(uint8_t ChIn);

/** @brief  Get analog value of AI-channel.
 *  @param  ChIn - channel number:
 *  @arg    = PLC_AI_00
 *  @arg    = PLC_AI_01
 *  @arg    = PLC_AI_MCU_TEMP
 *  @return Analog value (V):
 *  @arg    = PLC_AI_ANA_MIN ... PLC_AI_ANA_MAX
 */
float PlcAI_GetAna(uint8_t ChIn);


#endif //PLC_AI_H
