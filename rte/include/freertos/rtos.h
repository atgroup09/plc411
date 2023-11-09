/* @page rtos.h
 *       PLC411::RTE
 *       RTOS Context
 *       2022-2023, atgroup09@gmail.com
 */

#ifndef RTOS_H
#define RTOS_H

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"
#include "config.h"


/** TASK
 *    *_T_NAME     - task name (for debug, strlen <= configMAX_TASK_NAME_LEN)
 *    *_T_STACK_SZ - task stack size (>= configMINIMAL_STACK_SIZE)
 *    *_T_PRIORITY - task priority (<= configMAX_PRIORITIES)
 *
 *  QUEUE
 *    *_Q_ISZ      - size of one queue-item (sizeof(t), where t is the item type)
 *    *_Q_SZ       - quantity of queue-items
 *    *_Q          - queue
 *
 *  MUTEX
 *    *_MTX        - mutex
 *
 *  SEMAPHORE (binary)
 *    *_SEMA       - semaphore
 */


/** @def RTOS tick time
 *       1kHz = 1000Hz = 1ms
 */
#define RTOS_TICK_MS (uint32_t)1        //ms
#define RTOS_TICK_NS (uint32_t)1000000  //ns


/** @def Mutex MBTABLES
 */
extern SemaphoreHandle_t RTOS_MBTABLES_MTX;


#ifdef RTE_MOD_REG_MON

/** @def Queue DATA_REG_MONITOR_Q
 */
#define RTOS_DATA_REG_MONITOR_Q_ISZ    (UBaseType_t)sizeof(uint16_t)
#define RTOS_DATA_REG_MONITOR_Q_SZ     (UBaseType_t)256
extern QueueHandle_t RTOS_DATA_REG_MONITOR_Q;

#endif // RTE_MOD_REG_MON


#ifdef RTE_MOD_DI

#include "di.h"

/** @def Task DI_IRQ_T (blocking)
 */
#define RTOS_DI_IRQ_T_NAME             "DI_IRQ_T"
#define RTOS_DI_IRQ_T_STACK_SZ         (configSTACK_DEPTH_TYPE)configMINIMAL_STACK_SIZE
#define RTOS_DI_IRQ_T_PRIORITY         (UBaseType_t)PLC_RTOS_PRIO_T_DI_IRQ

/** @def Task DI_T (blocking)
 */
#define RTOS_DI_T_NAME                 "DI_T"
#define RTOS_DI_T_STACK_SZ             (configSTACK_DEPTH_TYPE)configMINIMAL_STACK_SIZE
#define RTOS_DI_T_PRIORITY             (UBaseType_t)PLC_RTOS_PRIO_T_DI

/** @def Queue DI_IRQ_Q
 *  @note > DI_IRQ_T (IRQ data)
 */
#define RTOS_DI_IRQ_Q_ISZ    		   (UBaseType_t)sizeof(PlcDI_IRQ_Q_t)
#define RTOS_DI_IRQ_Q_SZ     		   (UBaseType_t)(PLC_DI_SZ*64)
extern QueueHandle_t RTOS_DI_IRQ_Q;

/** @def Queue DI_Q
 *  @note > DI_T (settings, commands)
 */
#define RTOS_DI_Q_ISZ    			   (UBaseType_t)sizeof(PlcDI_Q_t)
#define RTOS_DI_Q_SZ     		       (UBaseType_t)(PLC_DI_SZ*16)
extern QueueHandle_t RTOS_DI_Q;

/** @def Queue DI_DATA_Q
 *  @note > DATA_T (approved settings and commands, statuses, data)
 */
#define RTOS_DI_DATA_Q_ISZ    		   (UBaseType_t)sizeof(PlcDI_Q_t)
#define RTOS_DI_DATA_Q_SZ     		   (UBaseType_t)(PLC_DI_SZ*64)
extern QueueHandle_t RTOS_DI_DATA_Q;

/** @var Timer DI_TACH_TIM (auto-reloaded with controlled launch)
 *  @note tachometer survey period
 */
#define RTOS_DI_TACH_TIM_NAME          "DI_TACH_TIM"
#define RTOS_DI_TACH_TIM_TM            (TickType_t)PLC_DI_TACH_SURVEY_PERIOD_MS
extern TimerHandle_t RTOS_DI_TACH_TIM;

/** @var Timer DI_FLTR_TIM (one-shot)
 */
#define RTOS_DI_FLTR_TIM_NAME          "DI_FLTR_TIM"
#define RTOS_DI_FLTR_TIM_TM            (TickType_t)PLC_DI_FLTR_DELAY_MS
extern TimerHandle_t RTOS_DI_FLTR_TIM;

#endif //RTE_MOD_DI


#ifdef RTE_MOD_DO

#include "do.h"

/** @def Task DO_T (blocking)
 */
#define RTOS_DO_T_NAME                 "DO_T"
#define RTOS_DO_T_STACK_SZ             (configSTACK_DEPTH_TYPE)configMINIMAL_STACK_SIZE
#define RTOS_DO_T_PRIORITY             (UBaseType_t)PLC_RTOS_PRIO_T_DO

/** @def Queue DO_Q
 *  @note > DO_T (settings, commands)
 */
#define RTOS_DO_Q_ISZ    			   (UBaseType_t)sizeof(PlcDO_Q_t)
#define RTOS_DO_Q_SZ     		       (UBaseType_t)(PLC_DO_SZ*16)
extern QueueHandle_t RTOS_DO_Q;

/** @def Queue DO_DATA_Q
 *  @note > DATA_T (approved settings and commands, statuses, data)
 */
#define RTOS_DO_DATA_Q_ISZ    		   (UBaseType_t)sizeof(PlcDO_Q_t)
#define RTOS_DO_DATA_Q_SZ     		   (UBaseType_t)(PLC_DO_SZ*16)
extern QueueHandle_t RTOS_DO_DATA_Q;

#endif //RTE_MOD_DO


#ifdef RTE_MOD_AI

#include "ai.h"

/** @def Task AI_T (blocking)
 */
#define RTOS_AI_T_NAME                 "AI_T"
#define RTOS_AI_T_STACK_SZ             (configSTACK_DEPTH_TYPE)configMINIMAL_STACK_SIZE
#define RTOS_AI_T_PRIORITY             (UBaseType_t)PLC_RTOS_PRIO_T_AI

/** @def Queue AI_Q
 *  @note > AI_T (settings, commands)
 */
#define RTOS_AI_Q_ISZ    			   (UBaseType_t)sizeof(PlcAI_Q_t)
#define RTOS_AI_Q_SZ     			   (UBaseType_t)(PLC_AI_SZ*16)
extern QueueHandle_t RTOS_AI_Q;

/** @def Queue AI_DATA_Q
 *  @note > DATA_T (approved settings and commands, statuses, data)
 */
#define RTOS_AI_DATA_Q_ISZ    		   (UBaseType_t)sizeof(PlcAI_Q_t)
#define RTOS_AI_DATA_Q_SZ     		   (UBaseType_t)(PLC_AI_SZ*16)
extern QueueHandle_t RTOS_AI_DATA_Q;

/** @var Timer AI_TIM (one-shot)
 *  @note survey period
 */
#define RTOS_AI_TIM_NAME               "AI_TIM"
#define RTOS_AI_TIM_TM                 (TickType_t)PLC_AI_SURVEY_PERIOD_MS
extern TimerHandle_t RTOS_AI_TIM;

#endif //RTE_MOD_AI


#ifdef RTE_MOD_LED

#include "led.h"

/** @def Queue LED_Q
 *  @note > LED_T (settings, commands)
 */
#define RTOS_LED_Q_ISZ    			   (UBaseType_t)sizeof(PlcLED_Q_t)
#define RTOS_LED_Q_SZ     			   (UBaseType_t)(PLC_LED_SZ*32)
extern QueueHandle_t RTOS_LED_Q;

/** @def Task LED_T (blocking)
 */
#define RTOS_LED_T_NAME                "LED_T"
#define RTOS_LED_T_STACK_SZ            (configSTACK_DEPTH_TYPE)configMINIMAL_STACK_SIZE
#define RTOS_LED_T_PRIORITY            (UBaseType_t)PLC_RTOS_PRIO_T_LED

#endif // RTE_MOD_LED


#ifdef RTE_MOD_DATA

/** @def Task DATA_T (blocking)
 */
#define RTOS_DATA_T_NAME               "DATA_T"
#define RTOS_DATA_T_STACK_SZ           (configSTACK_DEPTH_TYPE)256
#define RTOS_DATA_T_PRIORITY           (UBaseType_t)PLC_RTOS_PRIO_T_DATA

#endif // RTE_MOD_DATA


#ifdef RTE_MOD_COM1

/** @def Task COM1_T (blocking)
 */
#define RTOS_COM1_T_NAME               "COM1_T"
#define RTOS_COM1_T_STACK_SZ           (configSTACK_DEPTH_TYPE)configMINIMAL_STACK_SIZE
#define RTOS_COM1_T_PRIORITY           (UBaseType_t)PLC_RTOS_PRIO_T_COM1

/** @def Queue COM1 (settings, commands, input data)
 */
#define RTOS_COM1_Q_ISZ    			   (UBaseType_t)sizeof(uint8_t)
#define RTOS_COM1_Q_SZ     			   (UBaseType_t)32
extern QueueHandle_t RTOS_COM1_Q;

#endif //RTE_MOD_COM1


#ifdef RTE_MOD_COM2

/** @def Task COM2_T (blocking)
 */
#define RTOS_COM2_T_NAME               "COM2_T"
#define RTOS_COM2_T_STACK_SZ           (configSTACK_DEPTH_TYPE)configMINIMAL_STACK_SIZE
#define RTOS_COM2_T_PRIORITY           (UBaseType_t)PLC_RTOS_PRIO_T_COM2

/** @def Queue COM2 (settings, commands, input data)
 */
#define RTOS_COM2_Q_ISZ    			   (UBaseType_t)sizeof(uint8_t)
#define RTOS_COM2_Q_SZ     			   (UBaseType_t)32
extern QueueHandle_t RTOS_COM2_Q;

#endif //RTE_MOD_COM2


#ifdef RTE_MOD_APP

/** @def Task APP_T (non-blocking)
 */
#define RTOS_APP_T_NAME                "APP_T"
#define RTOS_APP_T_STACK_SZ            (configSTACK_DEPTH_TYPE)2048
#define RTOS_APP_T_PRIORITY            (UBaseType_t)PLC_RTOS_PRIO_T_APP

/** @def Semaphore APP_SEMA
 */
extern SemaphoreHandle_t RTOS_APP_SEMA;

/** @var Timer APP_TIM (one-shot)
 *  @note application period
 */
#define RTOS_APP_TIM_NAME              "APP_TIM"
#define RTOS_APP_TIM_TM                (TickType_t)1
extern TimerHandle_t RTOS_APP_TIM;

#endif //RTE_MOD_APP


#endif //RTOS_H
