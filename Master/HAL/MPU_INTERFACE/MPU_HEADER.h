#ifndef MPU_HEADER_H
#define MPU_HEADER_H

#include "../../Service/STD_TYPES.h"
#include "../../MCAL/I2C_DRIVER/I2C_header.h"
#include "../../MCAL/UART_DRIVER/USART_HEADER.h"
#include "../../MCAL/reg.h"
#include <math.h>
#include <util/delay.h>
#include "../LCD_interface/LCD_INT.h"

#define MPU6050_ADDRESS         0x68
#define PI                      3.1415926

#define DT 0.008f
static f32 gyroAngleX = 0.0f;
static f32 gyroAngleY = 0.0f;
static f32 yawAngle   = 0.0f;

typedef struct {
    f32 Accel_X , Accel_Y , Accel_Z;
    f32 Gyro_X , Gyro_Y , Gyro_Z;

    f32 AX_CAL , AY_CAL , AZ_CAL;
    f32 GX_CAL , GY_CAL , GZ_CAL;

    f32 Roll , Pitch , Yaw;
} MPU_Data;

void MPU6050_Init(void);
void MPU6050_Read(MPU_Data* data);
void calculate_angles(MPU_Data* data);

#endif
