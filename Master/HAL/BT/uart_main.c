#include "uart.h"

/* UART Initialization */
void UART_Init(void)
{
    uint16_t ubrr;

    ubrr = (F_CPU / (16UL * BAUD_RATE)) - 1;

    /* Set baud rate */
    UBRRH = (uint8_t)(ubrr >> 8);
    UBRRL = (uint8_t)ubrr;

    /* Enable transmitter and receiver */
    UCSRB = (1 << TXEN) | (1 << RXEN);

    /* 8 data bits, 1 stop bit, no parity */
    UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
}

/* Send one character */
void UART_SendChar(char data)
{
    /* Wait until transmit buffer is empty */
    while (!(UCSRA & (1 << UDRE)));

    /* Put data into buffer */
    UDR = data;
}

/* Receive one character */
char UART_ReceiveChar(void)
{
    /* Wait until data is received */
    while (!(UCSRA & (1 << RXC)));

    /* Get and return received data */
    return UDR;
}

/* Send string */
void UART_SendString(const char *str)
{
    while (*str)
    {
        UART_SendChar(*str);
        str++;
    }
}
