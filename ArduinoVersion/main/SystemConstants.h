#ifndef SYSTEMCONSTANTS_H_
#define SYSTEMCONSTANTS_H_

struct coordinates
{
    float x;
    float z;
};

/* This is a 2D array of 3 key positions for each of the 4 levels in the system in mm
 * Format: {xIn0, zIn0, xInLift0, zInLift0, xOut0, zOut0},
 *         {xIn1, zIn1, xInLift1, zInLift1, xOut1, zOut1},
 *         {xIn2, zIn2, xInLift2, zInLift2, xOut2, zOut2}};
 *
 * Where the numbers dictate the shelf level
 * More Generalized: Shelf: In, InLift, Out
 *
 * TODO: These values may need calibration and I'm not sure if it works yet
*/
static const struct coordinates positions[3][3] = {{260, 120, 250, 190, 125, 160},
                                                   {250, 180, 250, 230, 125, 230},
                                                   {240, 260, 240, 320, 125, 310}};

static const float ARM_LINK_LENGTH = 250;       // mm, both links are same length
static const float MOTOR_A_NEUTRAL_ANGLE_OFFSET = -5; // TODO these should be calibrated again
static const float MOTOR_B_NEUTRAL_ANGLE_OFFSET = -5; // TODO these should be calibrated again

#endif

