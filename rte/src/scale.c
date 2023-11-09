/* @page scale.c
 *       Scaling values
 *       2020, atgroup09@gmail.com
 */

#include "scale.h"


/** @brief  Scaling an input-value.
 *  @param  In   - input-value (not scalled value, ex.: ADC code).
 *  @param  KaIn - scale Ka-factor.
 *  @param  KbIn - scale Kb-factor.
 *  @return Real-value (Y).
 *  @note   Y = KaIn*In + KbIn
 */
inline float ScaleA(float In, float KaIn, float KbIn)
{
    return ((In*KaIn)+KbIn);
}

/** @brief  Calculate Ka-factor.
 *  @param  Y1In - min real-value  (ex.: degree C, pressure Pa, ...)
 *  @param  Y2In - max real-value  (ex.: degree C, pressure Pa, ...)
 *  @param  In1  - min input-value (not scalled value, ex.: ADC code)
 *  @param  In2  - max input-value (not scalled value, ex.: ADC code)
 *  @return Ka-factor.
 *  @note   Ka = (Y2In - Y1In)/(In2 - In1)
 */
float ScaleA_Ka(float Y1In, float Y2In, float In1, float In2)
{
    float In = (In2 - In1);
    return ((In > 0.0) ? ((Y2In - Y1In)/In) : (float)0.0);
}

/** @brief  Calculate Kb-factor.
 *  @param  Y1In - min real-value  (ex.: degree C, pressure Pa, ...)
 *  @param  Y2In - max real-value  (ex.: degree C, pressure Pa, ...)
 *  @param  In1  - min input-value (not scalled value, ex.: ADC code)
 *  @param  In2  - max input-value (not scalled value, ex.: ADC code)
 *  @return Kb-factor.
 *  @note   Kb = (Y1In*In2 - Y2In*In1)/(In2 - In1)
 */
float ScaleA_Kb(float Y1In, float Y2In, float In1, float In2)
{
    float In = (In2 - In1);
    return ((In > 0.0) ? (((Y1In*In2) - (Y2In*In1))/In) : (float)0.0);
}
