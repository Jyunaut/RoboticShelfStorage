#ifndef ANGLECALCULATION_H_
#define ANGLECALCULATION_H_

#include <math.h>

/* =================================================================================
 * Calculates Degrees to Radians.
 */
inline float DegToRad(float deg);

/* =================================================================================
 * Calculates Radians to Degrees.
 */
inline float RadToDeg(float rad);

/* =================================================================================
 * Calculates Degrees to Period (PWM duty cycle in microseconds).
 */
inline float DegToUs(float deg);

/* =================================================================================
 * Input positions are in mm from the motors' axis to top joint on the fork.
 * Calling code must provide 2-element array for function to write angles back to.
 * Returns an error number if the system fails to follow any of the constraints.
 * If returns > 0, then calling code must abort and not move motors output angles.
 */
char GetAngles(float* stepPosition, float* outputAngles);

#endif
