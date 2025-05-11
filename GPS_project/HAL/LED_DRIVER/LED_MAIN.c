#include "../../SERVICES/BITMATH.h"
#include "../../MCAL/GPIO_DRIVER/GPIO_INT.h"
#include "LED_INT.h"

LED_TYPE LED_INIT(U_CHAR port , U_CHAR pin){
    LED_TYPE myLED;
    myLED.LED_PORT = port;
    myLED.LED_PIN = pin;
    myLED.LED_CONNECTIVITY = LED_OUT_HIGH;

    return myLED;
}

void LED_ON(LED_TYPE *LED_CONFIG)
{
    // Set pin direction first
    GPIO_SetPinDir(LED_CONFIG->LED_PORT,
                   LED_CONFIG->LED_PIN,
                   OUTPUT);

    // Set pin value based on connectivity
    if (LED_CONFIG->LED_CONNECTIVITY == LED_OUT_HIGH)
    {
        GPIO_SetPinValue(LED_CONFIG->LED_PORT,
                         LED_CONFIG->LED_PIN,
                         HIGH);
    }
    else
    {
        GPIO_SetPinValue(LED_CONFIG->LED_PORT,
                         LED_CONFIG->LED_PIN,
                         LOW);
    }
}

void LED_OFF(LED_TYPE *LED_CONFIG)
{
    // Set pin direction first
    GPIO_SetPinDir(LED_CONFIG->LED_PORT,
                   LED_CONFIG->LED_PIN,
                   OUTPUT);

    // Set pin value based on connectivity (inverse of ON)
    if (LED_CONFIG->LED_CONNECTIVITY == LED_OUT_HIGH)
    {
        GPIO_SetPinValue(LED_CONFIG->LED_PORT,
                         LED_CONFIG->LED_PIN,
                         LOW);
    }
    else
    {
        GPIO_SetPinValue(LED_CONFIG->LED_PORT,
                         LED_CONFIG->LED_PIN,
                         HIGH);
    }
}
