/* @page debug-log.c
 *       PLC411::RTE
 *       DebugLog
 *       2022-2023, atgroup09@gmail.com
 */

#include "debug-log.h"


/** @var Process Locker
 */
volatile uint8_t DEBUG_LOG_LOCK = BIT_FALSE;

/** @brief  Wait for Process is unlocked
 *  @param  None.
 *  @return None.
 */
void DebugLog_Wait(void)
{
	while(DEBUG_LOG_LOCK);
}


/** @var Local buffer
 */
#ifdef DEBUG
static char DEBUG_LOG_BUFF[DEBUG_LOG_BUFF_SZ];

/** @brief  Lock Process
 *  @param  None.
 *  @return None.
 */
static inline void DebugLog_Lock(void)
{
	DEBUG_LOG_LOCK = BIT_TRUE;
}

/** @brief  UnLock Process
 *  @param  None.
 *  @return None.
 */
static inline void DebugLog_UnLock(void)
{
	DEBUG_LOG_LOCK = BIT_FALSE;
}

#endif // DEBUG

/** @brief  DebugLog init.
 *  @param  None.
 *  @return None.
 */
void DebugLog_Init(void)
{
#if (DEBUG_LOG_DST == DEBUG_LOG_DST_SWD)
	PlcSwd_Init();
#endif
}

/** @brief  DebugLog user-side function.
 *  @param  FmtIn - pointer to string with format specificators.
 *  @param  ... - arguments of format specificators.
 *  @return None.
 *  @note   !!! DON'T EXECUTE FROM IRQ !!!
 */
void DebugLog(const char *FmtIn, ...)
{
#ifdef DEBUG
    if(FmtIn)
    {
    	DebugLog_Wait();
    	DebugLog_Lock();

        va_list arp;
        va_start(arp, FmtIn);
        xsprintfa(DEBUG_LOG_BUFF, FmtIn, arp);

#if (DEBUG_LOG_DST == DEBUG_LOG_DST_SWD)
        PlcSwd_PrintStr(DEBUG_LOG_BUFF, strlen(DEBUG_LOG_BUFF));
        DebugLog_UnLock();
#endif
        va_end(arp);
    }

#else
    (void)FmtIn;
#endif // DEBUG
}
