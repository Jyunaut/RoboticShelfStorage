#include "AngleCalculation.h"

extern const float PI;
extern const float ARM_LINK_LENGTH;
extern char errorNumber;

float DegToRad(float deg)
{
    return deg * PI / 180;
}

void GetAngles(float xPos, float zPos, float* outputAnglesRad)
{

    // Calculate hypotenuse length and angle above horizontal
    float lHypotenuse = sqrtf((pow(xPos, 2)) + (pow(zPos, 2)));
    float aHypotenuse = atan2f(xPos, zPos);

    // Angle between hypotenuse and link1
    float ang_d = acos((lHypotenuse / 2) / ARM_LINK_LENGTH);

    // Calculate ideal motor angles (error offsets added by motion control)
    outputAnglesRad[0] = PI - aHypotenuse - ang_d;       // Motor A
    outputAnglesRad[1] = (PI / 2) - aHypotenuse + ang_d; // Motor B
}

char ValidateAngles(float xPos, float zPos, float* outputAnglesRad)
{
    float lHypotenuse = sqrtf((pow(xPos, 2)) + (pow(zPos, 2)));

    // Target is outside of workspace sphere, acos() will fail
    if (lHypotenuse > (ARM_LINK_LENGTH * 2))
    {
        return 1;
    }

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
