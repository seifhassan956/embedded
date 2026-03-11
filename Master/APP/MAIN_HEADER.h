#ifndef MAIN_HEADER_H
#define MAIN_HEADER_H

#include <util/delay.h>
#include "../Service/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../HAL/LCD_interface/CLCD_config.h"
#include "../HAL/LCD_interface/LCD_INT.h"
#include "../MCAL/I2C_DRIVER/I2C_header.h"
#include "../HAL/MPU_INTERFACE/MPU_HEADER.h"
#include "../MCAL/interrupt/interrupt_header.h"
#include "../MCAL/UART_DRIVER/USART_HEADER.h"
#include "../HAL/BT/Bluetooth_header.h"

#define DEADZONE   5.0f
#define MAX_ANGLE  30.0f
#define MAX_PWM    255

#endif
