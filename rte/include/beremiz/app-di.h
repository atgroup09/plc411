/* @page app-di.h
 *       PLC411::RTE
 *       BEREMIZ YAPLC DI System Functions (relationship of RTE with APP)
 *       2020-2023, atgroup09@gmail.com
 */

#ifndef APP_DI_H
#define APP_DI_H

#include <stdint.h>
#include "plc_abi.h"
#include "di.h"
#include "reg.h"
#include "rtos.h"


/** @def Result codes
 */
#define PLC_APP_DI_OK            0  //OK
#define PLC_APP_DI_ERR_DIN       1  //invalid channel number
#define PLC_APP_DI_ERR_M         2  //invalid mode
#define PLC_APP_DI_ERR_NOT_NORM  2  //the channel is not Normal
#define PLC_APP_DI_ERR_NOT_TACH  2  //the channel is not Tachometer
#define PLC_APP_DI_ERR_NOT_CNTR  2  //the channel is not Counter
#define PLC_APP_DI_ERR_INC       3  //try to set inc-mode for not Master-channels


/** @brief DIMode.
 *  @param DIn  - channel number:
 *  @arg      = 0..7
 *  @param M - mode (see di.h).
 *  @param Om - set mode
 *  @param Ok - result code
 *  @return None.
 */
void PlcApp_DIMode(BYTE *DIn, BYTE *M, BYTE *Om, BYTE *Ok);

/** @brief DINorm.
 *  @param DIn  - channel number:
 *  @arg      = 0..7
 *  @param Ov - normal value
 *  @param Ok - result code
 *  @return None.
 */
void PlcApp_DINorm(BYTE *DIn, BOOL *Ov, BYTE *Ok);

/** @brief DITach.
 *  @param DIn  - channel number:
 *  @arg      = 0..7
 *  @param Ref - reference
 *  @param RefEn - allow to work by reference
 *  @arg      = false - not allow
 *  @arg      = true  - allow
 *  @param Ov   - tachometer value
 *  @param Oref - reference status
 *  @param Ok   - result code
 *  @return None.
 */
void PlcApp_DITach(BYTE *DIn, WORD *Ref, BOOL *RefEn, WORD *Ov, BOOL *Oref, BYTE *Ok);

/** @brief DICntr.
 *  @param DIn  - channel number:
 *  @arg      = 0..7
 *  @param Ref - reference
 *  @param RefEn - allow to work by reference
 *  @arg      = false - not allow
 *  @arg      = true  - allow
 *  @param Ov   - counter value
 *  @param Oref - reference status
 *  @param Ok   - result code
 *  @return None.
 */
void PlcApp_DICntr(BYTE *DIn, DWORD *Ref, BOOL *RefEn, DWORD *Ov, BOOL *Oref, BYTE *Ok);

/** @brief DICntrRst.
 *  @param DIn  - channel number:
 *  @arg      = 0..7
 *  @param Rst - reset command
 *  @arg      = false - no reset
 *  @arg      = true  - reset
 *  @param Ok - result code
 *  @return None.
 */
void PlcApp_DICntrRst(BYTE *DIn, BOOL *Rst, BYTE *Ok);

/** @brief DIEnc.
 *  @param DIn  - channel number:
 *  @arg      = 0..7
 *  @param RefA - reference of phase A counter
 *  @param RefAEn - allow to work of phase A counter by reference
 *  @arg      = false - not allow
 *  @arg      = true  - allow
 *  @param RefB - reference of phase B counter
 *  @param RefBEn - allow to work of phase B counter by reference
 *  @arg      = false - not allow
 *  @arg      = true  - allow
 *  @param RefT - reference of tachometer
 *  @param RefTEn - allow to work of tachometer by reference
 *  @arg      = false - not allow
 *  @arg      = true  - allow
 *  @param OA - phase A counter value
 *  @param OAref - phase A counter reference status
 *  @param OB - phase B counter value
 *  @param OBref - phase B counter reference status
 *  @param OT - tachometer value
 *  @param OTref - tachometer reference status
 *  @param Ok - result code
 *  @return None.
 */
void PlcApp_DIEnc(BYTE *DIn, DWORD *RefA, BOOL *RefAEn, DWORD *RefB, BOOL *RefBEn, WORD *RefT, BOOL *RefTEn, DWORD *OutA, BOOL *OAref, DWORD *OutB, BOOL *OBref, WORD *OutT, BOOL *OTref, BYTE *Ok);

#endif /* APP_DI_H_ */
