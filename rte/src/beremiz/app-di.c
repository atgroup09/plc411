/* @page app-di.c
 *       PLC411::RTE
 *       BEREMIZ YAPLC DI System Functions (relationship of RTE with APP)
 *       2020-2023, atgroup09@gmail.com
 */

#include "app-di.h"


void PlcApp_DIMode(BYTE *DIn, BYTE *M, BYTE *Om, BYTE *Ok)
{
    if(DIn && M && Om && Ok)
    {
    	if(*DIn < PLC_DI_SZ && !(PLC_DI_IS_PHASE_B(*DIn) && *M > PLC_DI_MODE_TACH))
    	{
        	//LOCK
        	xSemaphoreTake(RTOS_MBTABLES_MTX, portMAX_DELAY);

        	uint8_t M_Current;
        	REG_CopyRegByPos((REG_DI_MODE__POS+(*DIn)), REG_COPY_MB_TO_VAR, &M_Current);

        	if(*M != M_Current)
        	{
        		if(!(PLC_DI_IS_PHASE_B(*DIn) && *M > PLC_DI_MODE_TACH))
        		{
        			if(*M <= PLC_DI_MODE_INC2)
        			{
        				if(REG_CopyRegByPos((REG_DI_MODE__POS+(*DIn)), REG_COPY_VAR_TO_MB, M))
        				{
        					*Om = *M;
        				}
        				*Ok = PLC_APP_DI_OK;
        			}
        			else
        			{
        				*Ok = PLC_APP_DI_ERR_M;
        			}
        		}
        		else
        		{
        			*Ok = PLC_APP_DI_ERR_INC;
        		}
        	}

        	xSemaphoreGive(RTOS_MBTABLES_MTX);
        	//UNLOCK
    	}
    	else
    	{
    		*Ok = PLC_APP_DI_ERR_DIN;
    	}
    }
}

void PlcApp_DINorm(BYTE *DIn, BOOL *Ov, BYTE *Ok)
{
    if(DIn && Ov && Ok)
    {
        if(*DIn < PLC_DI_SZ)
        {
            //LOCK
            xSemaphoreTake(RTOS_MBTABLES_MTX, portMAX_DELAY);

            uint8_t M_Current;
            REG_CopyRegByPos((REG_DI_MODE__POS+(*DIn)), REG_COPY_MB_TO_VAR, &M_Current);

            if(M_Current == PLC_DI_MODE_NORM)
            {
                REG_CopyRegByPos((REG_DI_NORM_VAL__POS+(*DIn)), REG_COPY_MB_TO_VAR, Ov);
                *Ok = PLC_APP_DI_OK;
            }
            else
            {
                *Ok = PLC_APP_DI_ERR_NOT_NORM;
            }

            xSemaphoreGive(RTOS_MBTABLES_MTX);
            //UNLOCK
        }
        else
        {
            *Ok = PLC_APP_DI_ERR_DIN;
        }
    }
}

void PlcApp_DITach(BYTE *DIn, WORD *Ref, BOOL *RefEn, WORD *Ov, BOOL *Oref, BYTE *Ok)
{
    if(DIn && Ref && RefEn && Ov && Oref && Ok)
    {
        if(*DIn < PLC_DI_SZ)
        {
            //LOCK
            xSemaphoreTake(RTOS_MBTABLES_MTX, portMAX_DELAY);

            uint8_t M_Current;
            REG_CopyRegByPos((REG_DI_MODE__POS+(*DIn)), REG_COPY_MB_TO_VAR, &M_Current);

            if(M_Current == PLC_DI_MODE_TACH)
            {
                REG_CopyRegByPos((REG_DI_TACH_SETPOINT__POS+(*DIn)), REG_COPY_VAR_TO_MB, Ref);
                REG_CopyRegByPos((REG_DI_TACH_SETPOINT_ALLOW__POS+(*DIn)), REG_COPY_VAR_TO_MB, RefEn);
                REG_CopyRegByPos((REG_DI_TACH_VAL__POS+(*DIn)), REG_COPY_MB_TO_VAR, Ov);
                REG_CopyRegByPos((REG_DI_TACH_SETPOINT__POS+(*DIn)), REG_COPY_MB_TO_VAR, Oref);
                *Ok = PLC_APP_DI_OK;
            }
            else
            {
                *Ok = PLC_APP_DI_ERR_NOT_TACH;
            }

            xSemaphoreGive(RTOS_MBTABLES_MTX);
            //UNLOCK
        }
        else
        {
            *Ok = PLC_APP_DI_ERR_DIN;
        }
    }
}

void PlcApp_DICntr(BYTE *DIn, DWORD *Ref, BOOL *RefEn, DWORD *Ov, BOOL *Oref, BYTE *Ok)
{
    if(DIn && Ref && RefEn && Ov && Oref && Ok)
    {
        if(*DIn < PLC_DI_SZ)
        {
            //LOCK
            xSemaphoreTake(RTOS_MBTABLES_MTX, portMAX_DELAY);

            uint8_t M_Current;
            REG_CopyRegByPos((REG_DI_MODE__POS+(*DIn)), REG_COPY_MB_TO_VAR, &M_Current);

            if(M_Current == PLC_DI_MODE_CNTR)
            {
                REG_CopyRegByPos((REG_DI_CNTR_SETPOINT__POS+(*DIn)), REG_COPY_VAR_TO_MB, Ref);
                REG_CopyRegByPos((REG_DI_CNTR_SETPOINT_ALLOW__POS+(*DIn)), REG_COPY_VAR_TO_MB, RefEn);
                REG_CopyRegByPos((REG_DI_CNTR_VAL__POS+(*DIn)), REG_COPY_MB_TO_VAR, Ov);
                REG_CopyRegByPos((REG_DI_CNTR_SETPOINT__POS+(*DIn)), REG_COPY_MB_TO_VAR, Oref);
                *Ok = PLC_APP_DI_OK;
            }
            else
            {
                *Ok = PLC_APP_DI_ERR_NOT_CNTR;
            }

            xSemaphoreGive(RTOS_MBTABLES_MTX);
            //UNLOCK
        }
        else
        {
            *Ok = PLC_APP_DI_ERR_DIN;
        }
    }
}

void PlcApp_DICntrRst(BYTE *DIn, BOOL *Rst, BYTE *Ok)
{
    if(DIn && Rst && Ok)
    {
        if(*DIn < PLC_DI_SZ)
        {
            //LOCK
            xSemaphoreTake(RTOS_MBTABLES_MTX, portMAX_DELAY);

            uint8_t M_Current;
            REG_CopyRegByPos((REG_DI_MODE__POS+(*DIn)), REG_COPY_MB_TO_VAR, &M_Current);

            if(M_Current == PLC_DI_MODE_CNTR || M_Current == PLC_DI_MODE_TACH || M_Current == PLC_DI_MODE_INC1 || M_Current == PLC_DI_MODE_INC2)
            {
                REG_CopyRegByPos((REG_DI_RESET__POS+(*DIn)), REG_COPY_VAR_TO_MB, Rst);
                *Ok = PLC_APP_DI_OK;
            }
            else
            {
                *Ok = PLC_APP_DI_ERR_NOT_CNTR;
            }

            xSemaphoreGive(RTOS_MBTABLES_MTX);
            //UNLOCK
        }
        else
        {
            *Ok = PLC_APP_DI_ERR_DIN;
        }
    }
}

void PlcApp_DIEnc(BYTE *DIn, DWORD *RefA, BOOL *RefAEn, DWORD *RefB, BOOL *RefBEn, WORD *RefT, BOOL *RefTEn, DWORD *OutA, BOOL *OAref, DWORD *OutB, BOOL *OBref, WORD *OutT, BOOL *OTref, BYTE *Ok)
{
    if(DIn && RefA && RefAEn && RefB && RefBEn && RefT && RefTEn && OutA && OAref && OutB && OBref && OutT && OTref && Ok)
    {
        if(PLC_DI_IS_PHASE_A(*DIn))
        {
            //LOCK
            xSemaphoreTake(RTOS_MBTABLES_MTX, portMAX_DELAY);

            uint8_t M_Current;
            REG_CopyRegByPos((REG_DI_MODE__POS+(*DIn)), REG_COPY_MB_TO_VAR, &M_Current);

            if(M_Current > PLC_DI_MODE_TACH)
            {
                uint16_t ChB = ((*DIn)+1);
                // phase A counter
                REG_CopyRegByPos((REG_DI_CNTR_SETPOINT__POS+(*DIn)), REG_COPY_VAR_TO_MB, RefA);
                REG_CopyRegByPos((REG_DI_CNTR_SETPOINT_ALLOW__POS+(*DIn)), REG_COPY_VAR_TO_MB, RefAEn);
                REG_CopyRegByPos((REG_DI_CNTR_VAL__POS+(*DIn)), REG_COPY_MB_TO_VAR, OutA);
                REG_CopyRegByPos((REG_DI_CNTR_SETPOINT__POS+(*DIn)), REG_COPY_MB_TO_VAR, OAref);
                // phase B counter
                REG_CopyRegByPos((REG_DI_CNTR_SETPOINT__POS+ChB), REG_COPY_VAR_TO_MB, RefB);
                REG_CopyRegByPos((REG_DI_CNTR_SETPOINT_ALLOW__POS+ChB), REG_COPY_VAR_TO_MB, RefBEn);
                REG_CopyRegByPos((REG_DI_CNTR_VAL__POS+ChB), REG_COPY_MB_TO_VAR, OutB);
                REG_CopyRegByPos((REG_DI_CNTR_SETPOINT__POS+ChB), REG_COPY_MB_TO_VAR, OBref);
                // phase B tachometer
                REG_CopyRegByPos((REG_DI_TACH_SETPOINT__POS+ChB), REG_COPY_VAR_TO_MB, RefT);
                REG_CopyRegByPos((REG_DI_TACH_SETPOINT_ALLOW__POS+ChB), REG_COPY_VAR_TO_MB, RefTEn);
                REG_CopyRegByPos((REG_DI_TACH_VAL__POS+ChB), REG_COPY_MB_TO_VAR, OutT);
                REG_CopyRegByPos((REG_DI_TACH_SETPOINT__POS+ChB), REG_COPY_MB_TO_VAR, OTref);
                *Ok = PLC_APP_DI_OK;
            }
            else
            {
                *Ok = PLC_APP_DI_ERR_NOT_CNTR;
            }

            xSemaphoreGive(RTOS_MBTABLES_MTX);
            //UNLOCK
        }
        else
        {
            *Ok = PLC_APP_DI_ERR_DIN;
        }
    }
}
