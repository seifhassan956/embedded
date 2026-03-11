/*
 * PRV_int.h
 *
 *  Created on: Apr 19, 2025
 *      Author: hassa
 */

#ifndef HAL_LCD_INTERFACE_PRV_INT_H_
#define HAL_LCD_INTERFACE_PRV_INT_H_

#define CLCD_4_BIT 0
#define CLCD_8_BIT 1

static void Set_Half_Port(u8 Copy_u8Data);
static void Send_Enable_Pulse();

#endif /* HAL_LCD_INTERFACE_PRV_INT_H_ */
