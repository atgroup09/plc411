/* @page plc_app.h
 *       PLC411::RTE
 *       BEREMIZ YAPLC Application ABI (relationship of RTE with APP)
 *       2020-2023, atgroup09@gmail.com
 */

#ifndef PLC_APP_H
#define PLC_APP_H

#include "config.h"

#include "plc_abi.h"
#include "plc_glue_rte.h"

#ifdef DEBUG
#include "debug-log.h"
#endif // DEBUG


/** @def Pointer to Application ABI-structure
 */
#define PLC_APP                        ((plc_app_abi_t *)0x08040000)

/** @var Pointer to Application ABI-structure
 *       (defined in plc_app.c)
 */
extern plc_app_abi_t *PLC_APP_CURR;


/** @def Version of Application ABI-structure
 */
#define PLC_APP_VER_MAJOR              PLC_RTE_VERSION_MAJOR
#define PLC_APP_VER_MINOR              PLC_RTE_VERSION_MINOR
#define PLC_APP_VER_PATCH              PLC_RTE_VERSION_PATCH
#define PLC_APP_HW_ID                  PLC_HW_CODE

/** @def Application states
 */
#define PLC_APP_STATE_STOPED           0x55
#define PLC_APP_STATE_STARTED          0xAA

/** @var Application state
 */
extern uint8_t PLC_APP_STATE;


/** @brief  Init. Application ABI-structure
 *  @param  None.
 *  @return Result:
 *  @arg     = 0 - application is not loaded (not valid)
 *  @arg     = 1 - loaded (valid)
 */
uint8_t PlcApp_Init(void);

/** @brief  Start Application.
 *  @param  None.
 *  @return None.
 */
void PlcApp_Start(void);

/** @brief  Stop Application.
 *  @param  None.
 *  @return None.
 */
void PlcApp_Stop(void);

/** @brief  Run Application.
 *  @param  None.
 *  @return None.
 */
void PlcApp_Run(void);

/** @brief  Test Located variable.
 *  @param  ZoneIn   - ID of zone           (plc_app.v_type).
 *  @param  TypeSzIn - ID of data type size (plc_app.v_size).
 *  @param  GroupIn  - ID of group          (plc_app.proto).
 *  @param  A00In    - ID of subgroup 0     (plc_app.a_data[0]) (<0 is not used).
 *  @param  A01In    - ID of subgroup 1     (plc_app.a_data[1]) (<0 is not used).
 *  @param  A02In    - ID of subgroup 2     (plc_app.a_data[2]) (<0 is not used).
 *  @return Pointer to located variable structure or 0 (if located variable is not supported)
 */
plc_loc_dsc_t *PlcApp_TestLocVar(const uint8_t ZoneIn, const uint8_t TypeSzIn, const uint16_t GroupIn, const int32_t A00In, const int32_t A01In, const int32_t A02In);


#ifdef DEBUG_LOG_APP_VAR
/** @brief  Debug print of PLC_APP_CURR->l_tab[i].
 *  @param  None.
 *  @return None.
 */
void PlcApp_DebugPrint(void);

/** @brief  Debug print of PLC_APP item.
 *  @param  None.
 *  @return None.
 */
void PlcApp_DebugPrintItem(plc_loc_dsc_t *pAppVarIn);
#endif //DEBUG_LOG_APP_VAR


#endif //PLC_APP_H
