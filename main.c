#include <math.h>
#include "PLL.h"
#include "SysTickInts.h"
#include "Initializations.h"
#include "Interrupts.h"

struct coordinates
{
    float x;
    float y;
};

/* This is a 2D array of 3 key positions for each of the 4 levels in the system in mm
 * Format: {xIn1, zIn1, xInLift1, zInLift1, xOut1, zOut1},
 *         {xIn2, zIn2, xInLift2, zInLift2, xOut2, zOut2},
 *         {xIn3, zIn3, xInLift3, zInLift3, xOut3, zOut3},
 *         {xIn4, zIn4, xInLift4, zInLift4, xOut4, zOut4}};
 *
 * Where the numbers dictate the shelf level
 * More Generalized: Shelf: In, InLift, Out
 *
 * TODO: These values may need calibration and I'm not sure if it works yet
*/
const struct coordinates positions[4][3] = {{300, 100, 300, 120, 150, 120},
                                            {300, 200, 300, 220, 150, 220},
                                            {300, 300, 300, 320, 150, 320},
                                            {300, 400, 300, 420, 150, 420}};

const float PI = (float)M_PI;
const float ARM_LINK_LENGTH = 250;       // mm, both links are same length
const float US_PER_DEG = 8.33333333333;  // TODO needs calibration. = 1500 us / 180 deg, but datasheet says 1000/180 = 5.55555
const float MOTOR_A_ZERO_ANGLE_US = 500; // TODO these should be calibrated again
const float MOTOR_B_ZERO_ANGLE_US = 470; // TODO these should be calibrated again

char errorNumber = 0;
short curShelf = 0;
short keyPosition = 0;

float outputAnglesRad[2] = {0, 0};
float outputAnglesUs[2]  = {0, 0};

int main()
{
    PLL_Init();
    InitPortFInterrupt();
    InitPortBPWM();
    SysTick_Init(1000);

    while (1)
    {
        wait_for_interrupts();
    }
}
