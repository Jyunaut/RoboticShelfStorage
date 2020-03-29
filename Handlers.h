#ifndef HANDLERS_H_
#define HANDLERS_H_

#include "tm4c123gh6pm.h"
#include "AngleCalculation.h"
#include "MotionControl.h"

/* =================================================================================
 * Handles the button press when starting the arm sequence.
 *
 * Increments the current shelf count then calls GetAngles() to retrieve the target
 * XZ coordinates and check arm constraints.
 * Finally, the program will select the appropriate arm movements in order to reach
 * the target.
 */
void HandlePortFInterrupt();

#endif
