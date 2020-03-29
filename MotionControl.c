#include "MotionControl.h"
#include "SystemConstants.h"

float DegToUs(float deg)
{
    // TODO: Convert degrees to PWM duty cycle in microseconds
}

short GetNumberOfSteps(short currentShelf, short currentKeyPosition, short targetKeyPosition)
{
    float xDistance = positions[currentShelf][targetKeyPosition].x - positions[currentShelf][currentKeyPosition].x;
    float zDistance = positions[currentShelf][targetKeyPosition].z - positions[currentShelf][currentKeyPosition].z;

    if (fabsf(xDistance) >= fabsf(zDistance))
    {
        return (short)xDistance;
    }
    return (short)zDistance;
}

void MoveToShelf(short currentShelf, short targetShelf)
{

}

void RemoveFork(short currentShelf)
{

}

void InsertFork(short currentShelf)
{

}

void ReturnHome()
{

}
