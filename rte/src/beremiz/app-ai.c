/* @page app-ai.c
 *       PLC411::RTE
 *       BEREMIZ YAPLC AI System Functions (relationship of RTE with APP)
 *       2020-2023, atgroup09@gmail.com
 */

#include "app-ai.h"


void PlcApp_AIMode(BYTE *AIn, BYTE *M, BYTE *Om, BYTE *Os, BYTE *Ok)
{
    if(AIn && M && Om && Os && Ok)
    {
    	if(*AIn < PLC_AI_SZ)
    	{
            //LOCK
            xSemaphoreTake(RTOS_MBTABLES_MTX, portMAX_DELAY);

            uint8_t M_Current;
            REG_CopyRegByPos((REG_AI_MODE__POS+(*AIn)), REG_COPY_MB_TO_VAR, &M_Current);

            if(*M != M_Current)
            {
                if(*M == PLC_AI_MODE_OFF || *M == PLC_AI_MODE_SURVEY || *M == PLC_AI_MODE_SURVEY_TMP36 || *M == PLC_AI_MODE_SURVEY_TMP_MCU)
                {
                    if(REG_CopyRegByPos((REG_AI_MODE__POS+(*AIn)), REG_COPY_VAR_TO_MB, M))
                    {
                    	*Om = *M;
                    	*Os = *M;
                    }
                    *Ok = PLC_APP_AI_OK;
                }
                else
                {
                    *Ok = PLC_APP_AI_ERR_MODE;
                }
            }

            xSemaphoreGive(RTOS_MBTABLES_MTX);
            //UNLOCK
    	}
        else
        {
            *Ok = PLC_APP_AI_ERR_CH;
        }
    }
}

void PlcApp_AINorm(BYTE *AIn, REAL *Ov, BYTE *Os, BYTE *Ok)
{
    if(AIn && Ov && Os && Ok)
    {
    	if(*AIn < PLC_AI_SZ)
    	{
            //LOCK
            xSemaphoreTake(RTOS_MBTABLES_MTX, portMAX_DELAY);

            uint8_t M_Current;
            REG_CopyRegByPos((REG_AI_MODE__POS+(*AIn)), REG_COPY_MB_TO_VAR, &M_Current);

            if(M_Current == PLC_AI_MODE_SURVEY || M_Current == PLC_AI_MODE_SURVEY_TMP36 || M_Current == PLC_AI_MODE_SURVEY_TMP_MCU)
            {
                //read current values
                REG_CopyRegByPos((REG_AI_VAL__POS+(*AIn)), REG_COPY_MB_TO_VAR, Ov);
                REG_CopyRegByPos((REG_AI_STATUS__POS+(*AIn)), REG_COPY_MB_TO_VAR, Os);
                *Ok  = PLC_APP_AI_OK;
            }
            else
            {
                *Ok = PLC_APP_AI_ERR_NOT_NORM;
            }

            xSemaphoreGive(RTOS_MBTABLES_MTX);
            //UNLOCK
    	}
        else
        {
            *Ok = PLC_APP_AI_ERR_CH;
        }
    }
}
