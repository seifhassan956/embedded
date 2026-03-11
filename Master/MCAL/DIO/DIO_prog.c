#include <util/delay.h>
#include "DIO_int.h"



//								port name       pin no            in / out
void DIO_voidSetPinDirection(u8 Copy_u8PortId , u8 Copy_u8PinId , u8 Copy_u8Dir){
	/*	handle pin number */
	if(Copy_u8PinId <= 7)
	{
		if(Copy_u8Dir == DIO_PIN_OUTPUT)
		{
			switch(Copy_u8PortId)
			{
			case DIO_PORTA : SET_BIT(DDRA_REG , Copy_u8PinId); break;
			case DIO_PORTB : SET_BIT(DDRB_REG , Copy_u8PinId); break;
			case DIO_PORTC : SET_BIT(DDRC_REG , Copy_u8PinId); break;
			case DIO_PORTD : SET_BIT(DDRD_REG , Copy_u8PinId); break;
			}
			/*set ddr*/
		}else if(Copy_u8Dir == DIO_PIN_INPUT)
		{
			switch(Copy_u8PortId)
			{
			case DIO_PORTA :CLR_BIT(DDRA_REG , Copy_u8PinId); break;
			case DIO_PORTB :CLR_BIT(DDRB_REG , Copy_u8PinId); break;
			case DIO_PORTC :CLR_BIT(DDRC_REG , Copy_u8PinId); break;
			case DIO_PORTD :CLR_BIT(DDRD_REG , Copy_u8PinId); break;
			}
			/*clear DDR */
		}else {
			/*error */
		}

	}else {
		/*error */
	}
}

							// port name            pin val
void DIO_voidSetPinValue    (u8 Copy_u8PortId , u8 Copy_u8PinId , u8 Copy_u8Val){

	if(Copy_u8Val == DIO_HIGH)
			{
					switch(Copy_u8PortId)
					{
					case DIO_PORTA : SET_BIT(PORTA_REG , Copy_u8PinId); break;
					case DIO_PORTB : SET_BIT(PORTB_REG , Copy_u8PinId); break;
					case DIO_PORTC : SET_BIT(PORTC_REG , Copy_u8PinId); break;
					case DIO_PORTD : SET_BIT(PORTD_REG , Copy_u8PinId); break;
					}

			}else {
				switch(Copy_u8PortId)
				{
				case DIO_PORTA : CLR_BIT(PORTA_REG , Copy_u8PinId); break;
				case DIO_PORTB : CLR_BIT(PORTB_REG , Copy_u8PinId); break;
				case DIO_PORTC : CLR_BIT(PORTC_REG , Copy_u8PinId); break;
				case DIO_PORTD : CLR_BIT(PORTD_REG , Copy_u8PinId); break;
				}
			}
}


u8 DIO_u8GetPinVal(u8 Copy_u8PortId , u8 Copy_u8PinId ){
	u8 temp;

	switch(Copy_u8PortId)
	{
	case DIO_PORTA : temp = GET_BIT(PINA_REG , Copy_u8PinId); break;
	case DIO_PORTB : temp = GET_BIT(PINB_REG , Copy_u8PinId); break;
	case DIO_PORTC : temp = GET_BIT(PINC_REG , Copy_u8PinId); break;
	case DIO_PORTD : temp = GET_BIT(PIND_REG , Copy_u8PinId); break;
	}

	return temp;
}


void DIO_voidSetPortDirection(u8 Copy_u8PortId , u8 Copy_u8Dir){
	/*	handle pin number */
	if(Copy_u8PortId <= 7)
	{
		if(Copy_u8Dir == DIO_Port_OUTPUT)
		{
			switch(Copy_u8PortId)
			{
			case DIO_PORTA : DDRA_REG = Copy_u8Dir; break;
			case DIO_PORTB : DDRB_REG = Copy_u8Dir; break;
			case DIO_PORTC : DDRC_REG = Copy_u8Dir; break;
			case DIO_PORTD : DDRD_REG = Copy_u8Dir; break;
			}
			/*set ddr*/
		}else if(Copy_u8Dir == DIO_PIN_INPUT)
		{
			switch(Copy_u8PortId)
			{
			case DIO_PORTA : DDRA_REG = Copy_u8Dir; break;
			case DIO_PORTB : DDRB_REG = Copy_u8Dir; break;
			case DIO_PORTC : DDRC_REG = Copy_u8Dir; break;
			case DIO_PORTD : DDRD_REG = Copy_u8Dir; break;
			}
			/*clear DDR */
		}else {
			/*error */
		}

	}else {
		/*error */
	}
}


void DIO_voidEnablePullUp(u8 Copy_u8PortId , u8 Copy_u8PinId){
	switch(Copy_u8PortId)
				{
				case DIO_PORTA : SET_BIT(PORTA_REG , Copy_u8PinId); break;
				case DIO_PORTB : SET_BIT(PORTB_REG , Copy_u8PinId); break;
				case DIO_PORTC : SET_BIT(PORTC_REG , Copy_u8PinId); break;
				case DIO_PORTD : SET_BIT(PORTD_REG , Copy_u8PinId); break;
				}
}

							// port name             pin val
void DIO_voidSetPortValue    (u8 Copy_u8PortId , u8 Copy_u8Val){

	if(Copy_u8Val == DIO_Port_OUTPUT)
			{
					switch(Copy_u8PortId)
					{
					case DIO_PORTA : PORTA_REG = Copy_u8Val; break;
					case DIO_PORTB : PORTB_REG = Copy_u8Val; break;
					case DIO_PORTC : PORTC_REG = Copy_u8Val; break;
					case DIO_PORTD : PORTD_REG = Copy_u8Val; break;
					}

			}else if(Copy_u8Val == DIO_Port_INPUT) {
				switch(Copy_u8PortId)
				{
				case DIO_PORTA : PORTA_REG = Copy_u8Val; break;
				case DIO_PORTB : PORTB_REG = Copy_u8Val; break;
				case DIO_PORTC : PORTC_REG = Copy_u8Val; break;
				case DIO_PORTD : PORTD_REG = Copy_u8Val; break;
				}
			}
				else{
					switch(Copy_u8PortId)
						{
						case DIO_PORTA : PORTA_REG = Copy_u8Val; break;
						case DIO_PORTB : PORTB_REG = Copy_u8Val; break;
						case DIO_PORTC : PORTC_REG = Copy_u8Val; break;
						case DIO_PORTD : PORTD_REG = Copy_u8Val; break;
						}
					}
}

u8   DIO_u8GetPortVal        (u8 Copy_u8PortId , u8 Copy_u8PinId ){
				u8 temp;

				switch(Copy_u8PortId)
				{
				case DIO_PORTA : temp = PINA_REG; break;
				case DIO_PORTB : temp = PINB_REG;; break;
				case DIO_PORTC : temp = PINC_REG; break;
				case DIO_PORTD : temp = PIND_REG; break;
				}

				return temp;

}

void binary_counter		    (u8 counter){

	_delay_ms(200);
	DIO_voidSetPinValue(DIO_PORTD , DIO_PIN_6 , (counter >> 0) & 1);
	DIO_voidSetPinValue(DIO_PORTC , DIO_PIN_7 , (counter >> 1) & 1);
	DIO_voidSetPinValue(DIO_PORTC , DIO_PIN_2 , (counter >> 2) & 1);
	DIO_voidSetPinValue(DIO_PORTB , DIO_PIN_3 , (counter >> 3) & 1);

	_delay_ms(20);
	counter = (counter + 1) % 16;

}
