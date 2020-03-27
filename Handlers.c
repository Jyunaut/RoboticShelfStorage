#include "Handlers.h"

extern short curShelf;

void HandlePortFInterrupt()
{
    curShelf++;

    float targetXY[2] = {0, 2};

    // TODO: Retrieve arm movement instructions
}
