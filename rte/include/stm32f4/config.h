/* @page config.h
 *       PLC411::RTE
 *       Configuration Defines
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022, atgroup09@gmail.com
 */

#ifndef PLC_CONFIG_H
#define PLC_CONFIG_H

#include <stdint.h>
#include <stdarg.h>

#include "bit.h"
#include "type.h"

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"


/** RTOS
 *  ===========================================================================
  */

/** @def RTOS used/not used
 */
#define PLC_RTOS


/** VERSION NUMBERS
 *  ===========================================================================
 */

/** @def    Pack RTE-version
 *  @param  MajorIn - Major
 *  @param  MinorIn - Minor
 *  @param  PatchIn - Patch
 *  @return Packed RTE-version
 */
#define PACK_PLC_RTE_VERSION(MajorIn, MinorIn, PatchIn) ((PatchIn<<8)+(MinorIn<<4)+MajorIn)

/** @def    Pack RTE-day.month
 *  @param  DayIn - Major
 *  @param  MonthIn - Minor
 *  @return Packed RTE-day.month
 */
#define PACK_PLC_RTE_DDMM(DayIn, MonthIn) ((DayIn<<4)+MonthIn)


/** @def PLC-code
 */
#define PLC_HW_CODE                              411

/** @def PLC-variant
 */
#define PLC_HW_VAR                               1

/** @def RTE-version
 */
#define PLC_RTE_VERSION_MAJOR                    1
#define PLC_RTE_VERSION_MINOR                    0
#define PLC_RTE_VERSION_PATCH                    0

/** @def RTE-version (packed)
 */
#define PLC_RTE_VERSION                          (uint16_t)PACK_PLC_RTE_VERSION(PLC_RTE_VERSION_MAJOR, PLC_RTE_VERSION_MINOR, PLC_RTE_VERSION_PATCH)

/** @def RTE-year
 */
#define PLC_RTE_YYYY                             2023

/** @def RTE-day.month
 */
#define PLC_RTE_DDMM                             (uint16_t)PACK_PLC_RTE_DDMM(11, 5)


/** RTE MODULES
 *  ===========================================================================
 *  (comment/uncomment the required lines)
 */

#define RTE_MOD_REG		          		 	 	 //Registers
#define RTE_MOD_REG_MON						 	 //Register Monitoring
#define RTE_MOD_DI				             	 //DI
#define RTE_MOD_DO			 	              	 //DO
#define RTE_MOD_AI				            	 //AI
#define RTE_MOD_LED				                 //LED
#define RTE_MOD_DATA				             //Data Manager
#define RTE_MOD_COM1		          		 	 //COM1
#define RTE_MOD_COM2		          		 	 //COM2
#define RTE_MOD_APP				             	 //Application
#define RTE_MOD_APP_TIM			             	 //Application Timer
#define RTE_MOD_APP_DEBUG_HANDLER			     //Application Debug-handler
//#define RTE_MOD_FACTORY			             //Factory values
#define RTE_MOD_SYS_REG			           	 	 //System registers


/** DEBUG MODE
 *  ===========================================================================
 *  (comment/uncomment the required lines)
 */

/** @def  Global permit Debug-flag
 *  @note remove compiler-option -DDEBUG to use this flag
 */
//#define DEBUG

/** @def Supported Debug-interfaces
 */
#define DEBUG_LOG_DST_NO                         0   //No output
#define DEBUG_LOG_DST_SWD                        1   //SWO

#ifdef DEBUG

/** @def Used Debug-interface
 */
#define DEBUG_LOG_DST                            DEBUG_LOG_DST_SWD

/** @def DebugLog Modules
 */
#define DEBUG_LOG_ERROR				         	 //RTOS errors
#define DEBUG_LOG_MAIN				             //Main
//#define DEBUG_LOG_REG							 //REG
//#define DEBUG_LOG_REG_MON			             //REG_MONITOR
//#define DEBUG_LOG_MBRTU		       		 	 //ModBus RTU API
//#define DEBUG_LOG_LED					         //LED_T
//#define DEBUG_LOG_COM1       		 	 	 	 //COM1_T
//#define DEBUG_LOG_COM2       		 	 	 	 //COM2_T
//#define DEBUG_LOG_DATA       		 	 	 	 //DATA_T
//#define DEBUG_LOG_SYS_REG						 //System Registers

//#define DEBUG_LOG_DI       		 	 	 	 //DI_T
//#define DEBUG_LOG_DI_EXTI       		 	 	 //DI_EXTI
//#define DEBUG_LOG_DI_TACH_TIM    		 	 	 //DI_TACH_TIM
//#define DEBUG_LOG_DI_FLTR_TIM    		 	 	 //DI_FLTR_TIM
//#define DEBUG_LOG_DI_Q      		 	 	 	 //DI_Q
//#define DEBUG_LOG_DI_IRQ_Q   		 	 	 	 //DI_IRQ_Q
//#define DEBUG_LOG_DI_DATA_Q  		 	 	 	 //DI_DATA_Q

//#define DEBUG_LOG_DO       		  	 	 	 //DO_T
//#define DEBUG_LOG_DO_Q  		 	 	 	 	 //DO_Q
//#define DEBUG_LOG_DO_Q_VAL  		 	 	 	 //DO_Q_VAL
//#define DEBUG_LOG_DO_DATA_Q  		 	 	 	 //DO_DATA_Q

//#define DEBUG_LOG_AI       		 	 	 	 //AI_T
//#define DEBUG_LOG_ADC       		 	 	 	 //ADC
//#define DEBUG_LOG_AI_TIM       		 	 	 //AI_TIM
//#define DEBUG_LOG_AI_Q  		 	 	 	 	 //AI_Q
//#define DEBUG_LOG_AI_Q_VAL  	 	 	 	 	 //AI_Q(VAL)
//#define DEBUG_LOG_AI_DATA_Q  		 	 	 	 //AI_DATA_Q
//#define DEBUG_LOG_AI_DATA_Q_VAL		 	 	 //AI_DATA_Q(VAL)

//#define DEBUG_LOG_APP       		 	 	 	 //APP_T
//#define DEBUG_LOG_APP_RUN       		 	 	 //APP_T.Run
//#define DEBUG_LOG_APP_TIM      		 	 	 //APP_TIM
//#define DEBUG_LOG_APP_VAR      		 	 	 //Application relation variables

#endif // DEBUG


/** FREQUENCY DEFINES
 *  ===========================================================================
 */

/** @def MHz base
 *       1 MHz = 1000000 Hz
 */
#define MHZ_BASE                                 1000000UL

/** @def Flag values
 */
#define FLAG_RESET                               BIT_FALSE
#define FLAG_SET                                 BIT_TRUE

/** @def SysClock defines
 */
#define PLC_F_CPU                                (uint32_t)(100*MHZ_BASE)

#define PLC_HSE_FREQ                             (uint32_t)(25*MHZ_BASE)  //HSE
#define PLC_SYSCLK_FREQ                          (uint32_t)(100*MHZ_BASE) //SYSCLK
#define PLC_HCLK_FREQ                            (uint32_t)(100*MHZ_BASE) //HCLK
#define PLC_AHB_FREQ                             PLC_HCLK_FREQ            //AHB
#define PLC_APB1_PCLK_FREQ                       (uint32_t)(50*MHZ_BASE)  //APB1 Peripheral clocks
#define PLC_APB1_TCLK_FREQ                       (uint32_t)(100*MHZ_BASE) //APB1 Timer clocks
#define PLC_APB2_PCLK_FREQ                       (uint32_t)(100*MHZ_BASE) //APB2 Peripheral clocks
#define PLC_APB2_TCLK_FREQ                       (uint32_t)(100*MHZ_BASE) //APB2 Timer clocks

/** @def SysTick freq.
 *       1-tick = 1000Hz = 1000us = 1ms
 *
 *       1kHz = 1000Hz = 1ms
 *       1MHz = 1000000Hz = 1us
 */
#define PLC_SYSTICK_FREQ_HZ                      1000   //Hz


/** IRQ PRIORITY DEFINES
 *  ===========================================================================
 *   0 is a higher priority
 *  15 is a lower priority
 */

// __initialize_hardware(void) :: HAL_Init()
//  4 bits for preemption priority (0...15)
//  0 bits for subpriority (0)
#define PLC_NVIC_PRIO_GROUP            			 NVIC_PRIORITYGROUP_4

//Lowest NVIC-priority
#define PLC_NVIC_PRIO_LOWEST                     15

//Max NVIC-priority of system-dependent IRQ
#define PLC_NVIC_PRIO_RTOS_SYSCALL               8

// SYSTEM-DEPENDENT ISR
// - PPRIO > PLC_NVIC_PRIO_RTOS_SYSCALL
// - that using RTOS API (*FromISR)
// - without interrupt the procedures of KERNEL or CRITICAL-SECTIONS (ISR is waiting for complete the procedures)

//COM1(DebugProto)
// .DMA.UART.Tx
#define PLC_NVIC_PPRIO_COM1_DMA_TX           	 13
#define PLC_NVIC_SPRIO_COM1_DMA_TX           	 0
// .DMA.UART.Rx
#define PLC_NVIC_PPRIO_COM1_DMA_RX           	 13
#define PLC_NVIC_SPRIO_COM1_DMA_RX          	 0
// .UART
#define PLC_NVIC_PPRIO_COM1_UART           		 13
#define PLC_NVIC_SPRIO_COM1_UART          		 0

//COM2(ModBus)
// .DMA.UART.Tx
#define PLC_NVIC_PPRIO_COM2_DMA_TX           	 9
#define PLC_NVIC_SPRIO_COM2_DMA_TX           	 0
// .DMA.UART.Rx
#define PLC_NVIC_PPRIO_COM2_DMA_RX           	 9
#define PLC_NVIC_SPRIO_COM2_DMA_RX          	 0
// .UART
#define PLC_NVIC_PPRIO_COM2_UART           		 9
#define PLC_NVIC_SPRIO_COM2_UART          		 0

//DO
// .DMA.Tc
#define PLC_NVIC_PPRIO_DO_DMA           	 	 10
#define PLC_NVIC_SPRIO_DO_DMA           	 	 0

//AI
// .DMA.Tc
#define PLC_NVIC_PPRIO_AI_DMA           	 	 11
#define PLC_NVIC_SPRIO_AI_DMA           	 	 0
// .ADC
#define PLC_NVIC_PPRIO_AI_ADC           	 	 11
#define PLC_NVIC_SPRIO_AI_ADC           	 	 0

//DI
// .EXTI
#define PLC_NVIC_PPRIO_DI_EXTI           	 	 12
#define PLC_NVIC_SPRIO_DI_EXTI           	 	 0

//SysTick
#define PLC_NVIC_PPRIO_SYSTICK                   15
#define PLC_NVIC_SPRIO_SYSTICK                   0

// SYSTEM-INDEPENDENT ISR
// - PPRIO <= PLC_NVIC_PRIO_RTOS_SYSCALL
// - that NOT using RTOS API (*FromISR)
// - with interrupt the procedures of KERNEL or CRITICAL-SECTIONS (ISR is not waiting for complete the procedures)


/** DMA PRIORITY DEFINES
 *  ===========================================================================
 */

//DO
#define PLC_DMA_PRIO_DO							DMA_PRIORITY_HIGH

//AI
#define PLC_DMA_PRIO_AI							DMA_PRIORITY_HIGH

//COM2(ModBus)
#define PLC_DMA_PRIO_COM2_RX					DMA_PRIORITY_MEDIUM
#define PLC_DMA_PRIO_COM2_TX					DMA_PRIORITY_MEDIUM

//COM1(DebugLog)
#define PLC_DMA_PRIO_COM1_RX					DMA_PRIORITY_LOW
#define PLC_DMA_PRIO_COM1_TX					DMA_PRIORITY_LOW


/** TASK PRIORITY DEFINES
 *  ===========================================================================
 *   0 is a lower priority (IDLE-task has zero priority)
 *  PLC_RTOS_PRIO_MAX-1 is a higher priority
 */

//Max NVIC-priority of system-dependent IRQ
#define PLC_RTOS_PRIO_MAX						10

// BLOCKING TASKS
// - higher priorities (4,5,6,7)
#define PLC_RTOS_PRIO_T_COM1					4
#define PLC_RTOS_PRIO_T_COM2					4
#define PLC_RTOS_PRIO_T_DI						5
#define PLC_RTOS_PRIO_T_DI_IRQ					5
#define PLC_RTOS_PRIO_T_AI						5
#define PLC_RTOS_PRIO_T_DO						6
#define PLC_RTOS_PRIO_T_LED						4

// NON-BLOCKING TASKS
// - lower priorities (1,2,3)
#define PLC_RTOS_PRIO_T_DATA					3
#define PLC_RTOS_PRIO_T_APP						3


/** COM1
 *  ===========================================================================
 */

/** @def Slave Address (by default)
 */
#define PLC_COM1_SLAVE_ADDR           			 (uint16_t)1


/** COM2
 *  ===========================================================================
 */

/** @def Slave Address (by default)
 */
#define PLC_COM2_SLAVE_ADDR           			 (uint16_t)1

/** @def Settings (pack)
 *       MBRTU_BAUDRATE_115200
 *       MBRTU_DATA_BITS_8
 *       MBRTU_PARITY_NONE
 *       MBRTU_STOP_BITS_1
 *       MBRTU_MODE_SLAVE
 *       MBRTU_BYTE_ORDER_1032
 */
#define PLC_COM2_SET                   			 (uint16_t)1031


#endif //PLC_CONFIG_H
