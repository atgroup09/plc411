/* @page reg-init.h
 *       PLC411::RTE
 *       Registers :: API (Init.)
 *       2022, atgroup09@gmail.com
 */

#ifndef REG_INIT_H
#define REG_INIT_H

#include "reg.h"


/** @typedef System states (1)
 *           bit-fields
 */
typedef struct REG_SysStat1_Pack_t_ {

    //Application load-status
    //  = 0 - not loaded
    //  = 1 - loaded
    uint16_t AppInited:1;

    //Application run-status
    //  = 0 - not run
    //  = 1 - run
    uint16_t AppRun:1;

    //Application run-first-cycle-status
    //  = 0 - first cycle is not completed
    //  = 1 - completed
    uint16_t AppRun1:1;

    //Safety timer time status
    //  = 0 - time is not set
    //  = 1 - time is set
    uint16_t SftyTimSet:1;

    //Safety timer status
    //  = 0 - timer is not completed count
    //  = 1 - timer is completed count
    uint16_t SftyTimCplt:1;

    //WD-timer time status
    //  = 0 - time is not set
    //  = 1 - time is set
    uint16_t WdTimSet:1;

    //LED_USER status
    //  = 0 - off
    //  = 1 - on
    uint16_t LedUser:1;

} REG_SysStat1_Pack_t;

typedef union {

    REG_SysStat1_Pack_t Pack;
    uint16_t Data;

}  REG_SysStat1_Pack_ut;

/** @def Field numbers
 */
#define PLC_SYS_STAT1_APP_INITED     (uint8_t)0
#define PLC_SYS_STAT1_APP_RUN        (uint8_t)1
#define PLC_SYS_STAT1_APP_RUN1       (uint8_t)2
#define PLC_SYS_STAT1_SFTY_TIM_SET   (uint8_t)3
#define PLC_SYS_STAT1_SFTY_TIM_CPLT  (uint8_t)4
#define PLC_SYS_STAT1_WD_TIM_SET     (uint8_t)5
#define PLC_SYS_STAT1_LED_USER       (uint8_t)6


/** @typedef RTE version (major minor) (packed)
 *           bit-fields
 */
typedef struct REG_RTE_VER_Pack_t_ {

    uint16_t Major:4;  //major
    uint16_t Minor:4;  //minor
    uint16_t Patch:4;  //patch

} REG_RTE_VER_Pack_t;

typedef union {

    REG_RTE_VER_Pack_t Pack;
    uint16_t Data;

}  REG_RTE_VER_Pack_ut;


/** @typedef RTE DDMM (day month) (packed)
 *           bit-fields
 */
typedef struct REG_RTE_DDMM_Pack_t_ {

    uint16_t DD:5;  //day
    uint16_t MM:5;  //month

} REG_RTE_DDMM_Pack_t;

typedef union {

    REG_RTE_DDMM_Pack_t Pack;
    uint16_t Data;

}  REG_RTE_DDMM_Pack_ut;


/** @var SYSTEM STATUS (1)
 *       packed
 */
extern REG_SysStat1_Pack_ut PLC_SYS_STAT1;


/** @brief  Init. registers.
 *  @param  None.
 *  @return The number of inited registers.
 */
uint16_t REG_Init(void);

#ifdef RTE_MOD_APP
/** @brief  Copy from ModBus (Data) Tables into Located variables.
 *  @param  None.
 *  @return The number of copied registers.
 */
uint16_t REG_CopyMbToApp(void);

/** @brief  Copy from Located variables into ModBus (Data) Tables.
 *  @param  None.
 *  @return The number of copied registers.
 */
uint16_t REG_CopyAppToMb(void);
#endif // RTE_MOD_APP

/** @brief  Set values by default.
 *  @param  None.
 *  @return None.
 */
void REG_SetDef(void);

/** @brief  Set register SYS_STAT1.
 *  @param  FieldIn - field number:
 *  @arg    = PLC_SYS_STAT1_APP_INITED ... PLC_SYS_STAT1_LED_USER
 *  @param  ValueIn - field value:
 *  @arg    = BIT_FALSE
 *  @arg    = BIT_TRUE
 *  @return None.
 */
void REG_SYS_STAT1_Set(uint8_t FieldIn, uint8_t ValueIn);

#endif //REG_INIT_H
