#include "Handlers.h"

extern short curShelf;
extern short keyPosition;
int x = 0;

void HandlePortFInterrupt()
{
    GPIO_PORTF_ICR_R = 0x10;
    curShelf++;

    x = x + 1;
}
