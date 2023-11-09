/* @page plc_app.c
 *       PLC411::RTE
 *       BEREMIZ YAPLC Application ABI (relationship of RTE with APP)
 *       2020-2023, atgroup09@gmail.com
 */

#include "plc_app.h"


/** @var Application ABI-structure
 */
plc_app_abi_t *PLC_APP_CURR = 0;

/** @var Application state
 */
uint8_t PLC_APP_STATE = PLC_APP_STATE_STOPED;

/** @var Debug messages
 */
const char plc_start_msg[]   = "Application is started.";
const char plc_app_err_msg[] = "Application is not valid.";


/** @brief  Init. Application ABI-structure
 *  @param  None.
 *  @return Result:
 *  @arg     = 0 - application is not loaded (not valid)
 *  @arg     = 1 - loaded (valid)
 */
uint8_t PlcApp_Init(void)
{
    if(plc_app_is_valid())
    {
        plc_app_cstratup();

        PLC_APP_CURR = (plc_app_abi_t *)PLC_APP;
        //PLC_APP_CURR->log_msg_post(LOG_DEBUG, (char *)plc_start_msg, sizeof(plc_start_msg));

#ifdef DEBUG_LOG_APP
        DebugLog("APP ABI [INITED] [%d %d.%d.%d]\n", PLC_APP_CURR->hw_id, PLC_APP_CURR->rte_ver_major, PLC_APP_CURR->rte_ver_minor, PLC_APP_CURR->rte_ver_patch);
#endif //DEBUG_LOG_APP

        return (BIT_TRUE);
    }

    return (BIT_FALSE);
}

/** @brief  Start Application.
 *  @param  None.
 *  @return None.
 */
void PlcApp_Start(void)
{
    if(PLC_APP_CURR)
    {
        PLC_APP_CURR->start(0, 0);
        PLC_APP_STATE = PLC_APP_STATE_STARTED;
    }
}

/** @brief  Stop Application.
 *  @param  None.
 *  @return None.
 */
void PlcApp_Stop(void)
{
    if(PLC_APP_CURR)
    {
        PLC_APP_STATE = PLC_APP_STATE_STOPED;
        PLC_APP_CURR->stop();
    }
}

/** @brief  Run Application.
 *  @param  None.
 *  @return None.
 */
void PlcApp_Run(void)
{
    if(PLC_APP_CURR)
    {
        PLC_APP_CURR->run();
    }
}


/** @brief  Test Located variable.
 *  @param  ZoneIn   - ID of zone           (plc_app.v_type).
 *  @param  TypeSzIn - ID of data type size (plc_app.v_size).
 *  @param  GroupIn  - ID of group          (plc_app.proto).
 *  @param  A00In    - ID of subgroup 0     (plc_app.a_data[0]) (<0 is not used).
 *  @param  A01In    - ID of subgroup 1     (plc_app.a_data[1]) (<0 is not used).
 *  @param  A02In    - ID of subgroup 2     (plc_app.a_data[2]) (<0 is not used).
 *  @return Pointer to located variable structure or 0 (if located variable is not supported)
 */
plc_loc_dsc_t *PlcApp_TestLocVar(const uint8_t ZoneIn, const uint8_t TypeSzIn, const uint16_t GroupIn, const int32_t A00In, const int32_t A01In, const int32_t A02In)
{
    plc_loc_dsc_t *Res = 0;
    uint16_t iVar;

    if(PLC_APP_CURR)
    {
        if(PLC_APP_CURR->l_tab && PLC_APP_CURR->l_sz > 0)
        {
            for(iVar=0; iVar<PLC_APP_CURR->l_sz; iVar++)
            {
                //test by:
                //  Zone   (l_tab[iVar].v_type)
                //  TypeSz (l_tab[iVar].v_size)
                //  Group  (l_tab[iVar].proto)
                //  v_buf
                if(PLC_APP_CURR->l_tab[iVar]->v_type == ZoneIn && PLC_APP_CURR->l_tab[iVar]->v_size == TypeSzIn && PLC_APP_CURR->l_tab[iVar]->proto == GroupIn && PLC_APP_CURR->l_tab[iVar]->v_buf)
                {
                    //test by:
                    //  A00 (l_tab[iVar]->a_data[0])
                    //  A01 (l_tab[iVar]->a_data[1])
                    //  A02 (l_tab[iVar]->a_data[2])
                    if(A00In >= 0 && PLC_APP_CURR->l_tab[iVar]->a_size >= 1)
                    {
                        if(PLC_APP_CURR->l_tab[iVar]->a_data[0] != (uint32_t)A00In) continue;
                    }

                    if(A01In >= 0 && PLC_APP_CURR->l_tab[iVar]->a_size >= 2)
                    {
                        if(PLC_APP_CURR->l_tab[iVar]->a_data[1] != (uint32_t)A01In) continue;
                    }

                    if(A02In >= 0 && PLC_APP_CURR->l_tab[iVar]->a_size >= 3)
                    {
                        if(PLC_APP_CURR->l_tab[iVar]->a_data[2] != (uint32_t)A02In) continue;
                    }

                    Res = (plc_loc_dsc_t *)PLC_APP_CURR->l_tab[iVar];
                    break;
                }
            }
        }
    }

    return (Res);
}


#ifdef DEBUG_LOG_APP_VAR

/** @brief  Debug print of PLC_APP item.
 *  @param  None.
 *  @return None.
 */
void PlcApp_DebugPrintItem(plc_loc_dsc_t *pAppVarIn)
{
    if(pAppVarIn)
    {
        char ty[3]  = {'I', 'M', 'Q'};
        char sz[5] = {'X', 'B', 'W', 'D', 'L'};
        uint16_t j, a;

        if(pAppVarIn->v_type < 3 && pAppVarIn->v_size < 5)
        {
            DebugLog("%c%c%d\0", ty[pAppVarIn->v_type], sz[pAppVarIn->v_size], pAppVarIn->proto);

            if(pAppVarIn->a_size > 0)
            {
                a = pAppVarIn->a_size;

                for(j=0; j<a; j++)
                {
                    DebugLog("_%d\0", pAppVarIn->a_data[j]);
                }
            }

            switch(pAppVarIn->v_size)
            {
                case PLC_LSZ_X:
                    DebugLog("=%d\n", (*(IEC_BOOL *)(pAppVarIn->v_buf)));
                    break;
                case PLC_LSZ_B:
                    DebugLog("=%d\n", (*(IEC_BYTE *)(pAppVarIn->v_buf)));
                    break;
                case PLC_LSZ_W:
                    DebugLog("=%d\n", (*(IEC_WORD *)(pAppVarIn->v_buf)));
                    break;
                case PLC_LSZ_D:
                    DebugLog("=%d\n", (IEC_WORD)(*(IEC_DWORD *)(pAppVarIn->v_buf)));
                    break;
                default:
                    DebugLog("\n");
            }
        }
    }
}


/** @brief  Debug print of PLC_APP_CURR->l_tab[i].
 *  @param  None.
 *  @return None.
 */
void PlcApp_DebugPrint(void)
{
    if(PLC_APP_CURR)
    {
        if(PLC_APP_CURR->l_tab && PLC_APP_CURR->l_sz > 0)
        {
            uint16_t i;
            for(i=0; i<PLC_APP_CURR->l_sz; i++)
            {
                PlcApp_DebugPrintItem((plc_loc_dsc_t *)PLC_APP_CURR->l_tab[i]);
            }
            DebugLog("---\n");
        }
    }
}

#endif //DEBUG_LOG_APP_VAR
