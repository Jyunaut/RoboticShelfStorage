#ifndef ANGLECALCULATION_H_
#define ANGLECALCULATION_H_

#include <math.h>

/* =================================================================================
 * Calculates Degrees to Radians
 */
float DegToRad(float deg);

/* =================================================================================
 * Input positions are in mm from the motors' axis to top joint on the fork
 * Calling code must provide 2-element array for function to write angles back to
 */
void GetAngles(float xPos, float zPos, float* outputAngles);

/* =================================================================================
 * Returns an error number if the system fails to follow any of the constraints
 * If returns > 0, then calling code must abort and not move motors output angles
 */
char ValidateAngles(float xPos, float zPos, float* outputAngles);

#endif
