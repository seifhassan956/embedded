#ifndef GPIO_INT_H
#define GPIO_INT_H

#define GPIOA 0
#define GPIOB 1
#define GPIOC 2
#define GPIOD 3
#define GPIOE 4
#define GPIOF 5

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

#define LOW 0
#define HIGH 1

#define Lock_key 0x4C4F434B

#define INPUT_PU 0
#define INPUT_PD 1

#define OUTPUT 3

/**********		Function Declaretion ***************/

/********** PIN fn **********/
static void initPort_PIN(int port, int pin);
static void PD_INPUT(int port, int pin);
static void PU_INPUT(int port, int pin);

void GPIO_SetPinDir(int port, int pin, int direction);
void GPIO_SetPinValue(int port, int pin, int value);
int GPIO_GetPinValue(int port, int pin);

/********** PORT fn ***************/
static void initPort(int port);
static void PU_INPUT_PORT(int port);
static void PD_INPUT_PORT(int port);

void GPIO_SetPortDir(int port, int direction);
void GPIO_SetPortValue(int port, int value);
int GPIO_GetPortValue(int port);

#endif
