/* @page di.h
 *       PLC411::RTE
 *       DI driver
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022-2023, atgroup09@gmail.com
 */

/** @note
  *		  PA8  -> EXTI8  -> DI.0
 *		  PB15 -> EXTI15 -> DI.1
 */

#ifndef PLC_DI_H
#define PLC_DI_H

#include "config.h"
#include "error.h"
#include "gpio.h"


/** @def Channel number
 */
#define PLC_DI_00                                0
#define PLC_DI_01                                1

/** @def Quantity of channels
 */
#define PLC_DI_SZ                                (uint8_t)(PLC_DI_01+1)

/** @def DI-channel
 *       GPIO reference
 */
#define PLC_DI_00__PORT                          GPIOA
#define PLC_DI_00__PIN                           GPIO_PIN_8

#define PLC_DI_01__PORT                          GPIOB
#define PLC_DI_01__PIN                           GPIO_PIN_15

/** @def Tachometer survey period (ms)
 */
#define PLC_DI_TACH_SURVEY_PERIOD_MS             1000

/** @def Filter delay (ms)
 */
#define PLC_DI_FLTR_DELAY_MS             		 20


/** @typedef DI-channel settings
 *           packed data
 */
typedef struct PlcDI_Pack_t_
{
    //@var Command to Allow Counter setpoint
    //@arg = 0 - no
    //@arg = 1 - yes
    uint8_t CntrSetpointAllow:1;

    //@var Сounter has reached the setpoint
    //@arg = 0 - no
    //@arg = 1 - yes
    uint8_t CntrSetpointReached:1;

    //@var Command to Allow Tachometer setpoint
    //@arg = 0 - no
    //@arg = 1 - yes
    uint8_t TachSetpointAllow:1;

    //@var Tachometer has reached the setpoint
    //@arg = 0 - no
    //@arg = 1 - yes
    uint8_t TachSetpointReached:1;

    //@var Command to Reset all counters
    //@arg = 0 - no
    //@arg = 1 - yes
    uint8_t Reset:1;

} PlcDI_Pack_t;

/** @typedef DI-channel settings
 *           main type
 */
typedef struct PlcDI_t_
{
	//CONSTANTS

	//@var Channel number
	//@arg = 0..15
	uint8_t Ch;

	//@var Pair channel number
    //@arg = 0..15
    uint8_t ChPair;

	//SETTINGS

    //@var Channel mode
   	//@arg = 0..15
   	uint8_t Mode;

	//@var Pack
    PlcDI_Pack_t Pack;

   	//@var Counter setpoint
    uint32_t CntrSetpoint;

    //@var Tachometer setpoint
    uint16_t TachSetpoint;

    //@var Filter timeout (ms)
   	//@arg = 0  - off
    //@arg = >0 - on
   	uint32_t FltrDelay;

	//VALUES

    //@var Normal value
    uint8_t NormVal;

    //@var Counter value
    uint32_t CntrVal;

    //@var Tachometer value
    uint16_t TachVal;

    //@var Tachometer local counter
    uint16_t TachCntrVal;

	//STATUSES

	//@var Status code
	//@arg = 0..255
	uint8_t Status;

} PlcDI_t;

/** @typedef DI-channel settings
 *           filter
 */
typedef struct PlcDI_Fltr_t_
{
	//SETTINGS

    //@var Filter timeout (ms)
   	//@arg = 0  - off
    //@arg = >0 - on
   	uint32_t FltrDelay;

	//VALUES

    //@var Filter value
    uint8_t FltrVal;

    //@var Filter timestamp
    uint32_t FltrTs;

	//STATUSES

    //@var Filter lock
    uint8_t Fltr;

} PlcDI_Fltr_t;


/** @def Modes
 */
#define PLC_DI_MODE_OFF                          (uint8_t)0  //off
#define PLC_DI_MODE_NORM                         (uint8_t)1  //normal
#define PLC_DI_MODE_CNTR                         (uint8_t)2  //counter
#define PLC_DI_MODE_TACH                         (uint8_t)3  //tachometer
#define PLC_DI_MODE_INC1                         (uint8_t)4  //incremental encoder (counter)
#define PLC_DI_MODE_INC2                         (uint8_t)5  //incremental encoder (counter + tachometer)

/** @def Settings by default
 */
#define PLC_DI_MODE_DEF      	                 PLC_DI_MODE_OFF
#define PLC_DI_CNTR_SETPOINT_DEF                 (uint32_t)0
#define PLC_DI_CNTR_SETPOINT_ALLOW_DEF           BIT_FALSE
#define PLC_DI_TACH_SETPOINT_DEF                 (uint16_t)0
#define PLC_DI_TACH_SETPOINT_ALLOW_DEF           BIT_FALSE
#define PLC_DI_FLTR_DELAY_DEF           		 PLC_DI_FLTR_DELAY_MS

/** @def Status codes
 */
#define PLC_DI_STATUS_OFF                        PLC_DI_MODE_OFF
#define PLC_DI_STATUS_NORM                       PLC_DI_MODE_NORM
#define PLC_DI_STATUS_CNTR                       PLC_DI_MODE_CNTR
#define PLC_DI_STATUS_TACH                       PLC_DI_MODE_TACH
#define PLC_DI_STATUS_INC1                       PLC_DI_MODE_INC1
#define PLC_DI_STATUS_INC2                       PLC_DI_MODE_INC2


/** @def    Test phase A of pair.
 *  @param  ChIn - channel number.
 *  @return Result:
 *  @arg    = 0 - the channel is not phase A of pair
 *  @arg    = 1 - the channel is phase A of pair
 */
#define PLC_DI_IS_PHASE_A(ChIn)                  (uint8_t)((ChIn == PLC_DI_00) ? BIT_TRUE : BIT_FALSE)

/** @def    Test phase B of pair.
 *  @param  ChIn - channel number.
 *  @return Result:
 *  @arg    = 0 - the channel is not phase B of pair
 *  @arg    = 1 - the channel is phase B of pair
 */
#define PLC_DI_IS_PHASE_B(ChIn)                  (!PLC_DI_IS_PHASE_A(ChIn))


/** @def Queue item
 *       IRQ
 */
typedef struct PlcDI_IRQ_Q_t_
{
    //@var Channel number
    uint8_t Ch:4;
    //@var Normal value
    uint8_t Val:1;

} PlcDI_IRQ_Q_t;

/** @def Queue item
 *       main settings
 */
typedef struct PlcDI_Q_t_
{
    //@var Channel number
    uint8_t Ch;
    //@var Item ID
    uint8_t ID;
    //@var Value
    uint32_t Val;

} PlcDI_Q_t;

/** @def Queue IDs
 */
#define PLC_DI_Q_ID_NONE       					 (uint8_t)0
#define PLC_DI_Q_ID_MODE       					 (uint8_t)1   //mode
#define PLC_DI_Q_ID_NORM_VAL  				     (uint8_t)2   //normal value
#define PLC_DI_Q_ID_CNTR_VAL   				     (uint8_t)3   //counter value
#define PLC_DI_Q_ID_CNTR_SETPOINT     			 (uint8_t)31  //counter setpoint
#define PLC_DI_Q_ID_CNTR_SETPOINT_ALLOW			 (uint8_t)32  //allow counter setpoint
#define PLC_DI_Q_ID_CNTR_SETPOINT_REACHED		 (uint8_t)33  //counter has reached the setpoint
#define PLC_DI_Q_ID_TACH_VAL   				     (uint8_t)4   //tachometer value
#define PLC_DI_Q_ID_TACH_SETPOINT     			 (uint8_t)41  //tachometer setpoint
#define PLC_DI_Q_ID_TACH_SETPOINT_ALLOW			 (uint8_t)42  //allow tachometer setpoint
#define PLC_DI_Q_ID_TACH_SETPOINT_REACHED		 (uint8_t)43  //tachometer has reached the setpoint
#define PLC_DI_Q_ID_STATUS     					 (uint8_t)5   //status
#define PLC_DI_Q_ID_RESET     					 (uint8_t)6   //command to reset all counters
#define PLC_DI_Q_ID_FILTER_DELAY				 (uint8_t)7   //filter delay


/** @typedef DI Callback user-functions
 */
typedef struct
{
    void (*Exti)(PlcDI_IRQ_Q_t DataIn);

} PLC_DI_UserFunc_t;


/** @var DI Callback user-functions
 */
extern PLC_DI_UserFunc_t PLC_DI00_USER_FUNC;
extern PLC_DI_UserFunc_t PLC_DI01_USER_FUNC;


/** @brief  Init. DI.
 *  @param  None.
 *  @return None.
 */
void PlcDI_Init(void);

/** @brief  DeInit. DI.
 *  @param  None.
 *  @return None.
 */
void PlcDI_DeInit(void);


/** @brief  Read channel normal value.
 *  @param  ChIn - channel number.
 *  @return Normal value.
 */
uint8_t PlcDI_ReadNormVal(uint8_t ChIn);


#endif //PLC_DI_H
