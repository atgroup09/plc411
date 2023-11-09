/* @page do.h
 *       PLC411::RTE
 *       DO driver
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022-2023, atgroup09@gmail.com
 */

/** @note
 *        PA0 <- TIM2.CH1.PWM <- DO.0
 *        PA1 <- TIM5.CH2.PWM <- DO.1
 *
 *        TIMx.CHx.PWM is using to control GPIO:
 *
 *        - mode 0 (Off):
 *          TIMx.T=PLC_DO_PWM_T_CODE__MAX, TIMx.D=PLC_DO_PWM_T__MIN -> 0 (FALSE) -> DOx
 *
 *        - mode 1,2 (Norm, Fast):
 *          TIMx.T=PLC_DO_PWM_T_CODE__MAX, TIMx.D=PLC_DO_PWM_T__MIN -> 0 (FALSE) -> DOx
 *          or
 *          TIMx.T=PLC_DO_PWM_T_CODE__MAX, TIMx.D=PLC_DO_PWM_T__MAX -> 1 (TRUE)  -> DOx
 */

#ifndef PLC_DO_H
#define PLC_DO_H

#include "config.h"
#include "error.h"

#include "tim2.h"
#include "tim5.h"

#include "scale.h"


/** @def Channel number
 */
#define PLC_DO_00                                0
#define PLC_DO_01                                1

/** @def Quantity of channels
 */
#define PLC_DO_SZ                                (uint8_t)(PLC_DO_01+1)

/** @def GPIO references
 */
#define PLC_DO_00__PORT                          GPIOA
#define PLC_DO_00__PIN                           GPIO_PIN_0
#define PLC_DO_00__PIN_MODE     				 PLC_GPIO_DO_PP

#define PLC_DO_01__PORT                          GPIOA
#define PLC_DO_01__PIN                           GPIO_PIN_1
#define PLC_DO_01__PIN_MODE     				 PLC_GPIO_DO_PP


/** @def PWM Period
 */
// limites (ms)
#define PLC_DO_PWM_T__MIN                        (float)0.01        //100.0   kHz
#define PLC_DO_PWM_T__1HZ                        (float)1000.0      //1.0     Hz
#define PLC_DO_PWM_T__MAX                        (float)1000000.0   //0.001   Hz

/** @def PWM Pulse (fill factor)
 */
// limites (%)
#define PLC_DO_PWM_D__MIN              		     (float)0.0
#define PLC_DO_PWM_D__50               		     (float)50.0
#define PLC_DO_PWM_D__MAX              		     (float)100.0


/** @typedef DO-channel settings
 *           packed data
 */
typedef struct PlcDO_Pack_t_
{
    //@var Command to Allow PWM
    //@arg = 0 - no
    //@arg = 1 - yes
    uint8_t PwmAllow:1;

    //@var Command to Allow Safety value
    //@arg = 0 - no
    //@arg = 1 - yes
    uint8_t SafeAllow:1;

    //@var Postponed normal value is ready
    //@note it's normal value from Beremiz
    //@arg = 0 - no
    //@arg = 1 - yes
    uint8_t PostponReady:1;

} PlcDO_Pack_t;

/** @typedef DO channel
 */
typedef struct PlcDO_t_
{
	//CONSTANTS

	//@var Channel number
	//@arg = 0..15
	uint8_t Ch;

	//SETTINGS

    //@var Channel mode
   	//@arg = 0..15
   	uint8_t Mode;

    //@var PWM period (ms)
    float PwmT;

    //@var Pack
    PlcDO_Pack_t Pack;

	//VALUES

    //@var Normal value
    uint8_t NormVal;

    //@var Fast value
    uint8_t FastVal;

    //@var PWM fill factor (%)
    float PwmD;

    //@var Safety value
    uint8_t SafeVal;

    //@var Postponed normal value
    //@note it's normal value from Beremiz
    uint8_t PostponedVal;

	//STATUSES

	//@var Status code
	//@arg = 0..255
	uint8_t Status;

	//GPIO

	//@var PORT
	GPIO_TypeDef *Port;

	//@var PIN
	uint16_t Pin;

	//@var TIM Handler
	TIM_HandleTypeDef *Tim;

	//@var TIM Channel
	uint32_t TimCh;

	//OTHER

	//@var PWM period (32-bit register value, ARR)
	//@note must be recalculated after change PwmT
	uint32_t Arr;

	//@var PWM pulse (32-bit register value, CCR)
	//@note must be recalculated after change PwmD
	uint32_t Ccr;

	//@var  Scale factors to convert PwmD (%) into 32-bit register value (CCR)
	//@note must be recalculated after change PwmT
	float Ka;
	float Kb;

} PlcDO_t;


/** @def Modes
 */
#define PLC_DO_MODE_OFF                          (uint8_t)0  //off
#define PLC_DO_MODE_NORM                         (uint8_t)1  //normal
#define PLC_DO_MODE_FAST                         (uint8_t)2  //fast
#define PLC_DO_MODE_PWM                          (uint8_t)3  //PWM

/** @def Settings by default
 */
#define PLC_DO_MODE_DEF      	                 PLC_DI_MODE_OFF
#define PLC_DO_PWM_T_DEF                         PLC_DO_PWM_T__1HZ
#define PLC_DO_PWM_D_DEF    		             PLC_DO_PWM_D__MIN
#define PLC_DO_PWM_ALLOW_DEF           			 BIT_FALSE
#define PLC_DO_NORM_VAL_DEF                 	 BIT_FALSE
#define PLC_DO_FAST_VAL_DEF                 	 BIT_FALSE
#define PLC_DO_SAFE_VAL_DEF                 	 BIT_FALSE
#define PLC_DO_SAFE_ALLOW_DEF           		 BIT_FALSE

/** @def Status codes
 */
#define PLC_DO_STATUS_OFF                        PLC_DO_MODE_OFF
#define PLC_DO_STATUS_NORM                       PLC_DO_MODE_NORM
#define PLC_DO_STATUS_FAST                       PLC_DO_MODE_FAST
#define PLC_DO_STATUS_PWM_ON                     PLC_DO_MODE_PWM
#define PLC_DO_STATUS_PWM_OFF                    (uint8_t)(PLC_DO_MODE_PWM*10)
#define PLC_DO_STATUS_SAFE                       (uint8_t)4


/** @def Queue item
 *       main settings
 */
typedef struct PlcDO_Q_t_
{
    //@var Channel number
    uint8_t Ch;
    //@var Item ID
    uint8_t ID;
    //@var Value
    float   Val;

} PlcDO_Q_t;

/** @def Queue IDs
 */
#define PLC_DO_Q_ID_NONE       					(uint8_t)0
#define PLC_DO_Q_ID_MODE       					(uint8_t)1   //mode
#define PLC_DO_Q_ID_NORM_VAL       				(uint8_t)2   //normal value
#define PLC_DO_Q_ID_FAST_VAL       				(uint8_t)3   //fast value
#define PLC_DO_Q_ID_PWM_T        				(uint8_t)4   //PWM period (ms)
#define PLC_DO_Q_ID_PWM_D       				(uint8_t)41  //PWM fill factor (%)
#define PLC_DO_Q_ID_PWM_ALLOW       			(uint8_t)43  //PWM allow
#define PLC_DO_Q_ID_SAFE_VAL     				(uint8_t)5   //safety value
#define PLC_DO_Q_ID_SAFE_ALLOW       			(uint8_t)51  //safety value allow
#define PLC_DO_Q_ID_STATUS     					(uint8_t)6   //status
#define PLC_DO_Q_ID_POSTPONED_VAL     			(uint8_t)7   //postponed normal value
#define PLC_DO_Q_ID_POSTPONED_APPLY    			(uint8_t)71  //apply postponed normal value

/** @var Postponed normal values (flag)
 *  @arg   = 0 - does not have postponed values
 *  @arg   = 1 - have postponed values
 */
extern uint8_t PLC_DO_POSTPONED;


/** @brief  Init. DO.
 *  @param  DOIn - channel.
 *  @return None.
 */
void PlcDO_Init(PlcDO_t *DOIn);

/** @brief  DeInit. DO.
 *  @param  DOIn - channel.
 *  @return None.
 */
void PlcDO_DeInit(PlcDO_t *DOIn);

/** @brief  Start DO.
 *  @param  DOIn - channel.
 *  @return None.
 */
void PlcDO_Start(PlcDO_t *DOIn);

/** @brief  Stop DO.
 *  @param  DOIn - channel.
 *  @return None.
 */
void PlcDO_Stop(PlcDO_t *DOIn);

/** @brief  Set new period value into TIM.PWM.
 *  @param  DOIn - channel.
 *  @param  PeriodIn - new period value (ms):
 *  @arg    = PLC_DO_PWM_T__MIN ... PLC_DO_PWM_T__MAX
 *  @return New period value (ms).
 */
float PlcDO_SetPeriod(PlcDO_t *DOIn, float PeriodIn);

/** @brief  Set new pulse value (fill factor) into TIM.PWM.
 *  @param  DOIn - channel.
 *  @param  PulseIn - new pulse value (%):
 *  @arg    = PLC_DO_PWM_D__MIN ... PLC_DO_PWM_D__MAX
 *  @return New pulse value (%).
 */
float PlcDO_SetPulse(PlcDO_t *DOIn, float PulseIn);

/** @brief  Set new normal value into TIM.PWM.
 *  @param  DOIn - channel.
 *  @param  ValIn - new normal value:
 *  @arg    = 0 - low output level
 *  @arg    = 1 - high output level
 *  @return None.
 */
void PlcDO_SetNormVal(PlcDO_t *DOIn, uint8_t ValIn);

#endif //PLC_DO_H
