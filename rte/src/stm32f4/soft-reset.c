/* @page soft-reset.c
 *       PLC411::RTE
 *       Soft Reset
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2023, atgroup09@gmail.com
 */

#include "soft-reset.h"


/** @brief  Software reset.
 *  @param  None.
 *  @return None.
 */
void Plc_SoftwareReset(void)
{
	SCB->AIRCR = (uint32_t)((0x5FAUL << SCB_AIRCR_VECTKEY_Pos) |
            				(SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk) |
							 SCB_AIRCR_SYSRESETREQ_Msk);

    //wait until reset
    while(1);
}
