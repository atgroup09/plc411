/* @page rtos.c
 *       PLC411::RTE
 *       RTOS Context
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022-2023, atgroup09@gmail.com
 */

#include "rtos.h"


SemaphoreHandle_t RTOS_MBTABLES_MTX;

#ifdef RTE_MOD_REG_MON
QueueHandle_t RTOS_DATA_REG_MONITOR_Q;
#endif // RTE_MOD_REG_MON

#ifdef RTE_MOD_DI
QueueHandle_t RTOS_DI_IRQ_Q;
QueueHandle_t RTOS_DI_Q;
QueueHandle_t RTOS_DI_DATA_Q;
TimerHandle_t RTOS_DI_TACH_TIM;
TimerHandle_t RTOS_DI_FLTR_TIM;
#endif // RTE_MOD_DI

#ifdef RTE_MOD_DO
QueueHandle_t RTOS_DO_Q;
QueueHandle_t RTOS_DO_DATA_Q;
#endif // RTE_MOD_DO

#ifdef RTE_MOD_AI
QueueHandle_t RTOS_AI_Q;
QueueHandle_t RTOS_AI_DATA_Q;
TimerHandle_t RTOS_AI_TIM;
#endif // RTE_MOD_AI

#ifdef RTE_MOD_LED
QueueHandle_t RTOS_LED_Q;
#endif // RTE_MOD_LED

#ifdef RTE_MOD_COM1
QueueHandle_t RTOS_COM1_Q;
#endif // RTE_MOD_COM1

#ifdef RTE_MOD_COM2
QueueHandle_t RTOS_COM2_Q;
#endif // RTE_MOD_COM2

#ifdef RTE_MOD_APP
SemaphoreHandle_t RTOS_APP_SEMA;
TimerHandle_t RTOS_APP_TIM;
#endif // RTE_MOD_APP
