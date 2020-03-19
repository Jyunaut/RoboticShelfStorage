#include "Interrupts.h"

/* Disable interrupts by setting the I bit in the PRIMASK system register */
void disable_interrupts(void)
{
    __asm("    CPSID  I\n"
          "    BX     LR");
}

/* Enable interrupts by clearing the I bit in the PRIMASK system register */
void enable_interrupts(void)
{
    __asm("    CPSIE  I\n"
          "    BX     LR");
}

/* Enter low-power mode while waiting for interrupts */
void wait_for_interrupts(void)
{
    __asm("    WFI\n"
          "    BX     LR");
}
