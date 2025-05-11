#ifndef LED_INT_H
#define LED_INT_H

typedef unsigned char U_CHAR;

#define LED_OUT_LOW  0
#define LED_OUT_HIGH 1

typedef struct{
    U_CHAR LED_PORT;
    U_CHAR LED_PIN;
    U_CHAR LED_CONNECTIVITY;
}LED_TYPE;


LED_TYPE LED_INIT(U_CHAR port , U_CHAR pin);
void LED_ON(LED_TYPE * LED_CONFIG);
void LED_OFF(LED_TYPE * LED_CONFIG);


#endif
