#include "AngleCalculation.h"
#include "SystemConstants.h"

/* =================================================================================
 * Calculates Degrees to Radians.
 */
static inline float DegToRad(float deg)
{
    return deg * PI / 180;
}

/* =================================================================================
 * Calculates Radians to Degrees.
 */
static inline float RadToDeg(float rad)
{
    return rad * 180 / PI;
}

/* =================================================================================
 * This causes the system to remain in an infinite loop if the system catches an
 * error.
 */
void GoToErrorState(char errorMessage[])
{
    Serial.print("\n");
    Serial.print(errorMessage);
    Serial.print("\t");
    while (1) {};
}

void GetAngles(float* stepPos, float* motorAngles)
{
    // Calculate hypotenuse length and check if the hypotenuse is longer than
    // the robot agit prm workspace, if so then return an error code
    float lHypotenuse = sqrt((pow(stepPos[0], 2)) + (pow(stepPos[1], 2)));
    if (lHypotenuse > ARM_LINK_LENGTH * 2)
    {
        GoToErrorState("Target position exceeds workspace.");
    }

    // Calculate hypotenuse angle above horizontal
    float aHypotenuse = atan2(stepPos[1], stepPos[0]);

    // Angle between hypotenuse and link1
    float ang_d = acos((lHypotenuse / 2) / ARM_LINK_LENGTH);
    
    // Calculate ideal motor angles (error offsets added by motion control)
    motorAngles[0] = RadToDeg(PI - aHypotenuse - ang_d);       // Motor A
    Serial.print("Motor A Angle: ");
    Serial.print(motorAngles[0], 3);
    Serial.print("\t");
    
    motorAngles[1] = RadToDeg((PI / 2) - aHypotenuse + ang_d); // Motor B
    Serial.print("Motor B Angle: ");
    Serial.print(motorAngles[1], 3);
    Serial.print("\t");
    
    // Check if Motor A out of range
    if (!((motorAngles[0] > 40) && (motorAngles[0] < 140)))
    {
        GoToErrorState("Motor A angle out of range.");
    }

    // Check if Motor B out of range TODO this may be too restrictive
//    if (!((motorAngles[1] > 15) && (motorAngles[1] < 130)))
//    {
//        GoToErrorState("Motor B angle out of range.");
//    }

    // Check if links are pinching
    if (!((motorAngles[0] + 65) > motorAngles[1]))
    {
        GoToErrorState("Links are pinching.");
    }

    // Check if links are overextended
    if (!((motorAngles[0] - motorAngles[1]) < 65))
    {
        GoToErrorState("Links are overextended.");
    }
}
