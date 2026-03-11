#include "MPU_HEADER.h"

void MPU6050_Init(void){
   I2C_Init();

   // ----------------- Sample Rate -----------------
   I2C_Start(MPU6050_ADDRESS << 1);
   I2C_Write(SMPLRT_DIV);
   I2C_Write(0x07);         // 1kHz/(1+7) = 125Hz sample rate
   I2C_Stop();

   // ---------------- Power Management -------------
   I2C_Start(MPU6050_ADDRESS << 1);
   I2C_Write(PWR_MGMT_1);
   I2C_Write(0x00);
   I2C_Stop();

   // ---------------- DLPF Config ------------------
   I2C_Start(MPU6050_ADDRESS << 1);
   I2C_Write(CONFIG);
   I2C_Write(0x05);
   I2C_Stop();

   // --------------- Accelerometer FSR -------------
   I2C_Start(MPU6050_ADDRESS << 1);
   I2C_Write(ACCEL_CONFIG);
   I2C_Write(0x10);         // ±8g full scale
   I2C_Stop();

   // ---------------- Gyroscope FSR ----------------
   I2C_Start(MPU6050_ADDRESS << 1);
   I2C_Write(GYRO_CONFIG);
   I2C_Write(0x10);         // ±1000°/s (or change to 0x00 for ±250°/s)
   I2C_Stop();

   // ------------- Enable Data Ready Interrupt -----
   I2C_Start(MPU6050_ADDRESS << 1);
   I2C_Write(INT_ENABLE);
   I2C_Write(0x01);         // Enable interrupt
   I2C_Stop();
}

void MPU6050_Read(MPU_Data* data)
{
   s16 Ax, Ay, Az, Gx, Gy, Gz, T;
   f32 AX, AY, AZ, GX, GY, GZ;

   // Start communication
   I2C_Start(MPU6050_ADDRESS << 1);
   I2C_Write(ACCEL_XOUT_H);
   I2C_Repeated_Start((MPU6050_ADDRESS << 1) | 0x01);

   // Read raw accelerometer and gyro data
   Ax = (s16)((I2C_Read_Ack() << 8) | I2C_Read_Ack());
   Ay = (s16)((I2C_Read_Ack() << 8) | I2C_Read_Ack());
   Az = (s16)((I2C_Read_Ack() << 8) | I2C_Read_Ack());
   T  = (s16)((I2C_Read_Ack() << 8) | I2C_Read_Ack());
   Gx = (s16)((I2C_Read_Ack() << 8) | I2C_Read_Ack());
   Gy = (s16)((I2C_Read_Ack() << 8) | I2C_Read_Ack());
   Gz = (s16)((I2C_Read_Ack() << 8) | I2C_Read_Nack());

   I2C_Stop();

   // Convert raw values to physical units
   AX = (f32)Ax / 4096.0;   // ±8g
   AY = (f32)Ay / 4096.0;
   AZ = (f32)Az / 4096.0;

   AZ -= 0.05;

   GX = (f32)Gx / 32.8;      // ±1000°/s
   GY = (f32)Gy / 32.8;
   GZ = (f32)Gz / 32.8;

   // Store in data struct
   data->Accel_X = AX;
   data->Accel_Y = AY;
   data->Accel_Z = AZ;

   data->Gyro_X = GX;
   data->Gyro_Y = GY;
   data->Gyro_Z = GZ;

}

void calculate_angles(MPU_Data* data)
{
   f32 AX = data->Accel_X - data->AX_CAL;
   f32 AY = data->Accel_Y - data->AY_CAL;
   f32 AZ = data->Accel_Z - data->AZ_CAL;

   f32 accRoll  = atan2(AY, sqrt(AX*AX + AZ*AZ)) * 180.0 / PI;
   f32 accPitch = atan2(-AX, sqrt(AY*AY + AZ*AZ)) * 180.0 / PI;

   data->Roll  = accRoll;
   data->Pitch = accPitch;
   data->Yaw += data->Gyro_Z * 0.008f;
}
