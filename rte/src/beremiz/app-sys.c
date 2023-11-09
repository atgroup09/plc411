/* @page app-sys.c
 *       PLC411::RTE
 *       BEREMIZ YAPLC System Functions (relationship of RTE with APP)
 *       2020-2023, atgroup09@gmail.com
 */

#include "app-sys.h"


void PlcApp_SoftwareReset(BOOL Ex)
{
    if(Ex) Plc_SoftwareReset();
}

void PlcApp_GetTime(IEC_TIME *CurrentTimeIn)
{
    if(CurrentTimeIn)
    {
        //1 tick of plc_sys_timer == 1 msec
    	uint32_t plc_sys_timer = HAL_GetTick();

        //part of seconds from plc_sys_timer
        CurrentTimeIn->tv_sec  = (long int)(plc_sys_timer/1000);
        //part of nanoseconds from plc_sys_timer
        CurrentTimeIn->tv_nsec = (long int)((plc_sys_timer-(CurrentTimeIn->tv_sec*1000))*1000000);
    }
}

void PlcApp_LedUser(BOOL *V, BOOL *Ov)
{
    if(V && Ov)
    {
    	//LOCK
    	xSemaphoreTake(RTOS_MBTABLES_MTX, portMAX_DELAY);

    	if(REG_CopyRegByPos(REG_SYS_CMD__POS_LED_USER, REG_COPY_VAR_TO_MB, V))
    	{
    		*Ov = *V;
    	}

    	xSemaphoreGive(RTOS_MBTABLES_MTX);
    	//UNLOCK
    }
}
