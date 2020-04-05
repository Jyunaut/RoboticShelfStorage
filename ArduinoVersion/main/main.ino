#include <Servo.h>
#include "AngleCalculation.h"
#include "SystemConstants.h"
#include "MotionControl.h"

Servo servoA;
Servo servoB;

short curShelf = 0;
short curKeyPos = 0;

float motorAngles[2] = {0, 0};
float curPos[2] = {positions[curShelf][curKeyPos].x, positions[curShelf][curKeyPos].z};

void setup()
{
    // Set up baud rate and servo connections
    Serial.begin(115200);
    servoA.attach(9);
    servoB.attach(10);

    curPos[0] = 250;
    curPos[1] = 250;
    // Start position at inside of feed shelf
    GetAngles(curPos, motorAngles);
    Serial.print("\n");
    servoA.write(motorAngles[0] + MOTOR_A_NEUTRAL_ANGLE_OFFSET);
    servoB.write(motorAngles[1] + MOTOR_B_NEUTRAL_ANGLE_OFFSET);
    delay(2000);

//    RemoveFork();
//    MoveToShelf(1);
//    InsertFork();
//    RemoveFork();
//    MoveToShelf(0);
//    InsertFork();
//    RemoveFork();
//    MoveToShelf(2);
//    InsertFork();
//    RemoveFork();
//    MoveToShelf(0);
//    InsertFork();
}

void loop()
{
//    MoveTo(200, 200);
//    MoveTo(300, 200);
//    MoveTo(300, 300);
//    MoveTo(200, 300);
}
