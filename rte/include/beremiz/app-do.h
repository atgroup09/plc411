/* @page app-do.h
 *       PLC411::RTE
 *       BEREMIZ YAPLC DO System Functions (relationship of RTE with APP)
 *       2020-2023, atgroup09@gmail.com
 */

#ifndef APP_DO_H
#define APP_DO_H

#include <stdint.h>
#include "plc_abi.h"
#include "do.h"
#include "reg.h"
#include "rtos.h"


/** @def Result codes
 */
#define PLC_APP_DO_OK            0  //OK
#define PLC_APP_DO_ERR_DON       1  //invalid channel number
#define PLC_APP_DO_ERR_M         2  //invalid mode
#define PLC_APP_DO_ERR_NOT_NORM  2  //the channel is not Normal
#define PLC_APP_DO_ERR_NOT_FAST  2  //the channel is not Fast
#define PLC_APP_DO_ERR_NOT_PWM   2  //the channel is not PWM


/** @brief DOMode.
 *  @param DOn  - channel number:
 *  @arg      = 0..7
 *  @param M - mode (see di.h).
 *  @param Om - set mode
 *  @param Ok - result code
 *  @return None.
 */
void PlcApp_DOMode(BYTE *DOn, BYTE *M, BYTE *Om, BYTE *Ok);

/** @brief DONorm.
 *  @param DOn  - channel number:
 *  @arg      = 0..7
 *  @param V  - output level:
 *  @arg      = 0
 *  @arg      = 1
 *  @param Ov - normal value
 *  @param Ok - result code
 *  @return None.
 */
void PlcApp_DONorm(BYTE *DOn, BOOL *V, BOOL *Ov, BYTE *Ok);

/** @brief DOFast.
 *  @param DOn  - channel number:
 *  @arg      = 0..7
 *  @param V  - output level:
 *  @arg      = 0
 *  @arg      = 1
 *  @param Ov - normal value
 *  @param Ok - result code
 *  @return None.
 */
void PlcApp_DOFast(BYTE *DOn, BOOL *V, BOOL *Ov, BYTE *Ok);

/** @brief DOPwm.
 *  @param En - PWM state:
 *  @arg      = false - off
 *  @arg      = true  - on
 *  @param DOn  - channel number:
 *  @arg      = 0..7
 *  @param Tm  - period (ms):
 *  @arg      = 100..4294967295
 *  @param D  - fill factor (%):
 *  @arg      = 0.0..100.0
 *  @param Ow - PWM state
 *  @param Ok - result code
 *  @return None.
 */
void PlcApp_DOPwm(BOOL *En, BYTE *DOn, REAL *Tm, REAL *D, BOOL *Ow, BYTE *Ok);

#endif //APP_DO_H
