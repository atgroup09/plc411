/* @page app.h
 *       PLC411::RTE
 *       BEREMIZ YAPLC System Functions (relationship of RTE with APP)
 *       2020-2023, atgroup09@gmail.com
 */

#ifndef APP_H
#define APP_H

#include <stdint.h>
#include "config.h"
#include "plc_app.h"

#ifdef RTE_MOD_DI
#include "app-di.h"
#endif //RTE_MOD_DI

#ifdef RTE_MOD_DO
#include "app-do.h"
#endif //RTE_MOD_DO

#ifdef RTE_MOD_AI
#include "app-ai.h"
#endif //RTE_MOD_AI

#include "app-sys.h"


/** @brief  Init. System Functions.
 *  @param  None.
 *  @return None.
 */
void PlcApp_InitSysFunc(void);

#endif //APP_H
