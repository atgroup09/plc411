/* @page app-ai.h
 *       PLC411::RTE
 *       BEREMIZ YAPLC AI System Functions (relationship of RTE with APP)
 *       2020-2023, atgroup09@gmail.com
 */

#ifndef APP_AI_H
#define APP_AI_H

#include <stdint.h>
#include "plc_abi.h"
#include "ai.h"
#include "reg.h"
#include "rtos.h"


/** @def Result codes
 */
#define PLC_APP_AI_OK            0  //OK
#define PLC_APP_AI_ERR_CH        1  //invalid channel number
#define PLC_APP_AI_ERR_MODE      2  //invalid mode
#define PLC_APP_AI_ERR_NOT_NORM  3  //not norm mode


/** @brief AIMode.
 *  @param AIn - channel number.
 *  @param M   - mode (see ai.h).
 *  @param Om  - set mode.
 *  @param Os  - status code.
 *  @param Ok  - result code.
 *  @return None.
 */
void PlcApp_AIMode(BYTE *AIn, BYTE *M, BYTE *Om, BYTE *Os, BYTE *Ok);

/** @brief AINorm.
 *  @param AIn - channel number.
 *  @param Ov  - value.
 *  @param Os  - status code.
 *  @param Ok  - result code.
 *  @return None.
 */
void PlcApp_AINorm(BYTE *AIn, REAL *Ov, BYTE *Os, BYTE *Ok);

#endif //APP_AI_H
