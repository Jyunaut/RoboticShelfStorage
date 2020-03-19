#include "Initializations.h"
#include "Interrupts.h"
#include "Handlers.h"

int main()
{
    InitPortFInterrupt();
    InitPortBPWM();
}
