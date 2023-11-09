/* @page app.h
 *       PLC411::RTE
 *       BEREMIZ YAPLC System Functions (relationship of RTE with APP)
 *       2020-2023, atgroup09@gmail.com
 */

#include "app.h"


/** @brief  Init. System Functions.
 *  @param  None.
 *  @return None.
 */
void PlcApp_InitSysFunc(void)
{
    if(PLC_APP_CURR)
    {
        if(PLC_APP_CURR->funcs)
        {
#ifdef RTE_MOD_DI
            PLC_APP_CURR->funcs->DIMode    = PlcApp_DIMode;
            PLC_APP_CURR->funcs->DINorm    = PlcApp_DINorm;
            PLC_APP_CURR->funcs->DITach    = PlcApp_DITach;
            PLC_APP_CURR->funcs->DICntr    = PlcApp_DICntr;
            PLC_APP_CURR->funcs->DICntrRst = PlcApp_DICntrRst;
            PLC_APP_CURR->funcs->DIEnc     = PlcApp_DIEnc;
#endif //RTE_MOD_DI

#ifdef RTE_MOD_DO
            PLC_APP_CURR->funcs->DOMode    = PlcApp_DOMode;
            PLC_APP_CURR->funcs->DONorm    = PlcApp_DONorm;
            PLC_APP_CURR->funcs->DOFast    = PlcApp_DOFast;
            PLC_APP_CURR->funcs->DOPwm     = PlcApp_DOPwm;
#endif //RTE_MOD_DO

#ifdef RTE_MOD_AI
            PLC_APP_CURR->funcs->AIMode    = PlcApp_AIMode;
            PLC_APP_CURR->funcs->AINorm    = PlcApp_AINorm;
#endif //RTE_MOD_AI

            PLC_APP_CURR->funcs->SoftReset = PlcApp_SoftwareReset;
            PLC_APP_CURR->funcs->GetTime   = PlcApp_GetTime;
            PLC_APP_CURR->funcs->LedUser   = PlcApp_LedUser;
        }
    }
}
