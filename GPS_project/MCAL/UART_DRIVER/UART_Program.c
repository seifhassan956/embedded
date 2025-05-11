#include "../../SERVICES/tm4c123gh6pm.h"
#include "../../SERVICES/BITMATH.H"
#include "../../SERVICES/BITMATH.h"
#include "../GPIO_DRIVER/GPIO_INT.h"
#include "UART_Interface.h"

void UART0_Init() {
    // 1. Configure PLL for 80MHz (unchanged from your code)
    SYSCTL_RCC2_R |= 0x80000000;
    SYSCTL_RCC2_R |= 0x00000800;
    SYSCTL_RCC_R = (SYSCTL_RCC_R & ~0x000007C0) | 0x00000540;
    SYSCTL_RCC2_R &= ~0x00000070;
    SYSCTL_RCC2_R |= 0x40000000;
    SYSCTL_RCC2_R = (SYSCTL_RCC2_R & ~0x1FC00000) | (4 << 22);
    SYSCTL_RCC2_R &= ~0x00000800;
    while((SYSCTL_RIS_R & 0x00000040) == 0);

    // 2. UART Initialization
    SETBIT(SYSCTL_RCGCUART_R, 0); // UART0
    SETBIT(SYSCTL_RCGCGPIO_R, 0); // Port A
    while(!GETBIT(SYSCTL_PRGPIO_R, 0)); // Wait for clock

    CLRBIT(UART0_CTL_R, 0); // Disable UART
    UART0_IBRD_R = 520;     // 80MHz, 9600 baud
    UART0_FBRD_R = 54;
    UART0_LCRH_R = (3 << 5) | (1 << 4); // 8-bit, FIFO
    SETBIT(UART0_CTL_R, 0);  // Enable UART
    SETBIT(UART0_CTL_R, 8);  // TX Enable
    SETBIT(UART0_CTL_R, 9);  // RX Enable

    // GPIO Configuration
    GPIO_PORTA_AFSEL_R |= 0x03;
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & ~0xFF) | 0x11;
    GPIO_PORTA_DEN_R |= 0x03;
}

char UART0_ReadChar()
{

	while (GETBIT(UART0_FR_R, BIT4) != 0);
	return (char)(UART0_DR_R & 0xFF);
}

char string[20];
char *UART0_ReadString()
{
	char DataCome;
	char counter = 0;

	while ((DataCome = UART0_ReadChar()) != '\n')
	{
		string[counter] = DataCome;
		counter++;
	}
	string[counter] = '\0';
	return string;
}

void UART0_SendChar(const unsigned char data)
{
    while (GETBIT(UART0_FR_R, BIT5)) {}  // Wait until TX FIFO not full
    UART0_DR_R = data;
}

void UART0_SendString(const unsigned char *data)
{
    unsigned char counter = 0;
    while (data[counter] != '\0')  
    {
        UART0_SendChar(data[counter]);
        counter++;
    }
}