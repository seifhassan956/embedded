/*
 * CLCD_config.h
 *
 *  Created on: Apr 18, 2025
 *      Author: hassa
 */

#ifndef HAL_LCD_INTERFACE_CLCD_CONFIG_H_
#define HAL_LCD_INTERFACE_CLCD_CONFIG_H_

#define CLCD_DATA_PORT DIO_PORTA
#define CLCD_CTRL_PORT DIO_PORTB

// 4 bit mode
#define CLCD_DATA_PIN_0 DIO_PIN_4
#define CLCD_DATA_PIN_1 DIO_PIN_5
#define CLCD_DATA_PIN_2 DIO_PIN_6
#define CLCD_DATA_PIN_3 DIO_PIN_7

#define CLCD_RS_PIN DIO_PIN_1
#define CLCD_RW_PIN DIO_PIN_0
#define CLCD_ENABLE_PIN DIO_PIN_2

#define CLCD_MODE  CLCD_4_BIT

#endif /* HAL_LCD_INTERFACE_CLCD_CONFIG_H_ */
