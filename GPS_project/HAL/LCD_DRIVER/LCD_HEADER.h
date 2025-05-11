#ifndef LCD_HEADER_H
#define LCD_HEADER_H

// for readability only for me
typedef unsigned char U_Char;
typedef unsigned char Const_U_Char;
typedef unsigned int U_int;

#define NULL (void *)0

void LCD_Port_init();
void LCD_VoidWriteData(U_Char Data);
void LCD_VoidWriteINS(U_Char Instruction);
void LCD_Init();
void LCD_VoidWriteString(Const_U_Char *str);
void LCD_VoidWriteNumber(U_int Number);
void LCD_VoidWriteFloat(float number);
void LCD_GoTo_ROW_COL(U_Char ROW, U_Char COL);
void LCD_Clear();

#endif
