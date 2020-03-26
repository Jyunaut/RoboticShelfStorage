#include <math.h>
#include "Initializations.h"
#include "Interrupts.h"
#include "Handlers.h"

const float ARM_LINK_LEN = 250;             // mm, both links are same length
const float servo_UsPerDeg = 8.33333333333; // TODO needs calibration. = 1500 us / 180 deg, but datasheet says 1000/180 = 5.55555
const float motA_angleUsOfZero = 500;       // TODO these should be calibrated again
const float motB_angleUsOfZero = 470;       // TODO these should be calibrated again
const float PI = (float)M_PI;

// Input positions are in mm from the motors' axis to top joint on the fork
// Calling code must provide 2-element array for function to write angles back to
// If returns > 0, then calling code must abort and not move motors output angles
char getAngles(float xPos, float zPos, float* outputAngles)
{
    // Calculate hypotenuse length and angle above horizontal
    float lHypotenuse = sqrtf((pow(xPos, 2)) + (pow(zPos, 2)));
    float aHypotenuse = atan2f(xPos, zPos);
    
    // Target is outside of workspace sphere, acos() will fail
    if (lHypotenuse > (ARM_LINK_LEN * 2))
    {
        return 1;
    }
    else
    {
        // Angle between hypotenuse and link1
        float ang_d = acos((lHypotenuse / 2) / ARM_LINK_LEN);

        // Calculate ideal motor angles (error offsets added by motion control)
        outputAngles[0] = PI - aHypotenuse - ang_d;       // Motor A
        outputAngles[1] = (PI / 2) - aHypotenuse + ang_d; // Motor B

        // Check if angles are valid
        if (!((outputAngles[0] > (40 * PI / 180)) && (outputAngles[0] < (140 * PI / 180))))
        {
            return 2; // Motor A out of range
        }
        if (!((outputAngles[1] > (15 * PI / 180)) && (outputAngles[1] < (130 * PI / 180))))
        {
            return 3; // Motor B out of range TODO this may be too restrictive
        }
        if (!((outputAngles[0] + (65 * PI / 180)) > outputAngles[1]))
        {
            return 4; // Links are pinching
        }
        if (!((outputAngles[0] - outputAngles[1]) > (65 * PI / 180)))
        {
            return 5; // Links are overextended
        }
    }
    return 0;
}

int main()
{
    InitPortFInterrupt();
    InitPortBPWM();
}
