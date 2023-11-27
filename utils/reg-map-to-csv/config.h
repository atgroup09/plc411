/* @page config.h
 *       Config defines
 *       2020-2022
 */

#ifndef PLC_CONFIG_H
#define PLC_CONFIG_H

#include <stdint.h>
#include <stdarg.h>
#include "bit.h"


/** RTE CONSTANTS
 */

/** @def PLC code (2004)
 */
#define PLC_HW_CODE                    (uint16_t)107

/** @def PLC variant
 */
#define PLC_HW_VAR                     (uint16_t)1

/** @def RTE version
 *  @note
 *       Bitfield:
 *       uint16_t Major:4 (1)
 *       uint16_t Minor:4 (3)
 *       uint16_t Patch:4 (0)
 */
#define PLC_RTE_VERSION                (uint16_t)49

/** @def RTE year (2021)
 */
#define PLC_RTE_YYYY                   (uint16_t)2021

/** @def RTE day+month
 *  @note
 *       Bitfield:
 *       uint16_t DD:5 (23)
 *       uint16_t MM:5 (02)
 */
#define PLC_RTE_DDMM                   (uint16_t)87

//=========================================================


/** RTE MODULES
 *  (comment/uncomment the required lines)
 */

#define RTE_MOD_DI              //DI
#define RTE_MOD_DO              //DO
//#define RTE_MOD_AI              //AI
//#define RTE_MOD_AO              //AO
//#define RTE_MOD_LED             //LED

#define RTE_MOD_MBRTU_SLAVE     //ModBus RTU Slave

//#define RTE_MOD_EXT_I2C       //External Modules (I2C)
//#define RTE_MOD_EEPROM_I2C    //EEPROM  (External I2C-Module)
//#define RTE_MOD_RTC_I2C       //RTC     (External I2C-Module)
//#define RTE_MOD_ACCGYRO_I2C   //ACCGYRO (External I2C-Module)
//#define RTE_MOD_LCD_I2C       //LCD     (External I2C-Module)

#define RTE_MOD_APP             //User Application
#define RTE_MOD_APP_DEBUG       //User Application Debugger
#define RTE_MOD_APP_TIM         //User Application Timer

#define RTE_MOD_REG_MONITOR     //Register Monitoring

#define RTE_MOD_DATA            //Data Manager

#define RTE_MOD_SOFT_RESET      //Software Reset

//#define RTE_MOD_FACTORY       //Factory values

//=========================================================


/** DEBUG MODE
 *  (remove compiler-option -DDEBUG to disable Debug mode)
 */

/** @def Debug Log Output Interfaces
 */
#define DEBUG_LOG_DST_NO               0   //No output
#define DEBUG_LOG_DST_SWD              1   //SWD.SWO
#define DEBUG_LOG_DST_USART            2   //USART

#ifdef DEBUG

/** @def Debug Log Interface
 *      (comment/uncomment the required line)
 */
//#define DEBUG_LOG_DST                DEBUG_LOG_DST_NO
#define DEBUG_LOG_DST                  DEBUG_LOG_DST_USART
//#define DEBUG_LOG_DST                DEBUG_LOG_DST_SWD

/** @def Debug Log USARTx
 *      (set UART interface and comment/uncomment DE-line config)
 */
//#define DEBUG_LOG_USART                USART3
//#define DEBUG_LOG_USART_DE_USE
//#define DEBUG_LOG_USART_DE_PORT      GPIOC
//#define DEBUG_LOG_USART_DE_PIN       GPIO_Pin_5

/** @def Debug Log Support
 *      (comment/uncomment the required lines)
 */

// Registers
#define DEBUG_REG

// Registers monitoring
//#define DEBUG_REG_MON

// T_MCU
//#define DEBUG_LOG_MCU

// T_MCU (ADC)
//#define DEBUG_LOG_MCU_ADC

// T_Data (DI)
//#define DEBUG_LOG_DATA_DI

// T_Data (DO)
//#define DEBUG_LOG_DATA_DO

// T_Data (AI)
//#define DEBUG_LOG_DATA_AI

// T_Data (AO)
//#define DEBUG_LOG_DATA_AO

// T_Data (MCU)
//#define DEBUG_LOG_DATA_MCU

// T_Data (COM)
//#define DEBUG_LOG_DATA_COM

// T_Data (RegMon)
//#define DEBUG_LOG_DATA_REG

// T_EEPROM
//#define DEBUG_LOG_EEPROM

// T_App
//#define DEBUG_LOG_APP

// Application Debug protocol
//#define DEBUG_LOG_APP_DBG_PROTO

// Software Reset
//#define DEBUG_LOG_SOFT_RESET

// MBRTU
//#define DEBUG_LOG_MBRTU

// T_DI
//#define DEBUG_LOG_DI

// T_DO
//#define DEBUG_LOG_DO

// T_AI
//#define DEBUG_LOG_AI

// T_AI (ADC)
//#define DEBUG_LOG_AI_ADC

// T_AO
//#define DEBUG_LOG_AO

// Main
#define DEBUG_LOG_MAIN

#else
#define DEBUG_LOG_DST                DEBUG_LOG_DST_NO
#endif // DEBUG

//=========================================================

/** @def MHz base
 *       1 MHz = 1000000 Hz
 */
#define MHZ_BASE                       1000000UL

/** @def Flag values
 */
#define FLAG_RESET                     BIT_FALSE
#define FLAG_SET                       BIT_TRUE

/** @def ModBus Slave Address
 *       (by default)
 */
#define PLC_MBRTU_SLAVE_ADDR           (uint16_t)1

/** @def COM1 settings
 *       (pack)
 */
#define PLC_COM1_SET                   (uint16_t)1031

#endif //PLC_CONFIG_H
