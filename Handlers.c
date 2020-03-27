#include "Handlers.h"

extern short curShelf;

void HandlePortFInterrupt()
{
    curShelf++;

    float lel[2] = {0, 2};

    GetAngles(1, 1, lel);
    ValidateAngles(1, 1, lel);
}
