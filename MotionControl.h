#ifndef MOTIONCONTROL_H_
#define MOTIONCONTROL_H_

#include "AngleCalculation.h"

/* ================================================================================
 * Calculates Degrees to Period (PWM duty cycle in microseconds).
 */
inline float DegToUs(float deg);

/* ================================================================================
 * Calculates the step size for the motors so that they have the same number of
 * steps. This assumes one step per mm.
 */
short GetNumberOfSteps(short currentShelf, short currentKeyPosition, short targetKeyPosition);

/* =================================================================================
 * This selects the key positions for the motion controller to move from the outside
 * of the current shelf to the outside of the target shelf.
 */
void MoveToShelf(short currentShelf, short targetShelf);

/* =================================================================================
 * This selects the key positions for the motion controller to leave the current
 * shelf.
 *
 * This results in the arm being left outside of the current shelf.
 */
void RemoveFork(short currentShelf);

/* =================================================================================
 * This selects the key positions for the motion controller to enter the current
 * shelf.
 *
 * This results in the arm being left inside of the current shelf.
 */
void InsertFork(short currentShelf);

/* =================================================================================
 * This tells the arm to move back from its current shelf back to the feed shelf
 *
 * This results in the arm being left inside of the feed shelf.
 */
void ReturnHome();

#endif
