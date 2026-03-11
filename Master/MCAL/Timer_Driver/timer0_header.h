#ifndef TIMER0_HEADER_H_
#define TIMER0_HEADER_H_

#define TIMER0_Normal_Mode 0
#define TIMER0_C2C_Mode 1
#define TIMER0_FPWM_Mode 2
#define TIMER0_PhaseCorrect_PWM_Mode 3

#define TIMER0_PRESCALER_1024 4
#define TIMER0_PRESCALER_256 3
#define TIMER0_PRESCALER_64 2
#define TIMER0_PRESCALER_8 1

#define TIMER0_Disable 0

#define TIMER0_TOGGLE 1
#define TIMER0_CLEAR 2
#define TIMER0_SET 3

void TIMER0_voidInit(u8 Copy_u8Prescaler , u8 Copy_u8MODE);
void TIMER0_voidSetPreload(u8 Copy_u8Preload);
void TIMER0_voidSetCallBack(void (*pf)(void));

void TIMER0_voidSetCallBack_C2C(void (*pf)(void));
void TIMER0_voidSetOCR_VAL(u8 Copy_u8OCR_VAL);
void TIMER0_C2C_Action(u8 Copy_u8Mode);

void TIMER0_PWM_INIT(u8 Mode , u8 Copy_u8Prescaler);

#endif
