/* @page tmp-mcu.c
 *       Low Voltage MCU Temperature Sensor (STM32F4)
 *       2022, atgroup09@gmail.com
 */

#include "tmp-mcu.h"


/** @brief  Get temperature.
 *  @param  V - sensor value (Vsense).
 *  @return Temperature (C*).
 */
inline float TmpMcu_GetTemp(float V)
{
	return (((V-TMP_MCU_V25)*TMP_MCU_AVG_SLOPE2)+25.0);
}
