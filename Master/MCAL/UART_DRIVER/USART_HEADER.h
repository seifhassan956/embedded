#ifndef USART_HEADER_H_
#define USART_HEADER_H_

#include "../../Service/STD_TYPES.h"
#include "../reg.h"

#define F_CPU 16000000UL
#define USART_BAUDRATE 38400
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void USART_voidInit();
void USART_voidSendData(u8 data);
u8 USART_voidReadData(void);
void USART_voidSendString(u8 *str);
void USART_voidReadString(u8 *buffer, u16 max_len);

#endif
