/* @page plc_glue_rte.h
 *       PLC RTE Merge ABI
 *       from YAPLS
 *       2020
 */

#ifndef PLC_GLUE_RTE_H_
#define PLC_GLUE_RTE_H_

#include <stdbool.h>
#include "plc_abi.h"
#include "plc_app.h"
#include "plc_tick.h"
#include "plc_rtc.h"
#include "plc_backup.h"


bool plc_app_is_valid(void);
void plc_app_cstratup(void);


#endif // PLC_GLUE_RTE_H_
