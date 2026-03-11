#ifndef MCAL_REG_H_
#define MCAL_REG_H_
/*
$1B ($3B) PORTA
$1A ($3A) DDRA
$19 ($39) PINA
$18 ($38) PORTB
$17 ($37) DDRB
$16 ($36) PINB
$15 ($35) PORTC
$14 ($34) DDRC
$13 ($33) PINC
$12 ($32) PORTD
$11 ($31) DDRD
$10 ($30) PIND*/

/*porta regiter file*/
#define PORTA_REG    *( volatile u8*)(0x3B)
#define DDRA_REG     *( volatile u8*)(0x3A)
#define PINA_REG     *( volatile u8*)(0x39)

#define PORTB_REG    *( volatile u8*)(0x38)
#define DDRB_REG     *( volatile u8*)(0x37)
#define PINB_REG     *( volatile u8*)(0x36)

#define PORTC_REG    *( volatile u8*)(0x35)
#define DDRC_REG     *( volatile u8*)(0x34)
#define PINC_REG     *( volatile u8*)(0x33)

#define PORTD_REG    *( volatile u8*)(0x32)
#define DDRD_REG     *( volatile u8*)(0x31)
#define PIND_REG     *( volatile u8*)(0x30)

/* STATUS REGISTER */
#define SREG         *(volatile u8*)(0x5F)   // Status Register (global interrupt enable, flags, etc.)



/* --------------------- EXTERNAL INTERRUPTS --------------------- */

/* General Interrupt Control Register (GICR) */
#define EXTI_GICR_REG        *(volatile u8*)(0x5B)   // Enables external interrupts INT0, INT1, INT2
#define EXTI_GICR_INTI1      7   // Enable bit for INT1
#define EXTI_GICR_INTI0      6   // Enable bit for INT0
#define EXTI_GICR_INTI2      5   // Enable bit for INT2

/* General Interrupt Flag Register (GIFR) */
#define EXTI_GIFR_REG        *(volatile u8*)(0x5A)   // Flags for external interrupts
#define EXTI_GIFR_INTIF1     7   // Interrupt flag for INT1
#define EXTI_GIFR_INTIF0     6   // Interrupt flag for INT0
#define EXTI_GIFR_INTIF2     5   // Interrupt flag for INT2

/* MCU Control Register (MCUCR) - for INT0 & INT1 sensing control */
#define EXTI_MCUCR_REG       *(volatile u8*)(0x55)
#define EXTI_MCUCR_ISC00     0   // Interrupt Sense Control 0, bit0
#define EXTI_MCUCR_ISC01     1   // Interrupt Sense Control 0, bit1

#define EXTI_MCUCR_ISC10     2   // Interrupt Sense Control 1, bit0
#define EXTI_MCUCR_ISC11     3   // Interrupt Sense Control 1, bit1
// Together (ISC01:ISC00) and (ISC11:ISC10) select: Low, Change, Falling, Rising edge trigger

/* MCU Control and Status Register (MCUCSR) - for INT2 sensing */
#define EXTI_MCUCSR_REG      *(volatile u8*)(0x54)
#define EXTI_MCUSR_ISC2      6   // Interrupt Sense Control for INT2 (0 = falling edge, 1 = rising edge)



/* --------------------- ADC REGISTERS --------------------- */

/* ADC Multiplexer Selection Register */
#define ADCMUX      *(volatile u8*)(0x27)    // Select ADC channel and reference voltage

/* ADC Control and Status Register A */
#define ADCSRA      *(volatile u8*)(0x26)    // Enable ADC, start conversion, prescaler, interrupt enable

/* ADC Data Registers */
#define ADCH        *(volatile u16*)(0x25)   // ADC Data High (upper 8 bits if left adjusted)
#define ADCL        *(volatile u16*)(0x24)   // ADC Data Low  (lower 8 bits if right adjusted)

#endif /* MCAL_REG_H_ */

/* --------------------- Timer0 REGISTERS --------------------- */
#define OCR0      *(volatile u8*)(0x5C)
#define TCNT0     *(volatile u8*)(0x52)

#define TIMSK     *(volatile u8*)(0x59)

#define TIMER0_TIMSK_OCIE2 7
#define TIMER0_TIMSK_TOIE2 6
#define TIMER0_TIMSK_TICIE1 5
#define TIMER0_TIMSK_OCIE1A 4
#define TIMER0_TIMSK_OCIE1B 3
#define TIMER0_TIMSK_TOIE1 2
#define TIMER0_TIMSK_OCIE0 1
#define TIMER0_TIMSK_TOIE0 0

#define TIFR      *(volatile u8*)(0x58)

#define TIMER0_TIFR_OCF2  7
#define TIMER0_TIFR_TOV2  6
#define TIMER0_TIFR_ICF1  5
#define TIMER0_TIFR_OCF1A 4
#define TIMER0_TIFR_OCF1B 3
#define TIMER0_TIFR_TOV1  2
#define TIMER0_TIFR_OCF0  1
#define TIMER0_TIFR_TOV0  0

#define TCCR0     *(volatile u8*)(0x53)

#define TIMER0_TCCR0_FOC0 7
#define TIMER0_TCCR0_WGM00 6
#define TIMER0_TCCR0_COM01 5
#define TIMER0_TCCR0_COM00 4
#define TIMER0_TCCR0_WGM01 3
#define TIMER0_TCCR0_CS02 2
#define TIMER0_TCCR0_CS01 1
#define TIMER0_TCCR0_CS00 0

/* --------------------- USART REGISTERS --------------------- */

/* --------------------- USART REGISTERS (ATmega32) --------------------- */

#define UDR     (*(volatile u8*)(0x2C))
#define UCSRA   (*(volatile u8*)(0x2B))
#define UCSRB   (*(volatile u8*)(0x2A))
#define UCSRC   (*(volatile u8*)(0x40))
#define UBRRH   (*(volatile u8*)(0x40))
#define UBRRL   (*(volatile u8*)(0x29))

/* --------------------- UCSRA Bits --------------------- */
#define UCSRA_RXC     7   
#define UCSRA_TXC     6   
#define UCSRA_UDRE    5  
#define UCSRA_FE      4  
#define UCSRA_DOR     3   
#define UCSRA_PE      2  
#define UCSRA_U2X     1  
#define UCSRA_MPCM    0   

/* --------------------- UCSRB Bits --------------------- */
#define UCSRB_RXCIE   7   
#define UCSRB_TXCIE   6   
#define UCSRB_UDRIE   5   
#define UCSRB_RXEN    4   
#define UCSRB_TXEN    3   
#define UCSRB_UCSZ2   2 
#define UCSRB_RXB8    1  
#define UCSRB_TXB8    0   

/* --------------------- UCSRC Bits --------------------- */
#define UCSRC_URSEL   7   
#define UCSRC_UMSEL   6   
#define UCSRC_UPM1    5  
#define UCSRC_UPM0    4   
#define UCSRC_USBS    3
#define UCSRC_UCSZ1   2  
#define UCSRC_UCSZ0   1 
#define UCSRC_UCPOL   0   

/* --------------------- SPI REGISTERS --------------------- */
#define SPCR      *(volatile u8*)(0x2D)

#define SPCR_SPIE 7
#define SPCR_SPE 6
#define SPCR_DORD 5
#define SPCR_MSTR 4
#define SPCR_CPOL 3
#define SPCR_CPHA 2
#define SPCR_SPR1 1
#define SPCR_SPR0 0

#define SPSR      *(volatile u8*)(0x2E)

#define SPSR_SPIF 7
#define SPSR_WCOL 6
#define SPSR_SPI2X 0

#define SPDR      *(volatile u8*)(0x2F)

/* --------------------- I2C REGISTERS --------------------- */

#define TWBR      *(volatile u8*)(0x20)

#define TWSR      *(volatile u8*)(0x21)

#define TWSR_TWS7 7
#define TWSR_TWS6 6
#define TWSR_TWS5 5
#define TWSR_TWS4 4
#define TWSR_TWS3 3
#define TWSR_TWPS1 1
#define TWSR_TWPS0 0

#define TWCR      *(volatile u8*)(0x56)

#define TWCR_TWINT 7    // TWINT: TWI Interrupt Flag
#define TWCR_TWEA 6     // TWEA: TWI Enable Acknowledge Bit
#define TWCR_TWSTA 5    // TWSTA: TWI START Condition Bit
#define TWCR_TWSTO 4    // TWSTO: TWI STOP Condition Bit
#define TWCR_TWWC 3     // TWWC: TWI Write Collision Flag  
#define TWCR_TWEN 2     // TWEN: TWI Enable Bit
#define TWCR_TWIE 0     // TWIE: TWI Interrupt Enable

#define TWDR      *(volatile u8*)(0x23)

#define TWAR      *(volatile u8*)(0x22)

#define TWAR_TWA6 7
#define TWAR_TWA5 6
#define TWAR_TWA4 5
#define TWAR_TWA3 4
#define TWAR_TWA2 3
#define TWAR_TWA1 2
#define TWAR_TWA0 1
#define TWAR_TWGCE 0


//----------[ MPU6050 Register Map ]-----------
#define XG_OFFS_TC         0x00
#define YG_OFFS_TC         0x01
#define ZG_OFFS_TC         0x02
#define X_FINE_GAIN        0x03
#define Y_FINE_GAIN        0x04
#define Z_FINE_GAIN        0x05
#define XA_OFFS_H          0x06
#define XA_OFFS_L_TC       0x07
#define YA_OFFS_H          0x08
#define YA_OFFS_L_TC       0x09
#define ZA_OFFS_H          0x0A
#define ZA_OFFS_L_TC       0x0B
#define XG_OFFS_USRH       0x13
#define XG_OFFS_USRL       0x14
#define YG_OFFS_USRH       0x15
#define YG_OFFS_USRL       0x16
#define ZG_OFFS_USRH       0x17
#define ZG_OFFS_USRL       0x18
#define SMPLRT_DIV         0x19
#define CONFIG             0x1A
#define GYRO_CONFIG        0x1B
#define ACCEL_CONFIG       0x1C
#define FF_THR             0x1D
#define FF_DUR             0x1E
#define MOT_THR            0x1F
#define MOT_DUR            0x20
#define ZRMOT_THR          0x21
#define ZRMOT_DUR          0x22
#define FIFO_EN            0x23
#define I2C_MST_CTRL       0x24
#define I2C_SLV0_ADDR      0x25
#define I2C_SLV0_REG       0x26
#define I2C_SLV0_CTRL      0x27
#define I2C_SLV1_ADDR      0x28
#define I2C_SLV1_REG       0x29
#define I2C_SLV1_CTRL      0x2A
#define I2C_SLV2_ADDR      0x2B
#define I2C_SLV2_REG       0x2C
#define I2C_SLV2_CTRL      0x2D
#define I2C_SLV3_ADDR      0x2E
#define I2C_SLV3_REG       0x2F
#define I2C_SLV3_CTRL      0x30
#define I2C_SLV4_ADDR      0x31
#define I2C_SLV4_REG       0x32
#define I2C_SLV4_DO        0x33
#define I2C_SLV4_CTRL      0x34
#define I2C_SLV4_DI        0x35
#define I2C_MST_STATUS     0x36
#define INT_PIN_CFG        0x37
#define INT_ENABLE         0x38
#define DMP_INT_STATUS     0x39
#define INT_STATUS         0x3A
#define ACCEL_XOUT_H       0x3B
#define ACCEL_XOUT_L       0x3C
#define ACCEL_YOUT_H       0x3D
#define ACCEL_YOUT_L       0x3E
#define ACCEL_ZOUT_H       0x3F
#define ACCEL_ZOUT_L       0x40
#define TEMP_OUT_H         0x41
#define TEMP_OUT_L         0x42
#define GYRO_XOUT_H        0x43
#define GYRO_XOUT_L        0x44
#define GYRO_YOUT_H        0x45
#define GYRO_YOUT_L        0x46
#define GYRO_ZOUT_H        0x47
#define GYRO_ZOUT_L        0x48
#define EXT_SENS_DATA_00   0x49
#define EXT_SENS_DATA_01   0x4A
#define EXT_SENS_DATA_02   0x4B
#define EXT_SENS_DATA_03   0x4C
#define EXT_SENS_DATA_04   0x4D
#define EXT_SENS_DATA_05   0x4E
#define EXT_SENS_DATA_06   0x4F
#define EXT_SENS_DATA_07   0x50
#define EXT_SENS_DATA_08   0x51
#define EXT_SENS_DATA_09   0x52
#define EXT_SENS_DATA_10   0x53
#define EXT_SENS_DATA_11   0x54
#define EXT_SENS_DATA_12   0x55
#define EXT_SENS_DATA_13   0x56
#define EXT_SENS_DATA_14   0x57
#define EXT_SENS_DATA_15   0x58
#define EXT_SENS_DATA_16   0x59
#define EXT_SENS_DATA_17   0x5A
#define EXT_SENS_DATA_18   0x5B
#define EXT_SENS_DATA_19   0x5C
#define EXT_SENS_DATA_20   0x5D
#define EXT_SENS_DATA_21   0x5E
#define EXT_SENS_DATA_22   0x5F
#define EXT_SENS_DATA_23   0x60
#define MOT_DETECT_STATUS  0x61
#define I2C_SLV0_DO        0x63 
#define I2C_SLV1_DO        0x64
#define I2C_SLV2_DO        0x65
#define I2C_SLV3_DO        0x66
#define I2C_MST_DELAY_CTRL 0x67
#define SIGNAL_PATH_RESET  0x68
#define MOT_DETECT_CTRL    0x69
#define USER_CTRL          0x6A
#define PWR_MGMT_1         0x6B
#define PWR_MGMT_2         0x6C
#define BANK_SEL           0x6D
#define MEM_START_ADDR     0x6E
#define MEM_R_W            0x6F
#define DMP_CFG_1          0x70
#define DMP_CFG_2          0x71
#define FIFO_COUNTH        0x72
#define FIFO_COUNTL        0x73
#define FIFO_R_W           0x74
#define WHO_AM_I           0x75