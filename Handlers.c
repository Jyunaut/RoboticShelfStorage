#include "Handlers.h"
#include "SystemConstants.h"
#include "Interrupts.h"

extern short targetShelf;
extern short currentShelf;
extern short keyPosition;
extern float period;

void HandlePortFInterrupt()
{
    GPIO_PORTF_ICR_R = 0x10;
    disable_interrupts();

    targetShelf = targetShelf + 1;

    period += 625 / 3;
    if (period > 2500)
    {
        period = 1250;
    }
    enable_interrupts();
}
