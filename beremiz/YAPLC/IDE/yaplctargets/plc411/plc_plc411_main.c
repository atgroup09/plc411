/* @page plc_plc411_main.c
 *       PLC411 (YAPLC), additional code
 *       platform-dependent code
 *       2020-2023
 *       1.0.0
 */

/**
 * Newlib stubs.
 **/

#include <sys/stat.h>

int _close(int file)
{
    (void)file;
    return -1;
}

int _fstat(int file, struct stat *st)
{
    (void)file;
    st->st_mode = S_IFCHR;
    return 0;
}

int _isatty(int file)
{
    (void)file;
    return 1;
}

int _lseek(int file, int ptr, int dir)
{
    (void)file;
    (void)ptr;
    (void)dir;
    return 0;
}

int _open(const char *name, int flags, int mode)
{
    (void)name;
    (void)flags;
    (void)mode;
    return -1;
}

int _read(int file, char *ptr, int len)
{
    (void)file;
    (void)ptr;
    (void)len;
    return 0;
}

char *heap_end = 0;
caddr_t _sbrk(int incr)
{
    (void)incr;
    return (caddr_t) 0;
}

int _write(int file, char *ptr, int len)
{
    (void)file;
    (void)ptr;
    (void)len;
    return 0;
}

/**
 * YAPLC specific code.
 **/

#include <string.h>
#include <iec_std_lib.h>
#include <plc_abi.h>

/**
 * YAPLC ABI.
 **/

void fake_start(void)
{
    while(1);
}

/*!< TODO: добавть специальную секцию для
type * name = &(PLC_LOC_BUF(name));
Чтобы можно было разместть их во flash-памяти.
*/

/* LOCATED_VARIABLES
 * global variables
 */

#define PLC_LOC_BUF(name)  PLC_LOC_CONCAT(name, _BUF)
#define PLC_LOC_ADDR(name) PLC_LOC_CONCAT(name, _ADDR)
#define PLC_LOC_DSC(name)  PLC_LOC_CONCAT(name, _LDSC)

#define __LOCATED_VAR( type, name, lt, lsz, io_proto, ... ) \
type PLC_LOC_BUF(name);                                     \
type * name = &(PLC_LOC_BUF(name));                         \
const uint32_t PLC_LOC_ADDR(name)[] = {__VA_ARGS__};        \
const plc_loc_dsc_t PLC_LOC_DSC(name) =                     \
    {                                                       \
     .v_buf  = (void *)&(PLC_LOC_BUF(name)),                \
     .v_type = PLC_LOC_TYPE(lt),                            \
     .v_size = PLC_LOC_SIZE(lsz),                           \
     .a_size = sizeof(PLC_LOC_ADDR(name))/sizeof(uint32_t), \
     .a_data = &(PLC_LOC_ADDR(name)[0]),                    \
     .proto  = io_proto                                     \
    };

#include "LOCATED_VARIABLES.h"
#undef __LOCATED_VAR


/** LOCATED VARIABLES
 */

#define __LOCATED_VAR(type, name, ...) &(PLC_LOC_DSC(name)),
plc_loc_tbl_t plc_loc_table[] =
{
#include "LOCATED_VARIABLES.h"
};
#undef __LOCATED_VAR

#define PLC_LOC_TBL_SIZE (sizeof(plc_loc_table)/sizeof(plc_loc_dsc_t *))
uint32_t plc_loc_weigth[PLC_LOC_TBL_SIZE];


/** LOCATED FUNCTIONS
 */

plc_app_funcs_t PlcAppFuncs = 
{
    .DIMode     = 0,
    .DINorm     = 0,
    .DITach     = 0,
    .DICntr     = 0,
    .DICntrRst  = 0,
    .DIEnc      = 0,

    .DOMode     = 0,
    .DONorm     = 0,
    .DOFast     = 0,
    .DOPwm      = 0,
    
    .AIMode     = 0,
    .AINorm     = 0,
    
    .SoftReset  = 0,
    .GetTime    = 0,
    .LedUser    = 0
};


#ifndef PLC_MD5
#error "PLC_MD5 must be defined!!!"
#endif

#define PLC_MD5_STR(a) # a
#define PLC_MD5_STR2(a) PLC_MD5_STR(a)
//App ABI, placed after .plc_app_abi_sec
__attribute__ ((section(".plc_md5_sec"))) char plc_md5[] = PLC_MD5_STR2(PLC_MD5);
//App ABI, placed at the .text end
__attribute__ ((section(".plc_check_sec"))) char plc_check_md5[] = PLC_MD5_STR2(PLC_MD5);

//Linker added symbols
extern uint32_t _plc_data_loadaddr, _plc_data_start, _plc_data_end, _plc_bss_end, _plc_sstart;

extern app_fp_t _plc_pa_start, _plc_pa_end;
extern app_fp_t _plc_ia_start, _plc_ia_end;
extern app_fp_t _plc_fia_start,_plc_fia_end;

extern int startPLC(int argc,char **argv);
extern int stopPLC();
extern void runPLC(void);

extern void resumeDebug(void);
extern void suspendDebug(int disable);

extern void FreeDebugData(void);
extern int GetDebugData(unsigned long *tick, unsigned long *size, void **buffer);

extern void ResetDebugVariables(void);
extern void RegisterDebugVariable(int idx, void* force);

extern void ResetLogCount(void);
extern uint32_t GetLogCount(uint8_t level);
extern uint32_t GetLogMessage(uint8_t level, uint32_t msgidx, char* buf, uint32_t max_size, uint32_t* tick, uint32_t* tv_sec, uint32_t* tv_nsec);

//App ABI, placed at the .text start
__attribute__ ((section(".plc_app_abi_sec"))) plc_app_abi_t plc_yaplc_app =
{
    .sstart = (uint32_t *)&_plc_sstart,
    .entry  = fake_start,
    
    //Startup interface
    .data_loadaddr = &_plc_data_loadaddr,

    .data_start    = &_plc_data_start,
    .data_end      = &_plc_data_end,

    .bss_end       = &_plc_bss_end,

    .pa_start  = &_plc_pa_start,
    .pa_end    = &_plc_pa_end,

    .ia_start  = &_plc_ia_start,
    .ia_end    = &_plc_ia_end,

    .fia_start = &_plc_fia_start,
    .fia_end   = &_plc_fia_end,

    .check_id  = plc_check_md5,

    //Must be run on compatible RTE
    .rte_ver_major = 1,
    .rte_ver_minor = 0,
    .rte_ver_patch = 0,
    
    .hw_id = 411,
    
    //Located Variables
    // IO manager interface
    .l_tab = &plc_loc_table[0],
    .w_tab = &plc_loc_weigth[0],
    .l_sz  = PLC_LOC_TBL_SIZE,
    
    //Located functions
    .funcs = &PlcAppFuncs,

    //Common ticktime
    .common_ticktime = &common_ticktime__,

    //App interface
    .id   = plc_md5,

    .start = startPLC,
    .stop  = stopPLC,
    .run   = runPLC,

    .dbg_resume    = resumeDebug,
    .dbg_suspend   = suspendDebug,

    .dbg_data_get  = GetDebugData,
    .dbg_data_free = FreeDebugData,

    .dbg_vars_reset   = ResetDebugVariables,
    .dbg_var_register = RegisterDebugVariable,

    .log_cnt_get   = GetLogCount,
    .log_msg_get   = GetLogMessage,
    .log_cnt_reset = ResetLogCount,
    .log_msg_post  = LogMessage
};

//Redefine LOG_BUFFER_SIZE
#define LOG_BUFFER_SIZE (1<<10) /*1Ko*/
#define LOG_BUFFER_ATTRS

#define PLC_RTE ((plc_rte_abi_t *)(PLC_RTE_ADDR))

void PLC_GetTime(IEC_TIME *CURRENT_TIME)
{
    //PLC_RTE->get_time( CURRENT_TIME );
    if(PlcAppFuncs.GetTime)
    {
       PlcAppFuncs.GetTime(CURRENT_TIME);
    }
    (void)CURRENT_TIME;
}

void PLC_SetTimer(unsigned long long next, unsigned long long period)
{
    //@TODO ???
    //PLC_RTE->set_timer( next, period );
    (void)next;
    (void)period;
}

long AtomicCompareExchange(long* atomicvar,long compared, long exchange)
{
	/* No need for real atomic op on LPC,
	 * no possible preemption between debug and PLC */
	long res = *atomicvar;
	if(res == compared){
		*atomicvar = exchange;
	}
	return res;
}

long long AtomicCompareExchange64(long long* atomicvar,long long compared, long long exchange)
{
	/* No need for real atomic op on LPC,
	 * no possible preemption between debug and PLC */
	long long res = *atomicvar;
	if(res == compared){
		*atomicvar = exchange;
	}
	return res;
}

static int debug_locked = 0;
static int _DebugDataAvailable = 0;
static unsigned long __debug_tick;

int TryEnterDebugSection(void)
{
    if(!debug_locked && __DEBUG){
        debug_locked = 1;
		return 1;
    }
    return 0;
}

void LeaveDebugSection(void)
{
        debug_locked = 0;
}

void InitiateDebugTransfer(void)
{
    /* remember tick */
    __debug_tick = __tick;
    _DebugDataAvailable = 1;
}

void suspendDebug(int disable)
{
    /* Prevent PLC to enter debug code */
    __DEBUG = !disable;
    debug_locked = !disable;
}

void resumeDebug(void)
{
    /* Let PLC enter debug code */
    __DEBUG = 1;
    debug_locked = 0;
}

int WaitDebugData(unsigned long *tick)
{
    if(_DebugDataAvailable && !debug_locked){
        /* returns 0 on success */
        *tick = __debug_tick;
        _DebugDataAvailable = 0;
        return 0;
    }
    return 1;
}

void ValidateRetainBuffer(void)
{
    //PLC_RTE->validate_retain_buf();
}
void InValidateRetainBuffer(void)
{
    //PLC_RTE->invalidate_retain_buf();
}
int CheckRetainBuffer(void)
{
    //return PLC_RTE->check_retain_buf();
    return (1);
}

void InitRetain(void)
{
}

void CleanupRetain(void)
{
}

void Retain(unsigned int offset, unsigned int count, void *p)
{
    //PLC_RTE->retain( offset, count, p );
}
void Remind(unsigned int offset, unsigned int count, void *p)
{
    //PLC_RTE->remind( offset, count, p );
}

int startPLC(int argc,char **argv)
{
	if(__init(argc,argv) == 0){
		PLC_SetTimer(0, common_ticktime__);
		return 0;
	}else{
		return 1;
	}
}

int stopPLC(void)
{
    __cleanup();
    return 0;
}

void runPLC(void)
{
    PLC_GetTime( &__CURRENT_TIME );
    __run();
}



/** F(B) C-code
 */

#include "iec_types_all.h"
#include "POUS.h"

//@TODO + define APP_* from LOCATED_VARIABLES_HIDDEN (by used libraries)

#define APP_DI
#define APP_DO
#define APP_AI
#define APP_FLR
#define APP_SYS

/** DI
 */

#ifdef APP_DI

/** @brief  DIMode.
 *  @param  DataIn - FB-arguments.
 *  @return None.
 */
void App_DIMode(DIMODE *DataIn)
{
    if(DataIn && PlcAppFuncs.DIMode)
    {
        BYTE DIn = __GET_VAR(DataIn->DIN);
        BYTE M   = __GET_VAR(DataIn->M);
        BYTE Om  = __GET_VAR(DataIn->OM);
        BYTE Ok  = 0;
        
        PlcAppFuncs.DIMode(&DIn, &M, &Om, &Ok);
        
        __SET_VAR(DataIn->, OM,, Om);
        __SET_VAR(DataIn->, OK,, Ok);
    }
}

/** @brief  DINorm.
 *  @param  DataIn - FB-arguments.
 *  @return None.
 */
void App_DINorm(DINORM *DataIn)
{
    if(DataIn && PlcAppFuncs.DINorm)
    {
        BYTE DIn = __GET_VAR(DataIn->DIN);
        BOOL Ov  = 0;
        BYTE Ok  = 0;
        
        PlcAppFuncs.DINorm(&DIn, &Ov, &Ok);
        
        __SET_VAR(DataIn->, OV,, Ov);
        __SET_VAR(DataIn->, OK,, Ok);
    }
}

/** @brief  DITach.
 *  @param  DataIn - FB-arguments.
 *  @return None.
 */
void App_DITach(DITACH *DataIn)
{
    if(DataIn && PlcAppFuncs.DITach)
    {
        BYTE DIn   = __GET_VAR(DataIn->DIN);
        WORD Ref   = __GET_VAR(DataIn->REF);
        BOOL RefEn = __GET_VAR(DataIn->REFEN);
        WORD Ov    = 0;
        BOOL Oref  = 0;
        BYTE Ok    = 0;
        
        PlcAppFuncs.DITach(&DIn, &Ref, &RefEn, &Ov, &Oref, &Ok);
        
        __SET_VAR(DataIn->, OV,, Ov);
        __SET_VAR(DataIn->, OREF,, Oref);
        __SET_VAR(DataIn->, OK,, Ok);
    }
}

/** @brief  DICntr.
 *  @param  DataIn - FB-arguments.
 *  @return None.
 */
void App_DICntr(DICNTR *DataIn)
{
    if(DataIn && PlcAppFuncs.DICntr)
    {
        BYTE DIn   = __GET_VAR(DataIn->DIN);
        DWORD Ref  = __GET_VAR(DataIn->REF);
        BOOL RefEn = __GET_VAR(DataIn->REFEN);
        DWORD Ov   = 0;
        BOOL Oref  = 0;
        BYTE Ok    = 0;
        
        PlcAppFuncs.DICntr(&DIn, &Ref, &RefEn, &Ov, &Oref, &Ok);
        
        __SET_VAR(DataIn->, OV,, Ov);
        __SET_VAR(DataIn->, OREF,, Oref);
        __SET_VAR(DataIn->, OK,, Ok);
    }
}

/** @brief  DICntrRst.
 *  @param  DataIn - FB-arguments.
 *  @return None.
 */
void App_DICntrRst(DICNTRRST *DataIn)
{
    if(DataIn && PlcAppFuncs.DICntrRst)
    {
        BYTE DIn = __GET_VAR(DataIn->DIN);
        BOOL Rst = __GET_VAR(DataIn->RST);
        BYTE Ok  = 0;
        
        PlcAppFuncs.DICntrRst(&DIn, &Rst, &Ok);
        
        __SET_VAR(DataIn->, OK,, Ok);
    }
}

/** @brief  DIEnc.
 *  @param  DataIn - FB-arguments.
 *  @return None.
 */
void App_DIEnc(DIENC *DataIn)
{
    if(DataIn && PlcAppFuncs.DIEnc)
    {
        BYTE  DIn    = __GET_VAR(DataIn->DIN);
        DWORD RefA   = __GET_VAR(DataIn->REFA);
        BOOL  RefAEn = __GET_VAR(DataIn->REFAEN);
        DWORD RefB   = __GET_VAR(DataIn->REFB);
        BOOL  RefBEn = __GET_VAR(DataIn->REFBEN);
        WORD  RefT   = __GET_VAR(DataIn->REFT);
        BOOL  RefTEn = __GET_VAR(DataIn->REFTEN);
        DWORD OA     = 0;
        BOOL  OAref  = 0;
        DWORD OB     = 0;
        BOOL  OBref  = 0;
        WORD  OT     = 0;
        BOOL  OTref  = 0;
        BYTE  Ok     = 0;
        
        PlcAppFuncs.DIEnc(&DIn, &RefA, &RefAEn, &RefB, &RefBEn, &RefT, &RefTEn, &OA, &OAref, &OB, &OBref, &OT, &OTref, &Ok);
        
        __SET_VAR(DataIn->, OA,, OA);
        __SET_VAR(DataIn->, OAREF,, OAref);
        __SET_VAR(DataIn->, OB,, OB);
        __SET_VAR(DataIn->, OBREF,, OBref);
        __SET_VAR(DataIn->, OT,, OT);
        __SET_VAR(DataIn->, OTREF,, OTref);
        __SET_VAR(DataIn->, OK,, Ok);
    }
}

#endif // APP_DI



/** DO
 */

#ifdef APP_DO

/** @brief  DOMode.
 *  @param  DataIn - FB-arguments.
 *  @return None.
 */
void App_DOMode(DOMODE *DataIn)
{
    if(DataIn && PlcAppFuncs.DOMode)
    {
        BYTE DOn = __GET_VAR(DataIn->DON);
        BYTE M   = __GET_VAR(DataIn->M);
        BYTE Om  = __GET_VAR(DataIn->OM);
        BYTE Ok  = 0;
        
        PlcAppFuncs.DOMode(&DOn, &M, &Om, &Ok);
        
        __SET_VAR(DataIn->, OM,, Om);
        __SET_VAR(DataIn->, OK,, Ok);
    }
}

/** @brief  DONorm.
 *  @param  DataIn - FB-arguments.
 *  @return None.
 */
void App_DONorm(DONORM *DataIn)
{
    if(DataIn && PlcAppFuncs.DONorm)
    {
        BYTE DOn = __GET_VAR(DataIn->DON);
        BOOL V   = __GET_VAR(DataIn->V);
        BOOL Ov  = 0;
        BYTE Ok  = 0;
        
        PlcAppFuncs.DONorm(&DOn, &V, &Ov, &Ok);
        
        __SET_VAR(DataIn->, OV,, Ov);
        __SET_VAR(DataIn->, OK,, Ok);
    }
}

/** @brief  DOFast.
 *  @param  DataIn - FB-arguments.
 *  @return None.
 */
void App_DOFast(DOFAST *DataIn)
{
    if(DataIn && PlcAppFuncs.DOFast)
    {
        BYTE DOn = __GET_VAR(DataIn->DON);
        BOOL V   = __GET_VAR(DataIn->V);
        BOOL Ov  = 0;
        BYTE Ok  = 0;
        
        PlcAppFuncs.DOFast(&DOn, &V, &Ov, &Ok);
        
        __SET_VAR(DataIn->, OV,, Ov);
        __SET_VAR(DataIn->, OK,, Ok);
    }
}

/** @brief  DOPwm.
 *  @param  DataIn - FB-arguments.
 *  @return None.
 */
void App_DOPwm(DOPWM *DataIn)
{
    if(DataIn && PlcAppFuncs.DOPwm)
    {
        BOOL En  = __GET_VAR(DataIn->ENX);
        BYTE DOn = __GET_VAR(DataIn->DON);
        REAL Tm  = __GET_VAR(DataIn->TM);
        REAL  D  = __GET_VAR(DataIn->DU);
        BOOL Ow  = 0;
        BYTE Ok  = 0;
        
        PlcAppFuncs.DOPwm(&En, &DOn, &Tm, &D, &Ow, &Ok);
        
        __SET_VAR(DataIn->, OW,, Ow);
        __SET_VAR(DataIn->, OK,, Ok);
    }
}

#endif // APP_DO



/** AI
 */

#ifdef APP_AI

/** @brief  AIMode.
 *  @param  DataIn - FB-arguments.
 *  @return None.
 */
void App_AIMode(AIMODE *DataIn)
{
    if(DataIn && PlcAppFuncs.AIMode)
    {
        BYTE  AIn = __GET_VAR(DataIn->AIN);
        BYTE  M   = __GET_VAR(DataIn->M);
        BYTE Om   = __GET_VAR(DataIn->OM);
        BYTE Os   = __GET_VAR(DataIn->OS);
        BYTE Ok   = 0;
        
        PlcAppFuncs.AIMode(&AIn, &M, &Om, &Os, &Ok);
        
        __SET_VAR(DataIn->, OM,, Om);
        __SET_VAR(DataIn->, OS,, Os);
        __SET_VAR(DataIn->, OK,, Ok);
    }
}

/** @brief  AINorm.
 *  @param  DataIn - FB-arguments.
 *  @return None.
 */
void App_AINorm(AINORM *DataIn)
{
    if(DataIn && PlcAppFuncs.AINorm)
    {
        BYTE AIn = __GET_VAR(DataIn->AIN);
        REAL Ov  = 0.0;
        BYTE Os  = 0;
        BYTE Ok  = 0;
        
        PlcAppFuncs.AINorm(&AIn, &Ov, &Os, &Ok);
        
        __SET_VAR(DataIn->, OV,, Ov);
        __SET_VAR(DataIn->, OS,, Os);
        __SET_VAR(DataIn->, OK,, Ok);
    }
}

#endif // APP_AI


/** FLR
 */

#ifdef APP_FLR

/** @def PI
 */
#define APP_FLR_PI          (REAL)3.14159265358979

/** @def Quantity of terms
 */
#define APP_FLR_SZ          5

/** @def Input terms
 */
#define APP_FLR_IN_HI2      0   //very higher
#define APP_FLR_IN_HI       1   //high
#define APP_FLR_IN_NORM     2   //normal
#define APP_FLR_IN_LO       3   //low
#define APP_FLR_IN_LO2      4   //very lowest

/** @def Output terms
 */
#define APP_FLR_OUT_OP2     0   //fast open  (speed 2)
#define APP_FLR_OUT_OP1     1   //slow open  (speed 1)
#define APP_FLR_OUT_NONE    2   //nothing
#define APP_FLR_OUT_CL1     3   //slow close (speed 1)
#define APP_FLR_OUT_CL2     4   //fast close (speed 2)

/** @def Direction of output value increase
 */
#define APP_FLR_DIR_DOWN    (SINT)-1
#define APP_FLR_DIR_NONE    (SINT)0
#define APP_FLR_DIR_UP      (SINT)1

/** @def Min/Max
 */
#define APP_FLR_MIN         (REAL)-1.0
#define APP_FLR_MAX         (REAL)1.0

/** @def Inverse probability of normal state
 *  @note q = (1 - Actions[APP_FLR_IN_NORM])
 */
#define APP_FLR_Q_MIN       (REAL)0.0
#define APP_FLR_Q_MAX       (REAL)0.3

/** @def Sigma
 */
#define APP_FLR_SIGMA       (REAL)0.0

/** @def Step of accumulating value increase
 */
#define APP_FLR_DX          (REAL)0.01


/** @brief  Gaus-function.
 *  @param  C   - value of In, where Gaus-function is maximum (1.0).
 *  @param  S   - incremental step of Gaus-function.
 *  @param  In  - input value.
 *  @param  Out - result.
 *  @return Result.
 */
REAL AppFlr_GausFx(const REAL C, const REAL S, const REAL In)
{
    if(S) return (exp(((-1.0)*(0.5*powf((In-C), 2.0)))/(powf(S, 2.0))));
    return (0.0);
}

/** @brief  Triangle-function.
 *  @param  A   - A-argument.
 *  @param  B   - B-argument.
 *  @param  C   - C-argument.
 *  @param  In  - input value.
 *  @return Result.
 */
REAL AppFlr_TriangleFx(const REAL A, const REAL B, const REAL C, const REAL In)
{
    if(In > A && In < C) return ((In < B) ? (In-A)/(B-A) : (C-In)/(C-B));
    return (0.0);
}

/** @brief  Get difference between value and setpoint in Term-format (-1 .. 1).
 *  @param  ErSrc  - source difference (error).
 *  @return None.
 */
REAL AppFlr_ErTerm(const REAL ErSrc)
{
    //trigonometric function
    REAL Er = (270.0-ErSrc);
    if(Er < 180.0) Er = 180.0;  //to min
    if(Er > 360.0) Er = 360.0;  //to max
    Er = Er*(APP_FLR_PI/180.0); //to radian
    Er = cos(Er)*2.0;
    return (Er);
}

/** @brief  Get output terms.
 *  @param  Sigma - Sigma-value.
 *  @param  Min - minimum.
 *  @param  Max - maximum.
 *  @param  In  - input value.
 *  @param  Out - pointer to array of output terms.
 *  @return None.
 */
void AppFlr_OutTerms(const REAL Sigma, const REAL Min, const REAL Max, const REAL In, REAL *Out)
{
    if(Out)
    {
        REAL S = ((Sigma != 0.0) ? Sigma : (Max-Min)/((REAL)(2*APP_FLR_SZ)));
        REAL C;
        BYTE i;
        
        for(i=0; i<APP_FLR_SZ; i++)
        {
            if(In < Min)
            {
                //fast open
                Out[i] = ((i == APP_FLR_OUT_OP2) ? APP_FLR_MAX : 0.0);
            }
            else if(In > Max)
            {
                //fast close
                Out[i] = ((i == APP_FLR_OUT_CL2) ? APP_FLR_MAX : 0.0);
            }
            else
            {
                C = Min+((((REAL)i)*(Max-Min))/((REAL)(APP_FLR_SZ-1)));
                Out[i] = AppFlr_GausFx(C, S, In);
            }
        }
    }
}

/** @brief  Accumulate actions.
 *  @param  dX  - step of value increase.
 *  @param  Min - minimum.
 *  @param  Max - maximum.
 *  @param  Actions - pointer to array of actions.
 *  @return Value of control action.
 */
REAL AppFlr_AccActions(const REAL dX, const REAL Min, const REAL Max, REAL *Actions, REAL *OCm, REAL *Om)
{
    if(Actions && dX)
    {
        /** @var Arguments of Triangle-function
         */
        REAL A[APP_FLR_SZ] = {-1.0, -0.7, -0.25, 0.4, 0.8};
        REAL B[APP_FLR_SZ] = {-0.9, -0.5,  0.0,  0.5, 0.9};
        REAL C[APP_FLR_SZ] = {-0.8, -0.3,  0.25, 0.7, 1.0};
        
        REAL Val, Acc;
        REAL L  = 0.0;
        REAL R  = 0.0;
        REAL cm = 0.0;
        REAL m  = 0.000000001;
        BYTE i;
        
        for(Val=Min; Val<=Max; Val+=dX)
        {
            //accumulate value
            for(i=0; i<APP_FLR_SZ; i++)
            {
                Acc = Actions[i]*AppFlr_TriangleFx(A[i], B[i], C[i], Val);
                if(!i || Acc > R) R = Acc;
            }
            
            cm = cm	+ (dX*(((Val*L)+(Val+dX)*R)/2.0));
            m  = m	+ (((L+R)/2.0)*dX);
            L  = R;
        }
        
        if(OCm) *OCm = cm;
        if(Om)  *Om  = m;
        
        if(m != 0.0) return (cm/m);
    }
    
    return (0.0);
}

/** @brief  Probability of normal state.
 *  @param  V       - current value.
 *  @param  Sp      - setpont.
 *  @param  Speed   - speed of changing V at time TmCy.
 *  @param  ActNorm - value of normal action.
 *  @param  Y       - Y-value.
 *  @return None.
 */
void AppFlr_ProbNorm(const REAL V, const REAL Sp, const REAL Speed, const REAL ActNorm, REAL *Y)
{
    if(Y)
    {
        /** @var Inverse probability of normal state
         */
        REAL q = (1.0-ActNorm);
        if(q > APP_FLR_Q_MIN && q < APP_FLR_Q_MAX)
        {
            if((V < Sp && Speed > 0.0) || (V > Sp && Speed < 0.0))
            {
                *Y *= (-1.0);
            }
        }
    }
}

/** @brief  Get direction of changing Y.
 *  @param  Y - Y-value.
 *  @return UpDown-value.
 */
SINT AppFlr_UpDown(const REAL Y)
{
    if(Y < 0.0) return (APP_FLR_DIR_DOWN);
    if(Y > 0.0) return (APP_FLR_DIR_UP);
    return (APP_FLR_DIR_NONE);
}

/** @brief  Get time of changing Y.
 *  @param  Tm - time of main-cycle (msec).
 *  @param  Y - Y-value.
 *  @return UpDown-value.
 */
REAL AppFlr_dVTm(const REAL Tm, const REAL Y)
{
    if(Tm)
    {
        REAL Yabs = (REAL)fabs((LREAL)Y);
        return ((Tm-(Yabs*Tm)));
    }
    return (0.0);
}

/** @brief  FuzzyLogic.
 *  @param  DataIn - FB-arguments.
 *  @return None.
 */
void AppFlr(FLR1 *DataIn)
{
    if(DataIn)
    {
        //get FB-data
        REAL V      = __GET_VAR(DataIn->V);
        REAL Vprev  = __GET_VAR(DataIn->VPREV);
        REAL Sp     = __GET_VAR(DataIn->SP);
        REAL ErSrc  = __GET_VAR(DataIn->ER);
        REAL Tm     = __GET_VAR(DataIn->TM);
        
        /** @var Debug
         */
        REAL Ocm, Om;
        
        /** @var Speed of changing source value
         */
        REAL Speed = (V-Vprev);
        
        /** @var Difference between value and setpoint (Term-format)
         */
        REAL Er = AppFlr_ErTerm(ErSrc);
        
        /** @var Output terms
         */
        REAL Outputs[APP_FLR_SZ];
        //init. output terms
        AppFlr_OutTerms(APP_FLR_SIGMA, APP_FLR_MIN, APP_FLR_MAX, Er, Outputs);
        
        /** @var Actions
         */
        REAL Actions[APP_FLR_SZ];
        //rules
        Actions[APP_FLR_IN_HI2]  = Outputs[APP_FLR_OUT_CL2];
        Actions[APP_FLR_IN_HI]   = Outputs[APP_FLR_OUT_CL1];
        Actions[APP_FLR_IN_NORM] = Outputs[APP_FLR_OUT_NONE];
        Actions[APP_FLR_IN_LO]   = Outputs[APP_FLR_OUT_OP1];
        Actions[APP_FLR_IN_LO2]  = Outputs[APP_FLR_OUT_OP2];
        //accumulate actions
        REAL Y = AppFlr_AccActions(APP_FLR_DX, APP_FLR_MIN, APP_FLR_MAX, Actions, &Ocm, &Om);
        //probability of normal action
        AppFlr_ProbNorm(V, Sp, Speed, Actions[APP_FLR_IN_NORM], &Y);
        
        /** @var Direction of changing Y
         */
        SINT UpDown = AppFlr_UpDown(Y);
        
        /** @var Time of changing Y (msec)
         */
        REAL TmDv = AppFlr_dVTm(Tm, Y);
        
        //set FB-data
        __SET_VAR(DataIn->, VPREV,, V);
        __SET_VAR(DataIn->, TMDV,, TmDv);
        __SET_VAR(DataIn->, UPDOWN,, UpDown);
        //__SET_VAR(DataIn->, DEB_SPEED,, Speed);
        //__SET_VAR(DataIn->, DEB_Y0,, Y0);
        //__SET_VAR(DataIn->, DEB_ER,, Er);
        //__SET_VAR(DataIn->, DEB_CM,, Ocm);
        //__SET_VAR(DataIn->, DEB_M,, Om);
    }
}

#endif // APP_FLR



/** SYSTEM
 */

#ifdef APP_SYS

/** @brief  Software reset.
 *  @param Ex - allow to execution:
 *  @arg     = false - not allow
 *  @arg     = true  - allow
 *  @return None.
 */
void AppSys_SoftReset(BOOL ExIn)
{
    if(PlcAppFuncs.SoftReset)
    {
        PlcAppFuncs.SoftReset(ExIn);
    }
}

/** @brief  LedUser.
 *  @param  DataIn - FB-arguments.
 *  @return None.
 */
void App_LedUser(LEDUSER *DataIn)
{
    if(DataIn && PlcAppFuncs.LedUser)
    {
        BOOL V   = __GET_VAR(DataIn->V);
        BOOL Ov  = 0;
        
        PlcAppFuncs.LedUser(&V, &Ov);
        
        __SET_VAR(DataIn->, OV,, Ov);
    }
}

#endif // APP_SYS
