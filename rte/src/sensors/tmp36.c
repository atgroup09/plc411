/* @page tmp36.c
 *       TMP36 - Low Voltage Temperature Sensor (Analog Devices)
 *       2022, atgroup09@gmail.com
 */

#include "tmp36.h"


/** @brief  Get temperature.
 *  @param  V - sensor value (V).
 *  @return Temperature (C*).
 */
inline float Tmp36_GetTemp(float V)
{
	return ((V-TMP36_500MV_V)*TMP36_10MV_V2);
}
