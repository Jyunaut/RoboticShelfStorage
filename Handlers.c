#include "Handlers.h"

extern short curShelf;
extern short keyPosition;

void HandlePortFInterrupt()
{
    GPIO_PORTF_ICR_R = 0x10;
    curShelf = curShelf + 1;


}
