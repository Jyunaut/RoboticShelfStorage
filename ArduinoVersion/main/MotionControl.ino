#include "MotionControl.h"
#include "SystemConstants.h"

extern Servo servoA;
extern Servo servoB;

extern float curPos[2];
extern float motorAngles[2];
extern short curShelf;
extern short curKeyPos;

short delayTime = 800; // in ms

/* ================================================================================
 * Calculates the step size for the motors so that they have the same number of
 * steps. This assumes one step per mm.
 */
short GetNumberOfSteps(short tarShelf, short tarKeyPos)
{
    float xDistance = abs(positions[tarShelf][tarKeyPos].x - positions[curShelf][curKeyPos].x);
    float zDistance = abs(positions[tarShelf][tarKeyPos].z - positions[curShelf][curKeyPos].z);

    if (xDistance >= zDistance)
    {
        return (short)xDistance;
    }
    return (short)zDistance;
}

/* ================================================================================
 * Updates the current X and Z positions of the arm end effector.
 */
void UpdateMotors(short tarShelf, short tarKeyPos, short numSteps, short iteration)
{
    float stepSizeX = (positions[tarShelf][tarKeyPos].x - positions[curShelf][curKeyPos].x) / numSteps;
    float stepSizeZ = (positions[tarShelf][tarKeyPos].z - positions[curShelf][curKeyPos].z) / numSteps;
    curPos[0] = positions[curShelf][curKeyPos].x + stepSizeX * iteration;
    curPos[1] = positions[curShelf][curKeyPos].z + stepSizeZ * iteration;

    GetAngles(curPos, motorAngles);
    servoA.write(motorAngles[0]);
    servoB.write(motorAngles[1]);
}

void PrintCoordinates()
{
    Serial.print("X: ");
    Serial.print(curPos[0]);
    Serial.print("\t");
    Serial.print("Z: ");
    Serial.print(curPos[1]);
    Serial.print("\t");
    Serial.print("curShelf: ");
    Serial.print(curShelf);
    Serial.print("\t");
    Serial.print("curKeyPos: ");
    Serial.print(curKeyPos);
    Serial.print("\n");
}

void MoveToShelf(short tarShelf, short tarKeyPos)
{
    short numSteps = GetNumberOfSteps(tarShelf, tarKeyPos);

    // Return if the target position is the same as the current
    if (numSteps == 0) return;
    for (short i = 1; i <= numSteps; i++)
    {
        UpdateMotors(tarShelf, tarKeyPos, numSteps, i);
        Serial.print("Move to shelf ");
        Serial.print(tarShelf);
        Serial.print("\t");
        PrintCoordinates();
    }
    // Update position values
    curShelf = tarShelf;
    curKeyPos = tarKeyPos;
}

void RemoveFork()
{
    short tarKeyPos = 0;
    short numSteps = 0;

    // Lift fork (Only for feed shelf)
    if (curShelf == 0)
    {
        tarKeyPos = 1;
        numSteps = GetNumberOfSteps(curShelf, tarKeyPos);

        // Return if the target position is the same as the current
        if (numSteps == 0) return;
        for (short i = 1; i <= numSteps; i++)
        {
            UpdateMotors(curShelf, tarKeyPos, numSteps, i);
            Serial.print("Lifting fork");
            Serial.print("\t");
            PrintCoordinates();
        }
        // Update position values
        curKeyPos = tarKeyPos;
        delay(delayTime);
    }

    // Pull fork out
    tarKeyPos = 2;
    numSteps = GetNumberOfSteps(curShelf, tarKeyPos);

    // Return if the target position is the same as the current
    if (numSteps == 0) return;
    for (short i = 1; i <= numSteps; i++)
    {
        UpdateMotors(curShelf, tarKeyPos, numSteps, i);
        Serial.print("Removing fork");
        Serial.print("\t");
        PrintCoordinates();
    }
    // Update position values
    curKeyPos = tarKeyPos;
    delay(delayTime);
}

void InsertFork()
{
    // Push fork in
    short tarKeyPos = (curShelf == 0) ? 0 : 1;
    short numSteps = GetNumberOfSteps(curShelf, tarKeyPos);

    // Return if the target position is the same as the current
    if (numSteps == 0) return;
    for (short i = 1; i <= numSteps; i++)
    {
        UpdateMotors(curShelf, tarKeyPos, numSteps, i);
        Serial.print("Inserting fork");
        Serial.print("\t");
        PrintCoordinates();
    }
    curKeyPos = tarKeyPos;
    delay(delayTime);

    // Lower fork
    tarKeyPos = 0;
    numSteps = GetNumberOfSteps(curShelf, tarKeyPos);

    // Return if the target position is the same as the current
    if (numSteps == 0) return;
    for (short i = 1; i <= numSteps; i++)
    {
        UpdateMotors(curShelf, tarKeyPos, numSteps, i);
        Serial.print("Lowering fork");
        Serial.print("\t");
        PrintCoordinates();
    }
    // Update position values
    curKeyPos = tarKeyPos;
    delay(delayTime);
}

void ReturnHome()
{

}

void MoveTo(float x, float z)
{
    float xDistance = abs(curPos[0] - x);
    float zDistance = abs(curPos[1] - z);
    
    short numSteps = (xDistance > zDistance) ? xDistance : zDistance;

    // Return if the target position is the same as the current
    if (numSteps == 0) return;
    for (short i = 1; i <= numSteps; i++)
    {
        float stepSizeX = (x - curPos[0]) / numSteps;
        float stepSizeZ = (z - curPos[1]) / numSteps;

        curPos[0] += stepSizeX * i;
        curPos[1] += stepSizeZ * i;

        GetAngles(curPos, motorAngles);
        servoA.write(motorAngles[0]);
        servoB.write(motorAngles[1]);

        PrintCoordinates();
    }
    delay(delayTime);
}

