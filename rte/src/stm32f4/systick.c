/* @page systick.c
 *       PLC411::RTE
 *       SysTick Driver
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022, atgroup09@gmail.com
 */

#include "systick.h"


/** @brief  SysTick Handler.
 *  @param  None.
 *  @return None.
 */
void SysTick_Handler(void)
{
	//HAL.Tick
	HAL_IncTick();

	//RTOS.Tick (if scheduler is started)
#if (INCLUDE_xTaskGetSchedulerState == 1 )
	if(xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
	{
#endif /* INCLUDE_xTaskGetSchedulerState */
		xPortSysTickHandler();
#if (INCLUDE_xTaskGetSchedulerState == 1 )
	}
#endif /* INCLUDE_xTaskGetSchedulerState */
}
