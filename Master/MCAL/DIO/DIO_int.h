/******************************** ATMEGA 32 Regfile ***********************
 * Auther  		: Eslam El Hefny
 * Version 		: 1.0.0
 * Date    		: 11 April 2025
 * Description  :
 *
 *************************************************************************/

#ifndef MCAL_DIO_DIO_INT_H_
#define MCAL_DIO_DIO_INT_H_

#include "../../Service/STD_TYPES.h"
#include "../../Service/bit_math.h"
#include "../reg.h"

/*Defining port*/
#define DIO_PORTA        0
#define DIO_PORTB        1
#define DIO_PORTC        2
#define DIO_PORTD        3

/*define Pins */
#define DIO_PIN_0        0
#define DIO_PIN_1        1
#define DIO_PIN_2        2
#define DIO_PIN_3        3
#define DIO_PIN_4        4
#define DIO_PIN_5        5
#define DIO_PIN_6        6
#define DIO_PIN_7        7

// set pin val
#define DIO_LOW		 	 0
#define DIO_HIGH 		 1


/*define direction*/
#define DIO_PIN_OUTPUT   1
#define DIO_PIN_INPUT    0

/*define direction*/
#define DIO_Port_OUTPUT   0xff
#define DIO_Port_INPUT    0x0

/*function Header */
void DIO_voidSetPinDirection(u8 Copy_u8PortId , u8 Copy_u8PinId , u8 Copy_u8Dir);
void DIO_voidSetPinValue    (u8 Copy_u8PortId , u8 Copy_u8PinId , u8 Copy_u8Val);
u8   DIO_u8GetPinVal        (u8 Copy_u8PortId , u8 Copy_u8PinId );

void DIO_voidEnablePullUp(u8 Copy_u8PortId , u8 Copy_u8PinId);

void DIO_voidSetPortDirection(u8 Copy_u8PortId , u8 Copy_u8Dir);
void DIO_voidSetPortValue    (u8 Copy_u8PortId , u8 Copy_u8Val);
u8   DIO_u8GetPortVal        (u8 Copy_u8PortId , u8 Copy_u8PinId );

void binary_counter		    (u8 counter);

#endif /* MCAL_DIO_DIO_INT_H_ */
