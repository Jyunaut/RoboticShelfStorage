#include <math.h>
#include "Initializations.h"
#include "Interrupts.h"

const float PI = (float)M_PI;
const float ARM_LINK_LENGTH = 250;       // mm, both links are same length
const float US_PER_DEG = 8.33333333333;  // TODO needs calibration. = 1500 us / 180 deg, but datasheet says 1000/180 = 5.55555
const float MOTOR_A_ZERO_ANGLE_US = 500; // TODO these should be calibrated again
const float MOTOR_B_ZERO_ANGLE_US = 470; // TODO these should be calibrated again
const short NUM_SHELVES = 4;

char errorNumber = 0;
short curShelf = 0;
float outputAnglesRad[2] = {0, 0};

int main()
{
    InitPortFInterrupt();
    InitPortBPWM();

    while (1)
    {
        wait_for_interrupts();
    }
}
