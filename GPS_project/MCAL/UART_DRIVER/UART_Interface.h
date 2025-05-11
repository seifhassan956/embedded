#ifndef UART_Interface_H
#define UART_Interface_H


#define SYSCTL_RCC_R        (*((volatile unsigned int *)0x400FE060))
#define SYSCTL_RCC2_R       (*((volatile unsigned int *)0x400FE070))
#define SYSCTL_RIS_R        (*((volatile unsigned int *)0x400FE050))

#define BIT0 0
#define BIT1 1
#define BIT2 2
#define BIT3 3
#define BIT4 4
#define BIT5 5
#define BIT6 6

#define CPU_CLK_F 16000000L
#define BoudRate_CLK_F 9600L

#define wordlength_5 0
#define wordlength_6 1
#define wordlength_7 2
#define wordlength_8 3

#define UART0_Enable 0
#define FIFO_Enable 4
#define Transmit_Enable 8
#define Receive_Enable 9

#define AF_UART 0X11

/**************	    Functions declaration 	****************/
void UART0_Init();
char UART0_ReadChar();
char *UART0_ReadString();
void UART0_SendChar(const unsigned char data);
void UART0_SendString(const unsigned char *data);

#endif
