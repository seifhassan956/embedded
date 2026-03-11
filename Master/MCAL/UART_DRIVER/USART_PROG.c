#include "USART_HEADER.h"

void USART_voidInit()
{
    UCSRB |= (1<<UCSRB_RXEN)|(1<<UCSRB_TXEN);
    UCSRC |= (1 << UCSRC_URSEL) | (1 << UCSRC_UCSZ0) | (1 << UCSRC_UCSZ1);
    UBRRL = BAUD_PRESCALE;
    UBRRH = (BAUD_PRESCALE >> 8);
}

u8 USART_voidReadData()
{
   while ((UCSRA & (1 << UCSRA_RXC)) == 0);
   return UDR;
}

void USART_voidSendData(u8 data)
{
   while ((UCSRA & (1 << UCSRA_UDRE)) == 0);
   UDR = data;
}

void USART_voidSendString(u8 *str)
{
    while (*str)
    {
        USART_voidSendData(*str++);
    }
}

void USART_voidReadString(u8 *buffer, u16 maxLen)
{
    u16 i = 0;
    char c;

    while (i < maxLen - 1)
    {
        c = USART_voidReadData();

        if (c == '\r' || c == '\n') // End of line
            break;

        buffer[i++] = c;
    }
    buffer[i] = '\0'; // null terminate
}

void USART_voidSendNumber(u16 num)
{
    char buffer[6];  
    u8 i = 0;

    if (num == 0)
    {
        USART_voidSendData('0');
        return;
    }

    while (num > 0)
    {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    while (i > 0)
    {
        USART_voidSendData(buffer[--i]);
    }
}