#ifndef HANDLERS_H_
#define HANDLERS_H_

#include "AngleCalculation.h"

/* =================================================================================
 * Handles the button press when starting the arm sequence.
 *
 * Increments the current shelf count then calls GetAngles() to retrieve the target
 * XZ coordinates and calls ValidateAngles() to check arm constraints.
 * Finally, the program will select the appropriate arm movements in order to reach
 * the target.
 */
void HandlePortFInterrupt();

#endif
