#include "../reg.h"
#include "../../Service/STD_TYPES.h"
#include "../../Service/bit_math.h"
#include "../DIO/DIO_int.h"
#include "timer0_header.h"

void (*TIMER0_PF)(void);
void (*TIMER0_PF_C2C)(void);

void TIMER0_voidInit(u8 Copy_u8Prescaler , u8 Copy_u8MODE)
{
    TCCR0 &= 0b11111000;
    TCCR0 |= Copy_u8Prescaler;

    switch (Copy_u8MODE)
    {
    case TIMER0_Normal_Mode:
                            SET_BIT(TIMSK , TIMER0_TIMSK_TOIE0);
                            break;
    case TIMER0_C2C_Mode:
                            CLR_BIT(TIMSK , TIMER0_TCCR0_WGM00);
                            SET_BIT(TIMSK , TIMER0_TCCR0_WGM01);
                            SET_BIT(TIMSK , TIMER0_TIMSK_OCIE0);
                            break;
    default:
        break;
    }

}

void TIMER0_PWM_INIT(u8 Mode , u8 Copy_u8Prescaler){
    TCCR0 &= 0b11111000;
    TCCR0 |= Copy_u8Prescaler;

    switch (Mode)
    {
    case TIMER0_FPWM_Mode:
        SET_BIT(TCCR0 , TIMER0_TCCR0_WGM00);
        SET_BIT(TCCR0 , TIMER0_TCCR0_WGM01);
        break;

    case TIMER0_PhaseCorrect_PWM_Mode:
        SET_BIT(TCCR0 , TIMER0_TCCR0_WGM00);
        CLR_BIT(TCCR0 , TIMER0_TCCR0_WGM01);
        break;
    
    default:
        break;
    }

    

    CLR_BIT(TCCR0 , TIMER0_TCCR0_COM00);
    SET_BIT(TCCR0 , TIMER0_TCCR0_COM01);

    SET_BIT(TIMSK , TIMER0_TIMSK_OCIE0);
}

void TIMER0_voidSetPreload(u8 Copy_u8Preload)
{
    TCNT0 = Copy_u8Preload;
}

void TIMER0_voidSetCallBack(void (*pf)(void))
{
    TIMER0_PF = pf;
}

void TIMER0_voidSetOCR_VAL(u8 Copy_u8OCR_VAL)
{
    OCR0 = Copy_u8OCR_VAL;
}

void TIMER0_C2C_Action(u8 Copy_u8Mode)
{
    TCCR0 &= 0b11001111;
    TCCR0 |= Copy_u8Mode << 4;
}

void TIMER0_voidSetCallBack_C2C(void (*pf)(void))
{
    TIMER0_PF_C2C = pf;
}

void __vector_11(void) __attribute__ ((signal));
void __vector_11(void){
    if (TIMER0_PF != NULL)
    {
        TIMER0_PF();
    }
}

void __vector_10(void) __attribute__ ((signal));
void __vector_10(void)
{
    if (TIMER0_PF_C2C != NULL)
    {
        TIMER0_PF_C2C();
    }
}
