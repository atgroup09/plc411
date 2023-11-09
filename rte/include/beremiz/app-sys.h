/* @page app-sys.h
 *       PLC411::RTE
 *       BEREMIZ YAPLC System Functions (relationship of RTE with APP)
 *       2020-2023, atgroup09@gmail.com
 */

#ifndef APP_SYS_H
#define APP_SYS_H

#include <stdint.h>
#include "plc_abi.h"
#include "soft-reset.h"
#include "reg.h"
#include "rtos.h"

#ifdef DEBUG
#include "debug-log.h"
#endif // DEBUG


/** @brief Software Reset.
 *  @param Ex - allow to execution:
 *  @arg      = false - not allow
 *  @arg      = true  - allow
 *  @return None.
 */
void PlcApp_SoftwareReset(BOOL Ex);

/** @brief  Get SysTime.
 *  @param  None.
 *  @return None.
 */
void PlcApp_GetTime(IEC_TIME *CurrentTimeIn);

/** @brief LED_USER Control.
 *  @param V  - output level:
 *  @arg      = 0
 *  @arg      = 1
 *  @param Ov - result output level
 *  @return None.
 */
void PlcApp_LedUser(BOOL *V, BOOL *Ov);

#endif //APP_SYS_H
