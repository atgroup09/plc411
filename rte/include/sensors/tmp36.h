/* @page tmp36.h
 *       TMP36 - Low Voltage Temperature Sensor (Analog Devices)
 *       2022, atgroup09@gmail.com
 */

/** @note
 * 		 Low voltage operation (2.7 V to 5.5 V)
 * 		 −40 ... +125 C, operation to +150 C
 *
 * 		 Scaling formulas:
 *
 * 		 1) Converting ADC-code to Volts:
 *
 * 		 !  V = (Ka*ADC) + Kb
 *
 * 		    where, ADC - ADC-code (ex.: 0.0 ... 4095 for 12bit ADC)
 * 		           Ka  - slope of characteristic  (> 0)
 * 		           Kb  - offset of characteristic (>=0)
 *
 * 		           Ka = (Ymax - Ymin)/(ADCmax - ADCmin)
 * 		           Kb = (Ymin*ADCmax - Ymax*ADCmin)/(ADCmax - ADCmin)
 *
 * 		           Ymin ... Ymax - real-values
 * 		           ADCmin ... ADCmax - ADC-code
 *
 * 		     or
 *
 * 		    V = (ADC)*(V_PWR/ADCmax)
 *
 * 		     where, V_PWR - power supply of sensor (0.0 ... 3,3 V, 0.0 ... 5,0 V)
 *
 * 		 2) Converting Volts to Centigrade temperature (C*):
 *
 * 		    Temp = (V - OffsetV)/FactorV  ->  (V*1/FactorV) + (-OffsetV*1/FactorV)
 *
 * 		     where, FactorV - scale factor (10 mV/C = 0.01 V/C)
 * 		            OffsetV - offset to allow for negative temperatures (500 mV = 0.5 V)
 *
 * 		    or
 *
 * 		 !  Temp = (Ka*V) + Kb
 *
 * 		    where, Ka = 1/FactorV = 1/0.01 = 100
 * 		           Kb = -OffsetV*1/FactorV = -0.5*100 = -50
 */

#ifndef TMP36_H_
#define TMP36_H_

#include <stdint.h>


/** @def mV to V
 */
#define TMP36_500MV_V	(float)0.5
#define TMP36_10MV_V	(float)0.01
#define TMP36_10MV_V2	(float)100.0    // 1/TMP36_10MV_V

/** @def Scale factors
 */
#define TMP36_KA	    (float)100.0
#define TMP36_KB	    (float)-50.0


/** @brief  Get temperature.
 *  @param  V - sensor value (V).
 *  @return Temperature (C*).
 */
float Tmp36_GetTemp(float V);


#endif // TMP36_H_
