#include "I2C_header.h"

void I2C_Init(void){
    TWSR = 0x00;
    CLR_BIT(TWCR , TWSR_TWPS0);
    CLR_BIT(TWCR , TWSR_TWPS1);

    TWBR = 32;
}

u8 I2C_Start(u8 write_address)
{
    u8 status;
    TWCR=(1 << TWCR_TWSTA) | (1 << TWCR_TWEN) | (1 << TWCR_TWINT);
    while(!(TWCR & (1 << TWCR_TWINT)));

    status = TWSR & 0xF8;

    if(status != 0x08)	return 0;

    TWDR = write_address;
    TWCR = (1<<TWCR_TWEN) | (1 << TWCR_TWINT);

    while(!(TWCR & (1 << TWCR_TWINT)));

    status = TWSR & 0xF8;

    if(status == 0x18) return 1;

    if(status == 0x20) return 2;
    else return 3;
}

u8 I2C_Repeated_Start(u8 read_address)
{
    u8 status;
    TWCR = (1 << TWCR_TWSTA) | (1 << TWCR_TWEN) | (1 << TWCR_TWINT);

    while(!(TWCR & (1 << TWCR_TWINT)));

    status = TWSR & 0xF8;
    if(status != 0x10) return 0;

    TWDR = read_address;
    TWCR = (1 << TWCR_TWEN) | (1 << TWCR_TWINT);

    while(!(TWCR & (1 << TWCR_TWINT)));

    status = TWSR & 0xF8;

    if(status == 0x40) return 1;
    if(status == 0x48) return 2;
    else return 3;
}

u8 I2C_Write(u8 data)
{
    u8 status;
    TWDR = data;
    TWCR = (1 << TWCR_TWEN) | (1 << TWCR_TWINT);

    while(!(TWCR & (1 << TWCR_TWINT)));

    status = TWSR & 0xF8;

    if(status == 0x28) return 0;

    if(status == 0x30) return 1;
    else return 2;
}

u8 I2C_Read_Ack(void)
{
    TWCR = (1 << TWCR_TWEN) | (1 << TWCR_TWINT) | (1 << TWCR_TWEA);
    while(!(TWCR & (1 << TWCR_TWINT)));
    return TWDR;
}

u8 I2C_Read_Nack(void)
{
    TWCR = (1 << TWCR_TWEN) | (1 << TWCR_TWINT);
    while(!(TWCR & (1 << TWCR_TWINT)));
    return TWDR;
}

void I2C_Stop(void)
{
    TWCR = (1 << TWCR_TWSTO) | (1 << TWCR_TWINT) | (1 << TWCR_TWEN);
    while(TWCR & (1 << TWCR_TWSTO));
}

void I2C_Slave_Init(u8 slave_address)
{
    TWAR = slave_address;
    TWCR = (1 << TWCR_TWEN) | (1 << TWCR_TWEA) | (1 << TWCR_TWINT);
}

u8 I2C_Slave_Listen(void)
{
    while(1) {
        u8 reg_status;

        while(!(TWCR & (1 << TWCR_TWINT)));

        reg_status = TWSR & 0xF8;

        if(reg_status == 0x60 || reg_status == 0x68)
            return 0;

        if(reg_status == 0xA8 || reg_status == 0xB0)
            return 1;

        if(reg_status == 0x70 || reg_status == 0x78)
            return 2;
        else
            continue;
    }
}

u8 I2C_Slave_Transmit(u8 reg_data)
{
    u8 reg_status;

    TWDR = reg_data;
    TWCR = (1 <<  TWCR_TWEN) | (1 <<  TWCR_TWINT) | (1 <<  TWCR_TWEA);

    while(!(TWCR & (1 <<  TWCR_TWINT)));

    reg_status = TWSR & 0xF8;

    if(reg_status == 0xA0) {
        TWCR |= (1 <<  TWCR_TWINT);
        return -1;
    }

    if(reg_status == 0xB8)
        return 0;

    if(reg_status == 0xC0) {
        TWCR |= (1 <<  TWCR_TWINT);
        return -2;
    }

    if(reg_status == 0xC8)
        return -3;
    else
        return -4;
}

u8 I2C_Slave_Receive(void)
{
    u8 reg_status;

    TWCR = (1 <<  TWCR_TWEN) | (1 <<  TWCR_TWEA) | (1 <<  TWCR_TWINT);

    while(!(TWCR & (1 <<  TWCR_TWINT)));

    reg_status = TWSR & 0xF8;

    if(reg_status == 0x80 || reg_status == 0x90)
        return TWDR;

    if(reg_status == 0x88 || reg_status == 0x98)
        return TWDR;

    if(reg_status == 0xA0) {
        TWCR |= (1 <<  TWCR_TWINT);
        return -1;
    }
    else
        return -2;
}
