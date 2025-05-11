#ifndef SYSTICK_H
#define SYSTICK_H

typedef unsigned int uint32_t;

/* System Control Registers */
#define SYSCTL_RCC_R        (*((volatile uint32_t *)0x400FE060))
#define SYSCTL_RCC2_R       (*((volatile uint32_t *)0x400FE070))
#define SYSCTL_RIS_R        (*((volatile uint32_t *)0x400FE050))

/* Bit Definitions */
#define RCC_XTAL_16MHZ      0x00000540
#define RCC2_USERCC2        0x80000000
#define RCC2_BYPASS2        0x00000800
#define RCC2_DIV400         0x40000000
#define RIS_PLLLRIS         0x00000040
#define RCC2_SYSDIV2_80MHZ  (4 << 22)

/* SysTick Registers */
#define NVIC_ST_CTRL_R      (*((volatile uint32_t *)0xE000E010))
#define NVIC_ST_RELOAD_R    (*((volatile uint32_t *)0xE000E014))
#define NVIC_ST_CURRENT_R   (*((volatile uint32_t *)0xE000E018))

/* SysTick Control Bits */
#define ST_CTRL_ENABLE      (1U << 0)
#define ST_CTRL_TICKINT     (1U << 1)
#define ST_CTRL_CLKSRC      (1U << 2)
#define ST_CTRL_COUNTFLAG   (1U << 16)

/* Clock Configuration */
#define SYSTEM_CLK_FREQ     80000000UL
#define SYSTICK_1MS_DELAY   (SYSTEM_CLK_FREQ/1000UL)
#define SYSTICK_1US_DELAY   (SYSTEM_CLK_FREQ/1000000UL)

void SysTick_Init();
void _delay_ms(uint32_t milliseconds);
void _delay_us(uint32_t microseconds);

#endif