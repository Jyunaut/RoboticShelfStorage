#ifndef MOTIONCONTROL_H_
#define MOTIONCONTROL_H_

#include <Servo.h>
#include "AngleCalculation.h"

/* =================================================================================
 * This selects the key positions for the motion controller to move from the outside
 * of the current shelf to the outside of the target shelf.
 */
void MoveToShelf(short targetShelf, short targetKeyPosition = 2);

/* =================================================================================
 * This selects the key positions for the motion controller to leave the current
 * shelf.
 *
 * This results in the arm being left outside of the current shelf.
 */
void RemoveFork();

/* =================================================================================
 * This selects the key positions for the motion controller to enter the current
 * shelf.
 *
 * This results in the arm being left inside of the current shelf.
 */
void InsertFork();

/* =================================================================================
 * This tells the arm to move back from its current shelf back to the feed shelf
 *
 * This results in the arm being left inside of the feed shelf.
 */
void ReturnHome();

/* =================================================================================
 * This function takes a set of XZ coordinates and linearly moves the arm to the
 * requested position.
 */
void MoveTo(float x, float z);

#endif

