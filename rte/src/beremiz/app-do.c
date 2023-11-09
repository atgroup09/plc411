/* @page app-do.c
 *       PLC411::RTE
 *       BEREMIZ YAPLC DO System Functions (relationship of RTE with APP)
 *       2020-2023, atgroup09@gmail.com
 */

#include "app-do.h"


void PlcApp_DOMode(BYTE *DOn, BYTE *M, BYTE *Om, BYTE *Ok)
{
    if(DOn && M && Om && Ok)
    {
    	if(*DOn < PLC_DO_SZ)
    	{
            //LOCK
            xSemaphoreTake(RTOS_MBTABLES_MTX, portMAX_DELAY);

            uint8_t M_Current;
            REG_CopyRegByPos((REG_DO_MODE__POS+(*DOn)), REG_COPY_MB_TO_VAR, &M_Current);

            if(*M != M_Current)
            {
                if(*M == PLC_DO_MODE_OFF || *M == PLC_DO_MODE_NORM || *M == PLC_DO_MODE_FAST || *M == PLC_DO_MODE_PWM)
                {
                    if(REG_CopyRegByPos((REG_DO_MODE__POS+(*DOn)), REG_COPY_VAR_TO_MB, M))
                    {
                        *Om = *M;
                    }
                    *Ok = PLC_APP_DO_OK;
                }
                else
                {
                    *Ok = PLC_APP_DO_ERR_M;
                }
            }

            xSemaphoreGive(RTOS_MBTABLES_MTX);
            //UNLOCK
    	}
        else
        {
            *Ok = PLC_APP_DO_ERR_DON;
        }
    }
}

void PlcApp_DONorm(BYTE *DOn, BOOL *V, BOOL *Ov, BYTE *Ok)
{
    if(DOn && V && Ov && Ok)
    {
        if(*DOn < PLC_DO_SZ)
        {
            //LOCK
            xSemaphoreTake(RTOS_MBTABLES_MTX, portMAX_DELAY);

            uint8_t M_Current;
            REG_CopyRegByPos((REG_DO_MODE__POS+(*DOn)), REG_COPY_MB_TO_VAR, &M_Current);

            if(M_Current == PLC_DO_MODE_NORM)
            {
            	//set postponed normal value
            	PlcDO_Q_t DO_Q_Data;
            	DO_Q_Data.Ch  = (*DOn);
            	DO_Q_Data.ID  = PLC_DO_Q_ID_POSTPONED_VAL;
            	DO_Q_Data.Val = (float)(float)(*V);
            	xQueueSendToBack(RTOS_DO_Q, &DO_Q_Data, 0);
            	PLC_DO_POSTPONED = BIT_TRUE;

                REG_CopyRegByPos((REG_DO_NORM_VAL__POS+(*DOn)), REG_COPY_VAR_TO_MB__NO_MON, V);

                *Ov = *V;
                *Ok = PLC_APP_DO_OK;
            }
            else
            {
                *Ok = PLC_APP_DO_ERR_NOT_NORM;
            }

            xSemaphoreGive(RTOS_MBTABLES_MTX);
            //UNLOCK
        }
        else
        {
            *Ok = PLC_APP_DO_ERR_DON;
        }
    }
}

void PlcApp_DOFast(BYTE *DOn, BOOL *V, BOOL *Ov, BYTE *Ok)
{
    if(DOn && V && Ov && Ok)
    {
        if(*DOn < PLC_DO_SZ)
        {
            //LOCK
            xSemaphoreTake(RTOS_MBTABLES_MTX, portMAX_DELAY);

            uint8_t M_Current;
            REG_CopyRegByPos((REG_DO_MODE__POS+(*DOn)), REG_COPY_MB_TO_VAR, &M_Current);

            if(M_Current == PLC_DO_MODE_FAST)
            {
                REG_CopyRegByPos((REG_DO_FAST_VAL__POS+(*DOn)), REG_COPY_VAR_TO_MB, V);

                *Ov = *V;
                *Ok = PLC_APP_DO_OK;
            }
            else
            {
                *Ok = PLC_APP_DO_ERR_NOT_FAST;
            }

            xSemaphoreGive(RTOS_MBTABLES_MTX);
            //UNLOCK
        }
        else
        {
            *Ok = PLC_APP_DO_ERR_DON;
        }
    }
}

void PlcApp_DOPwm(BOOL *En, BYTE *DOn, REAL *Tm, REAL *D, BOOL *Ow, BYTE *Ok)
{
    if(En && DOn && Tm && D && Ow && Ok)
    {
        if(*DOn < PLC_DO_SZ)
        {
            //LOCK
            xSemaphoreTake(RTOS_MBTABLES_MTX, portMAX_DELAY);

            uint8_t M_Current;
            REG_CopyRegByPos((REG_DO_MODE__POS+(*DOn)), REG_COPY_MB_TO_VAR, &M_Current);

            if(M_Current == PLC_DO_MODE_PWM)
            {
                if(REG_CopyRegByPos((REG_DO_PWM_ALLOW__POS+(*DOn)), REG_COPY_VAR_TO_MB, En))
                {
                    *Ow = *En;
                }

                REG_CopyRegByPos((REG_DO_PWM_PERIOD__POS+(*DOn)), REG_COPY_VAR_TO_MB, Tm);
                REG_CopyRegByPos((REG_DO_PWM_VAL__POS+(*DOn)), REG_COPY_VAR_TO_MB, D);

                *Ok = PLC_APP_DO_OK;
            }
            else
            {
                *Ok = PLC_APP_DO_ERR_NOT_PWM;
            }

            xSemaphoreGive(RTOS_MBTABLES_MTX);
            //UNLOCK
        }
        else
        {
            *Ok = PLC_APP_DO_ERR_DON;
        }
    }
}
