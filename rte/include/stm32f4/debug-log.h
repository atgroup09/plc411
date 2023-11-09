/* @page debug-log.h
 *       PLC411::RTE
 *       DebugLog
 *       2022-2023, atgroup09@gmail.com
 */


/** @note
 *        Debug log out:
 *        + SWD/SWO
 */

#ifndef RTOS_TASK_LOG_H
#define RTOS_TASK_LOG_H

#include "xprintf.h"
#include "config.h"

#if (DEBUG_LOG_DST == DEBUG_LOG_DST_SWD)
#include "swd.h"
#endif


/** @def Size of local buffer
 */
#define DEBUG_LOG_BUFF_SZ  250


/** @brief  Wait for Process is unlocked
 *  @param  None.
 *  @return None.
 */
void DebugLog_Wait(void);

/** @brief  DebugLog init.
 *  @param  None.
 *  @return None.
 */
void DebugLog_Init(void);

/** @brief  DebugLog user-side function.
 *  @param  FmtIn - pointer to string with format specificators.
 *  @param  ...   - arguments of format specificators.
 *  @return None.
 *  @note   !!! DON'T EXECUTE FROM IRQ !!!
 */
void DebugLog(const char *FmtIn, ...);


#endif //RTOS_TASK_LOG_H
