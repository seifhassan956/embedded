/*
 * LCD_INT.h
 *
 *  Created on: Apr 18, 2025
 *      Author: hassa
 */

#ifndef HAL_LCD_INTERFACE_LCD_INT_H_
#define HAL_LCD_INTERFACE_LCD_INT_H_

void CLCD_VoidWriteData(u8 Copy_u8Data);
void CLCD_VoidWriteINS(u8 Copy_u8INS);
void CLCD_VoidInit();
void CLCD_VoidWriteString(const u8 * Copy_str);
void CLCD_VoidWriteNumber(u32 Copy_Number);
void LCD_VoidWriteFloat(f32 number);
void CLCD_GoTo_XY(u8 X , u8 Y);
void CLCD_Void_WriteSpecialChar(u8 * Copy_pattern , u8 Copy_index , u8 Copy_u8x , u8 Copy_u8y);
void CLCD_CLR();

#endif /* HAL_LCD_INTERFACE_LCD_INT_H_ */
