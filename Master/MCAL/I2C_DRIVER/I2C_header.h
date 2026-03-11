#ifndef I2C_HEADER_H
#define I2C_HEADER_H

#include "../reg.h"
#include "../../Service/STD_TYPES.h"
#include "../../Service/bit_math.h"
#include <math.h>

/* Define bit rate */
#define F_CPU 16000000UL
#define SCL_CLK 1600000UL
#define BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWSR_TWPS0)|(1<<TWSR_TWPS1)))))

#define I2C_PORT DIO_PORTC
#define I2C_SCL 0
#define I2C_SDA 1

void I2C_Init(void);
u8 I2C_Start(u8 write_address);
u8 I2C_Repeated_Start(u8 read_address);
void I2C_Stop(void);

u8 I2C_Write(u8 data);
u8 I2C_Read(u8 ack);
u8 I2C_Read_Nack(void);
u8 I2C_Read_Ack(void);

void I2C_Slave_Init(u8 slave_address);
u8 I2C_Slave_Listen(void);
u8 I2C_Slave_Transmit(u8 reg_data);
u8 I2C_Slave_Receive(void);

#endif