#include "MAIN_HEADER.h"

u8 angle_to_pwm(f32 angle)
{
    if (angle > MAX_ANGLE)
        angle = MAX_ANGLE;
    if (angle < -MAX_ANGLE)
        angle = -MAX_ANGLE;

    if (angle < 0)
        angle = -angle;

    return (u8)((angle / MAX_ANGLE) * MAX_PWM);
}

u8 get_direction(MPU_Data *m)
{
    if (m->Pitch > DEADZONE)
        return 'F';
    if (m->Pitch < -DEADZONE)
        return 'B';
    if (m->Roll > DEADZONE)
        return 'R';
    if (m->Roll < -DEADZONE)
        return 'L';
    return 'S';
}

int main(void)
{
    USART_voidInit();
    MPU6050_Init();

    MPU_Data mpu_Data;

    u8 dir, pwm;

    while (1)
    {
        MPU6050_Read(&mpu_Data);
        calculate_angles(&mpu_Data);

        dir = get_direction(&mpu_Data);

        if (dir == 'F' || dir == 'B')
            pwm = angle_to_pwm(mpu_Data.Pitch);
        else if (dir == 'L' || dir == 'R')
            pwm = angle_to_pwm(mpu_Data.Roll);
        else
            pwm = 0;

        USART_voidSendData('<');
        USART_voidSendData(dir);
        USART_voidSendData(',');
        USART_voidSendNumber(pwm);
        USART_voidSendData('>');
        USART_voidSendData('\n');

        _delay_ms(20);
    }

    return 0;
}
