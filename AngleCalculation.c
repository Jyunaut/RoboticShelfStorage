#include "AngleCalculation.h"

extern const float PI;
extern const float ARM_LINK_LENGTH;
extern char errorNumber;

float DegToRad(float deg)
{
    return deg * PI / 180;
}

float RadToDeg(float rad)
{
    return rad * 180 / PI;
}

char GetAngles(float* targetXZCoord, float* outputAnglesRad)
{

    // Calculate hypotenuse length and check if the hypotenuse is longer than
    // the robot agit prm workspace, if so then return an error code
    float lHypotenuse = sqrtf((pow(targetXZCoord[0], 2)) + (pow(targetXZCoord[1], 2)));
    if (lHypotenuse > ARM_LINK_LENGTH * 2)
    {
        return 1;
    }

    // Calculate hypotenuse angle above horizontal
    float aHypotenuse = atan2f(targetXZCoord[0], targetXZCoord[1]);

    // Angle between hypotenuse and link1
    float ang_d = acos((lHypotenuse / 2) / ARM_LINK_LENGTH);

    // Calculate ideal motor angles (error offsets added by motion control)
    outputAnglesRad[0] = PI - aHypotenuse - ang_d;       // Motor A
    outputAnglesRad[1] = (PI / 2) - aHypotenuse + ang_d; // Motor B

    // Check if Motor A out of range
    if (!((outputAnglesRad[0] > DegToRad(40)) && (outputAnglesRad[0] < DegToRad(140))))
    {
        return 2;
    }

    // Check if Motor B out of range TODO this may be too restrictive
    if (!((outputAnglesRad[1] > DegToRad(15)) && (outputAnglesRad[1] < DegToRad(130))))
    {
        return 3;
    }

    // Check if links are pinching
    if (!((outputAnglesRad[0] + DegToRad(65)) > outputAnglesRad[1]))
    {
        return 4;
    }

    // Check if links are overextended
    if (!((outputAnglesRad[0] - outputAnglesRad[1]) > DegToRad(65)))
    {
        return 5;
    }

    // Pass test
    return 0;
}
