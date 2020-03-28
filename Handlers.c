#include "Handlers.h"

extern short curShelf;
float targetPos[2] = {250, 105};

void HandlePortFInterrupt()
{
    curShelf++;


}
