/* @page tmp-mcu.h
 *       Low Voltage MCU Temperature Sensor (STM32F4)
 *       2022, atgroup09@gmail.com
 */

/** @note MCU Temperature sensor
 *        + 12 bit
 *        + 0 .. 4095 (-40 .. 125 C*)
 *
 *        Temp-sensor -> ADC1.Channel16 > DMA2.Stream0.Channel0(ADC1)::Rank3
 *        used AI-buffer (PLC_AI_ADC_BUFF, see ai.h and ai.c)
 *
 *        ====================================================================
 *
 *        Temp = { (Vsense - V25) / Avg_Slope } + 25 (C*)
 *
 *        Vsense = (ADC/ADCmax)*Vref
 *          or
 *        Vsense = (Ka*ADC) + Kb
 *
 *        where,
 *          ADC       - current ADC-code
 *          ADCmax    - maximum ADC-code (4095 for 12bit ADC)
 *          Vref      - ADC Vref (V)
 *          Vsense    - current sensor value (V)
 *          V25       - Vsense value for 25 C* (constant)
 *          Avg_Slope - average slope of the temperature vs. Vsense curve (V/C*) (constant)
 *
 * 		    Ka  - slope of characteristic  (> 0)
 * 		    Kb  - offset of characteristic (>=0)
 *
 * 		    Ka = (Vmax - Vmin)/(ADCmax - ADCmin)
 * 		    Kb = (Vmin*ADCmax - Vmax*ADCmin)/(ADCmax - ADCmin)
 */

#ifndef TMP_MCU_H
#define TMP_MCU_H

#include <stdint.h>


/** @def V25 (mV)
 *       value for 25 C*
 */
#define TMP_MCU_V25                         (float)0.76

/** @def Avg_Slope (mV/C*)
 *       average slope
 */
#define TMP_MCU_AVG_SLOPE                   (float)2.5
#define TMP_MCU_AVG_SLOPE2                  (float)0.4         // 1/TMP_MCU_AVG_SLOPE


/** @def Analog levels (C*)
 */
#define TMP_MCU_TEMP_MIN                     (float)-40.0      //minumum
#define TMP_MCU_TEMP_MAX                     (float)125.0      //maximum
#define TMP_MCU_TEMP_DEF                     TMP_MCU_TEMP_MIN  //by default


/** @brief  Get temperature.
 *  @param  V - sensor value (Vsense).
 *  @return Temperature (C*).
 */
float TmpMcu_GetTemp(float V);


#endif //TMP_MCU_H
