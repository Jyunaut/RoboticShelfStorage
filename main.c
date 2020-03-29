#include <math.h>
#include "PLL.h"
#include "SysTickInts.h"
#include "Initializations.h"
#include "Interrupts.h"
#include "SystemConstants.h"

char errorNumber = 0;
short currentShelf = 0;
short targetShelf = 0;
short currentKeyPosition = 0;
short targetKeyPosition = 0;

float outputAnglesRad[2] = {0, 0};
float outputAnglesUs[2]  = {0, 0};

int main()
{
    PLL_Init();
    InitPortFInterrupt();
    InitPortBPWM();
    SysTick_Init(1000);

    while (1)
    {
        wait_for_interrupts();
    }
}
