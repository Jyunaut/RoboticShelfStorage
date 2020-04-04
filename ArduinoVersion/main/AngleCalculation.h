#ifndef ANGLECALCULATION_H_
#define ANGLECALCULATION_H_

/* =================================================================================
 * Input positions are in mm from the motors' axis to top joint on the fork.
 * Calling code must provide 2-element array for function to write angles back to.
 * Returns an error number if the system fails to follow any of the constraints.
 * If returns > 0, then calling code must abort and not move motors output angles.
 */
void GetAngles(float* stepPosition, float* motorAngles);

#endif

