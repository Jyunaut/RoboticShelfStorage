#include "Handlers.h"

extern short targetShelf;
extern short keyPosition;

void HandlePortFInterrupt()
{
    GPIO_PORTF_ICR_R = 0x10;

    targetShelf = targetShelf + 1;

}
