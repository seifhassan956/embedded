#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

/* UART Baud Rate */
#define BAUD_RATE   9600
#define F_CPU       16000000UL

/* Functions Prototypes */
void UART_Init(void);
void UART_SendChar(char data);
char UART_ReceiveChar(void);
void UART_SendString(const char *str);

#endif
