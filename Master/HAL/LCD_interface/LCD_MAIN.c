/*
 * LCD_MAIN.c
 *
 *  Created on: Apr 18, 2025
 *      Author: hassa
 */

#include <util/delay.h>
#include "../../Service/STD_TYPES.h"
#include "../../Service/bit_math.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "PRV_int.h"
#include "CLCD_config.h"
#include "LCD_INT.h"

static void Set_Half_Port(u8 Copy_u8Data){
	DIO_voidSetPinValue(CLCD_DATA_PORT , CLCD_DATA_PIN_0 , GET_BIT(Copy_u8Data , 0));
	DIO_voidSetPinValue(CLCD_DATA_PORT , CLCD_DATA_PIN_1 , GET_BIT(Copy_u8Data , 1));
	DIO_voidSetPinValue(CLCD_DATA_PORT , CLCD_DATA_PIN_2 , GET_BIT(Copy_u8Data , 2));
	DIO_voidSetPinValue(CLCD_DATA_PORT , CLCD_DATA_PIN_3 , GET_BIT(Copy_u8Data , 3));
}

static void Send_Enable_Pulse(){
	DIO_voidSetPinValue(CLCD_CTRL_PORT , CLCD_ENABLE_PIN , DIO_HIGH);
	_delay_ms(10);
	DIO_voidSetPinValue(CLCD_CTRL_PORT , CLCD_ENABLE_PIN , DIO_LOW);
}

void CLCD_VoidWriteData(u8 Copy_u8Data){
	//	DIO_voidSetPortDirection(CLCD_DATA_PORT , DIO_Port_OUTPUT);
	//	DIO_voidSetPortDirection(CLCD_CTRL_PORT , DIO_Port_OUTPUT);

	DIO_voidSetPinValue(CLCD_CTRL_PORT , CLCD_RW_PIN , DIO_LOW);
	DIO_voidSetPinValue(CLCD_CTRL_PORT , CLCD_RS_PIN , DIO_HIGH);

#if CLCD_MODE == CLCD_8_BIT
	DIO_voidSetPortValue(CLCD_DATA_PORT , Copy_u8Data);
	Send_Enable_Pulse();

#elif CLCD_MODE == CLCD_4_BIT
	Set_Half_Port(Copy_u8Data >> 4);
	Send_Enable_Pulse();

	Set_Half_Port(Copy_u8Data);
	Send_Enable_Pulse();

#else
#warning  "wrong lcd mode"

#endif
}

void CLCD_VoidWriteINS(u8 Copy_u8INS){

	DIO_voidSetPinValue(CLCD_CTRL_PORT , CLCD_RW_PIN , DIO_LOW);
	DIO_voidSetPinValue(CLCD_CTRL_PORT , CLCD_RS_PIN , DIO_LOW);

#if CLCD_MODE == CLCD_8_BIT
	DIO_voidSetPortValue(CLCD_DATA_PORT , Copy_u8INS);
	Send_Enable_Pulse();

#elif CLCD_MODE == CLCD_4_BIT
	Set_Half_Port(Copy_u8INS >> 4);
	Send_Enable_Pulse();

	Set_Half_Port(Copy_u8INS);
	Send_Enable_Pulse();

#else
#warning  "wrong lcd mode"

#endif
}

void CLCD_VoidInit(){
	/* Wait 40ms for LCD power-up */
	/*wait 40 m*/
	_delay_ms(40);

	#if CLCD_MODE == CLCD_8_BIT
		CLCD_VoidWriteINS(0b000111000);

	#elif CLCD_MODE == CLCD_4_BIT
	    Set_Half_Port(0b0010);
	    Send_Enable_Pulse();

	    Set_Half_Port(0b0010);
	    Send_Enable_Pulse();

	    Set_Half_Port(0b1000);
	    Send_Enable_Pulse();
	#endif

	/*send on/off Control Ob00001110*/
	    CLCD_VoidWriteINS(0b00001110);

	/*clear*/
	    CLCD_VoidWriteINS(1);
}

void CLCD_VoidWriteString(const u8 * Copy_str){
	while(*Copy_str != NULL){
		CLCD_VoidWriteData(* Copy_str ++);

	}
}

void CLCD_VoidWriteNumber(u32 Copy_Number){
    if (Copy_Number == 0) {
        CLCD_VoidWriteData('0');
        return;
    }


	u8 str[20] , i = 0;

	while(Copy_Number > 0){
		str[i++] = Copy_Number % 10;
		Copy_Number /= 10;

	}

	//    while (i > 0) {
	//        CLCD_VoidWriteData(str[--i] + '0');
	//    }

	for(; i > 0 ; ){
		CLCD_VoidWriteData(str[--i] + '0');
	}

	// int power = (int)log10(num);
	// int divisor = (int)pow(10, power);

	// while (divisor > 0) {
    //     int digit = num / divisor;
    //     CLCD_VoidWriteData(digit + '0');
    //     divisor /= 10;
    // }
}

void CLCD_GoTo_XY(u8 X , u8 Y){
	u8 address = X + (Y * 0x40);
	SET_BIT(address , 7);
	CLCD_VoidWriteINS(address);
}

void CLCD_Void_WriteSpecialChar(u8 * Copy_pattern , u8 Copy_index , u8 Copy_u8x , u8 Copy_u8y){

	u8 Local_u8Address = Copy_index * 8;
	SET_BIT(Local_u8Address,6);

	CLCD_VoidWriteINS(Local_u8Address);

	// store it in CGRAM
	for(u8 i = 0 ; i<8 ;i++)
	{
		CLCD_VoidWriteData(Copy_pattern[i]);
	}

	// set x and y
	CLCD_GoTo_XY(Copy_u8x , Copy_u8y);

	//write
	CLCD_VoidWriteData(Copy_index);
}

void LCD_VoidWriteFloat(f32 number) {
    // Handle negative numbers
    if (number < 0) {
    	CLCD_VoidWriteData('-');
        number = -number;
    }

    // Get the integer part
    u32 int_part = (u32)number;
    CLCD_VoidWriteNumber(int_part);  // You already have this function

    // Print the decimal point
    CLCD_VoidWriteData('.');

    // Get the fractional part
    float frac_part = number - int_part;

    // Convert to 2 decimal digits
    frac_part *= 100;

    if (frac_part < 10) {
    	CLCD_VoidWriteData('0');
    }

    CLCD_VoidWriteNumber(frac_part);
}

void CLCD_CLR(){
	CLCD_VoidWriteINS(1);
}