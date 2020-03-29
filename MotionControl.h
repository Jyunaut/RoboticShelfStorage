#ifndef MOTIONCONTROL_H_
#define MOTIONCONTROL_H_

/* =================================================================================
 * Calculates Degrees to Period (PWM duty cycle in microseconds).
 */
inline float DegToUs(float deg);

/*==================================================================================
 * This selects the key positions for the motion controller to leave the current
 * shelf.
 *
 * This results in the arm being left outside of the current shelf.
 */
void RemoveFork(short currentShelf);

/*==================================================================================
 * This selects the key positions for the motion controller to enter the current
 * shelf.
 *
 * This results int he arm being left inside of the current shelf.
 */
void InsertFork(short currentShelf);

/*==================================================================================
 * This selects the key positions for the motion controller to move from the outside
 * of the current shelf to the outside of the target shelf.
 */
void MoveToShelf(short currentShelf, short targetShelf);

#endif
