#include "../../SERVICES/BITMATH.h"
#include "../../MCAL/GPIO_DRIVER/GPIO_INT.h"
#include "../../MCAL/SYSTICK_DRIVER/SYSTICK_HEADER.h"
#include "LCD_CONFIG.h"
#include "LCD_HELPER.h"
#include "LCD_HEADER.h"

static void Set_Half_Port(U_Char Data)
{
	GPIO_SetPinValue(LCD_DATA_PORT, LCD_DATA_PIN_0, GETBIT(Data, 0));
	GPIO_SetPinValue(LCD_DATA_PORT, LCD_DATA_PIN_1, GETBIT(Data, 1));
	GPIO_SetPinValue(LCD_DATA_PORT, LCD_DATA_PIN_2, GETBIT(Data, 2));
	GPIO_SetPinValue(LCD_DATA_PORT, LCD_DATA_PIN_3, GETBIT(Data, 3));
}

static void Send_Enable_Pulse()
{
	GPIO_SetPinValue(LCD_CTRL_PORT, LCD_ENABLE_PIN, HIGH);
	_delay_us(10); // Increased from 1us to 10us
	GPIO_SetPinValue(LCD_CTRL_PORT, LCD_ENABLE_PIN, LOW);
	_delay_us(50); // Increased delay after pulse
}

void LCD_Port_init()
{
	/* Configure Data Port */
	GPIO_SetPinDir(LCD_DATA_PORT, LCD_DATA_PIN_0, OUTPUT);
	GPIO_SetPinDir(LCD_DATA_PORT, LCD_DATA_PIN_1, OUTPUT);
	GPIO_SetPinDir(LCD_DATA_PORT, LCD_DATA_PIN_2, OUTPUT);
	GPIO_SetPinDir(LCD_DATA_PORT, LCD_DATA_PIN_3, OUTPUT);

	/* Configure Control Pins */
	GPIO_SetPinDir(LCD_CTRL_PORT, LCD_RS_PIN, OUTPUT);
	GPIO_SetPinDir(LCD_CTRL_PORT, LCD_RW_PIN, OUTPUT);
	GPIO_SetPinDir(LCD_CTRL_PORT, LCD_ENABLE_PIN, OUTPUT);
}

void LCD_VoidWriteData(U_Char Data)
{
	GPIO_SetPinValue(LCD_CTRL_PORT, LCD_RW_PIN, LOW);
	GPIO_SetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, HIGH);

#if LCD_MODE == LCD_8_BIT
	voidSetPortValue(LCD_DATA_PORT, Data);
	Send_Enable_Pulse();

#elif LCD_MODE == LCD_4_BIT
	Set_Half_Port(Data >> 4);
	Send_Enable_Pulse();

	Set_Half_Port(Data);
	Send_Enable_Pulse();

#else
#warning "wrong lcd mode"

#endif
}

void LCD_VoidWriteINS(U_Char Instruction)
{
	GPIO_SetPinValue(LCD_CTRL_PORT, LCD_RW_PIN, LOW);
	GPIO_SetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, LOW);

#if LCD_MODE == LCD_8_BIT
	voidSetPortValue(LCD_DATA_PORT, Instruction);
	Send_Enable_Pulse();

#elif LCD_MODE == LCD_4_BIT
	Set_Half_Port(Instruction >> 4);
	Send_Enable_Pulse();

	Set_Half_Port(Instruction);
	Send_Enable_Pulse();

#else
#warning "wrong lcd mode"

#endif
}

void LCD_Init()
{
	// int i;
	SysTick_Init();
	LCD_Port_init();

	_delay_ms(50); // Some LCDs need up to 50ms

#if LCD_MODE == LCD_4_BIT
	/* Special 4-bit initialization sequence */
	// for (i = 0; i < 3; i++)
	// {
	// 	Set_Half_Port(0x3);
	// 	Send_Enable_Pulse();
	// 	_delay_ms(i == 0 ? 15 : 5); // 15ms, then 5ms delays
	// }

	Set_Half_Port(0x3);
	Send_Enable_Pulse();
	_delay_ms(15);

	Set_Half_Port(0x3);
	Send_Enable_Pulse();
	_delay_ms(5);

	Set_Half_Port(0x3);
	Send_Enable_Pulse();
	_delay_ms(5);

	/* Switch to 4-bit mode */
	Set_Half_Port(0x2);
	Send_Enable_Pulse();
	_delay_ms(1);

	/* Function Set: 4-bit, 2-line, 5x8 */
	LCD_VoidWriteINS(0x28);
	_delay_ms(1);
#endif

	/* Display Control */
	LCD_VoidWriteINS(0x0C); // Display ON, Cursor OFF
	_delay_ms(1);

	LCD_VoidWriteINS(0x01); // Clear display
	_delay_ms(2);			// Clear needs extra time

	LCD_VoidWriteINS(0x06); // Entry Mode Set
	_delay_ms(1);
}

void LCD_VoidWriteString(Const_U_Char *str)
{
	while (*str != '\0')
	{
		LCD_VoidWriteData(*str++);
	}
}

void LCD_VoidWriteNumber(U_int Number)
{
	U_Char buffer[16];
	int i = 0;

	// Handle zero case
	if (Number == 0)
	{
		LCD_VoidWriteData('0');
		return;
	}

	// Convert number to string (reverse order)
	while (Number > 0)
	{
		buffer[i++] = (Number % 10) + '0';
		Number /= 10;
	}

	// Write digits in correct order
	while (i > 0)
	{
		LCD_VoidWriteData(buffer[--i]);
	}
}

// void LCD_VoidWriteFloat(float number) {
// 	unsigned int int_part;
// 	float frac_part;

//     // Handle negative numbers
//     if (number < 0) {
//     	LCD_VoidWriteData('-');
//         number = -number;
//     }

//     // Get the integer part
//     int_part = (unsigned int)number;
//     LCD_VoidWriteNumber(int_part);  // You already have this function

//     // Print the decimal point
//     LCD_VoidWriteData('.');

//     // Get the fractional part
//     frac_part = number - int_part;

//     // Convert to 2 decimal digits
//     frac_part *= 100;

//     if (frac_part < 10) {
//     	LCD_VoidWriteData('0');
//     }

//     LCD_VoidWriteNumber(frac_part);
// }

void LCD_VoidWriteFloat(float number) {
    unsigned int int_part;
    int frac_part;

    if (number < 0) {
        LCD_VoidWriteData('-');
        number = -number;
    }

    int_part = (unsigned int)number;
    LCD_VoidWriteNumber(int_part);  // Your existing int printer

    LCD_VoidWriteData('.');

    // Get fractional part
    number -= int_part;
    number *= 100.0f;

    frac_part = (int)(number + 0.5f);  // Round properly

    if (frac_part < 10) {
        LCD_VoidWriteData('0');  // leading zero if needed
    }

    LCD_VoidWriteNumber(frac_part);
}


void LCD_GoTo_ROW_COL(U_Char ROW, U_Char COL)
{
	unsigned char address;
	switch (ROW)
	{
	case 0:
		address = 0x00 + COL;
		break;
	case 1:
		address = 0x40 + COL;
		break;
	default:
		address = 0x00 + COL;
		break;
	}
	SETBIT(address, 7); // Set DDRAM address mode
	LCD_VoidWriteINS(address);
}

void LCD_Clear() {
    // Send Clear Display command (0x01)
    LCD_VoidWriteINS(0x01);
    
    // Wait for the command to complete (1.52ms minimum per datasheet)
    _delay_ms(2);  // Using 2ms for safety margin
    
    // Optional: Return cursor to home position (address 0)
    LCD_VoidWriteINS(0x02);
    _delay_ms(2);
}