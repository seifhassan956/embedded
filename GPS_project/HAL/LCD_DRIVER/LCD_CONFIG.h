#ifndef HAL_LCD_INTERFACE_CLCD_CONFIG_H_
#define HAL_LCD_INTERFACE_CLCD_CONFIG_H_

#define LCD_DATA_PORT GPIOA
#define LCD_CTRL_PORT GPIOB

// 4 bit mode

// port A
#define LCD_DATA_PIN_0     PIN4
#define LCD_DATA_PIN_1     PIN5
#define LCD_DATA_PIN_2     PIN6
#define LCD_DATA_PIN_3     PIN7

// port B
#define LCD_RW_PIN          PIN0
#define LCD_RS_PIN          PIN1
#define LCD_ENABLE_PIN      PIN2

#define LCD_8_BIT 1
#define LCD_4_BIT 0
#define LCD_MODE LCD_4_BIT

#endif