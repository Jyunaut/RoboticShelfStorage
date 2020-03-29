#include "Initializations.h"

const long CLOCK = 16000; // Desired PWM frequency

void InitPortFInterrupt()
{
    // Set up GPIO functionality on PortF
    SYSCTL_RCGC2_R |= 0x00000020;                   // activate clock for PortF
    while ((SYSCTL_PRGPIO_R & 0x00000020) == 0) {}; // wait until PortF is ready
    GPIO_PORTF_LOCK_R = 0x4C4F434B;                 // unlock GPIO PortF
    GPIO_PORTF_CR_R = 0x1F;                         // allow changes to PF4-0
    GPIO_PORTF_AMSEL_R = 0x00;                      // disable analog on PortF
    GPIO_PORTF_PCTL_R = 0x00000000;                 // use PF4-0 as GPIO
    GPIO_PORTF_DIR_R = 0x0E;                        // PF4,PF0 in, PF3-1 out
    GPIO_PORTF_AFSEL_R = 0x00;                      // disable alt function on PF
    GPIO_PORTF_PUR_R = 0x11;                        // enable pull-up on PF0,PF4
    GPIO_PORTF_DEN_R = 0x1F;                        // enable digital I/O on PF4-0

    // Set up PortF for interrupts
    GPIO_PORTF_IS_R &= ~0x00;
    GPIO_PORTF_IBE_R &= ~0x00;
    GPIO_PORTF_IEV_R &= ~0x00;
    GPIO_PORTF_ICR_R = 0x10;
    GPIO_PORTF_IM_R |= 0x10;

    NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF) | 0x00A00000;
    NVIC_EN0_R = 0x40000000;
}

void InitPortBPWM()
{
    SYSCTL_RCGC0_R |= 0x00100000;       // Enable PWM Clock
    SYSCTL_RCGC2_R |= 0x00000002;       // Use Module B
    SYSCTL_RCC_R &= 0x00100000;         // Use PWM divide and set PWM divider to divide by 2

    GPIO_PORTB_AFSEL_R = 0x00000040;    // Enable the alternate function for PB6
    GPIO_PORTB_PCTL_R &= ~0x0F000000;   // Clear GPIO Port Control
    GPIO_PORTB_PCTL_R = 0x04000000;     // Enable Module 0 PWM Generator 0 (M0PWM0) on PB6
    GPIO_PORTB_DEN_R = 0x40;            // Enable digital signals on PB6

    PWM0_0_CTL_R = 0;                   // Disable timers in PWM Generator
    PWM0_0_GENA_R = 0x0000008C;         // Enable settings so that the controller will drive PWMA low when counter matches comparator A
                                        // while counting down and drive PWMA high when counter matches the value in the PWM0LOAD register
    PWM0_0_LOAD_R = CLOCK;              // 1/100 Hz = 0.01 s -> PWM divide => 80/2 = 40 MHz -> Clock ticks per period = 40 x 10^6 * 0.01 = 400000 ticks/period
    PWM0_0_CMPA_R = CLOCK - 1;          // Set to 0% duty cycle -> initial value
    PWM0_0_CTL_R = 1;                   // Enable timers in PWM Generator
    PWM0_ENABLE_R = 0x00000003;         // Enable PWM outputs
}
