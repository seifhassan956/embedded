#include "../../SERVICES/tm4c123gh6pm.h"
#include "../../SERVICES/BITMATH.h"
// #include "../../MCAL/GPIO_DRIVER/GPIO_INT.h"
#include "../../SERVICES/tm4c123gh6pm.h"
#include "SYSTICK_HEADER.h"

void SysTick_Init(void)
{
    /* ---------- Clock Initialization ---------- */
    // 1. Use RCC2 and bypass PLL during initialization
    SYSCTL_RCC2_R |= RCC2_USERCC2 | RCC2_BYPASS2;

    // 2. Set crystal frequency to 16MHz
    SYSCTL_RCC_R = (SYSCTL_RCC_R & ~0x000007C0) | RCC_XTAL_16MHZ;
    SYSCTL_RCC2_R &= ~0x00000070;

    // 3. Configure for main oscillator source (MOSC)
    SYSCTL_RCC2_R |= 0x00000000;

    // 4. Power up PLL and set 80MHz system clock
    SYSCTL_RCC2_R &= ~0x00002000;
    SYSCTL_RCC2_R |= RCC2_DIV400;
    SYSCTL_RCC2_R = (SYSCTL_RCC2_R & ~0x1FC00000) | RCC2_SYSDIV2_80MHZ;

    // 5. Wait for PLL lock
    while ((SYSCTL_RIS_R & RIS_PLLLRIS) == 0)
    {
        __asm("nop");
    }

    // 6. Enable PLL
    SYSCTL_RCC2_R &= ~RCC2_BYPASS2;

    /* ---------- SysTick Initialization ---------- */
    NVIC_ST_CTRL_R = 0;            // Disable SysTick
    NVIC_ST_RELOAD_R = 0x00FFFFFF; // Max reload value
    NVIC_ST_CURRENT_R = 0;         // Clear counter
    NVIC_ST_CTRL_R = ST_CTRL_CLKSRC | ST_CTRL_ENABLE;
}

static void SysTick_Wait(uint32_t cycles)
{
    NVIC_ST_RELOAD_R = cycles - 1;
    NVIC_ST_CURRENT_R = 0;
    while ((NVIC_ST_CTRL_R & ST_CTRL_COUNTFLAG) == 0)
    {
        __asm("nop");
    }
}

void _delay_ms(uint32_t milliseconds)
{
    while (milliseconds--)
    {
        SysTick_Wait(SYSTICK_1MS_DELAY);
    }
}

void _delay_us(uint32_t microseconds)
{
    while (microseconds >= 1000)
    {
        _delay_ms(1);
        microseconds -= 1000;
    }
    while (microseconds--)
    {
        SysTick_Wait(SYSTICK_1US_DELAY);
    }
} 