/* @page error.c
 *       PLC411::RTE
 *       Error handler
 *       2022, atgroup09@gmail.com
 */

#include "error.h"


/** @brief  This function is executed in case of error occurrence.
 *  @param  FileIn - file name.
 *  @param  LineIn - line in file.
 *  @retval None.
 */
void _Error_Handler(const char *FileIn, int LineIn)
{
#ifdef DEBUG_LOG_ERROR
	if(FileIn)
		 DebugLog("ERROR IN %s:%d\n", FileIn, LineIn);
	else DebugLog("ERROR\n");
	DebugLog_Wait();
#else
	(void)FileIn;
	(void)LineIn;
#endif //DEBUG_LOG_ERROR

	__disable_irq();

	while(1)
	{
	}
}
