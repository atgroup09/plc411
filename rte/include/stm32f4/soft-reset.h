/* @page soft-reset.h
 *       PLC411::RTE
 *       Soft Reset
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2023, atgroup09@gmail.com
 */

#ifndef PLC_SOFT_RESET_H
#define PLC_SOFT_RESET_H

#include "config.h"


/** @brief  Software reset.
 *  @param  None.
 *  @return None.
 */
void Plc_SoftwareReset(void);

#endif //PLC_SOFT_RESET_H
