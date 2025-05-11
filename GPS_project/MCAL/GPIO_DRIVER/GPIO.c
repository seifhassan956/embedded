#include "../../SERVICES/tm4c123gh6pm.h"
#include "../../SERVICES/BITMATH.h"
#include "GPIO_INT.h"

/********** PIN fn **********/
static void initPort_PIN(int port, int pin)
{
    SETBIT(SYSCTL_RCGCGPIO_R, port);
    while ((SYSCTL_PRGPIO_R & (1 << port)) == 0);

    switch (port)
    {
        case GPIOA:

            GPIO_PORTA_LOCK_R = Lock_key;
            SETBIT(GPIO_PORTA_CR_R, pin);
            SETBIT(GPIO_PORTA_DEN_R, pin);
            CLRBIT(GPIO_PORTA_AMSEL_R, pin);
            GPIO_PORTA_PCTL_R &= ~((0xF) << pin);
            GPIO_PORTA_AFSEL_R = 0x00;
            break;

        case GPIOB:

            GPIO_PORTB_LOCK_R = Lock_key;
            SETBIT(GPIO_PORTB_CR_R, pin);
            SETBIT(GPIO_PORTB_DEN_R, pin);
            CLRBIT(GPIO_PORTB_AMSEL_R, pin);
            GPIO_PORTB_PCTL_R &= ~((0xF) << pin);
            GPIO_PORTB_AFSEL_R = 0x00;
            break;

        case GPIOC:

            GPIO_PORTC_LOCK_R = Lock_key;
            SETBIT(GPIO_PORTC_CR_R, pin);
            SETBIT(GPIO_PORTC_DEN_R, pin);
            CLRBIT(GPIO_PORTC_AMSEL_R, pin);
            GPIO_PORTC_PCTL_R &= ~((0xF) << pin);
            GPIO_PORTC_AFSEL_R = 0x00;
            break;

        case GPIOD:

            GPIO_PORTD_LOCK_R = Lock_key;
            SETBIT(GPIO_PORTD_CR_R, pin);
            SETBIT(GPIO_PORTD_DEN_R, pin);
            CLRBIT(GPIO_PORTD_AMSEL_R, pin);
            GPIO_PORTD_PCTL_R &= ~((0xF) << pin);
            GPIO_PORTD_AFSEL_R = 0x00;
            break;

        case GPIOF:

            GPIO_PORTF_LOCK_R = Lock_key;
            SETBIT(GPIO_PORTF_CR_R, pin);
            SETBIT(GPIO_PORTF_DEN_R, pin);
            CLRBIT(GPIO_PORTF_AMSEL_R, pin);
            GPIO_PORTF_PCTL_R &= ~((0xF) << pin);
            GPIO_PORTF_AFSEL_R = 0x00;
            // GPIO_PORTF_DEN_R = 0x1F;
            break;

        default:
            // Invalid port
            break;
    }
}

static void PD_INPUT(int port, int pin)
{
    switch (port)
        {
            case GPIOA:
                CLRBIT(GPIO_PORTA_DIR_R, pin);
                CLRBIT(GPIO_PORTA_PUR_R, pin);    // Disable pull-up
                SETBIT(GPIO_PORTA_PDR_R, pin);    // Enable pull-down
                break;


            case GPIOB:
                CLRBIT(GPIO_PORTB_DIR_R, pin);
                CLRBIT(GPIO_PORTB_PUR_R, pin);    // Disable pull-up
                SETBIT(GPIO_PORTB_PDR_R, pin);    // Enable pull-down
                break;


            case GPIOC:
                CLRBIT(GPIO_PORTC_DIR_R, pin);
                CLRBIT(GPIO_PORTC_PUR_R, pin);    // Disable pull-up
                SETBIT(GPIO_PORTC_PDR_R, pin);    // Enable pull-down
                break;


            case GPIOD:
                CLRBIT(GPIO_PORTD_DIR_R, pin);
                CLRBIT(GPIO_PORTD_PUR_R, pin);    // Disable pull-up
                SETBIT(GPIO_PORTD_PDR_R, pin);    // Enable pull-down
                break;


            case GPIOF:
                    CLRBIT(GPIO_PORTF_DIR_R, pin);
                    CLRBIT(GPIO_PORTF_PUR_R, pin);    // Disable pull-up
                    SETBIT(GPIO_PORTF_PDR_R, pin);    // Enable pull-down
                break;

                
            default: return; // invalid port
        }
}

static void PU_INPUT(int port, int pin)
{
    switch (port)
        {
            case GPIOA:
                CLRBIT(GPIO_PORTA_DIR_R, pin);
                SETBIT(GPIO_PORTA_PUR_R, pin);    // ENABLE pull-up
                CLRBIT(GPIO_PORTA_PDR_R, pin);    // Disable pull-down
                break;


            case GPIOB:
                CLRBIT(GPIO_PORTB_DIR_R, pin);
                SETBIT(GPIO_PORTB_PUR_R, pin);    // ENABLE pull-up
                CLRBIT(GPIO_PORTB_PDR_R, pin);    // Disable pull-down
                break;


            case GPIOC:
                CLRBIT(GPIO_PORTC_DIR_R, pin);
                SETBIT(GPIO_PORTC_PUR_R, pin);    // ENABLE pull-up
                CLRBIT(GPIO_PORTC_PDR_R, pin);    // Disable pull-down
                break;


            case GPIOD:
                CLRBIT(GPIO_PORTD_DIR_R, pin);
                SETBIT(GPIO_PORTD_PUR_R, pin);    // ENABLE pull-up
                CLRBIT(GPIO_PORTD_PDR_R, pin);    // Disable pull-down
                break;


            case GPIOF:
                    CLRBIT(GPIO_PORTF_DIR_R, pin);
                    SETBIT(GPIO_PORTF_PUR_R, pin);    // ENABLE pull-up
                    CLRBIT(GPIO_PORTF_PDR_R, pin);    // Disable pull-downn
                break;

                
            default: return; // invalid port
        }
}


void GPIO_SetPinDir(int port, int pin, int direction)
{
    if (pin < 0 || pin > 7)
        return;

    initPort_PIN(port, pin);

    switch (direction)
    {
        case INPUT_PD: PD_INPUT(port , pin); break;

        case INPUT_PU: PU_INPUT(port , pin); break;

        case OUTPUT:
            switch (port)
            {
                case GPIOA: SETBIT(GPIO_PORTA_DIR_R, pin); break;

                case GPIOB: SETBIT(GPIO_PORTB_DIR_R, pin); break;

                case GPIOC: SETBIT(GPIO_PORTC_DIR_R, pin); break;

                case GPIOD: SETBIT(GPIO_PORTD_DIR_R, pin); break;

                case GPIOF: SETBIT(GPIO_PORTF_DIR_R, pin);

                default: return; // invalid port
            }
        break;

        default: return; // invalid direction
    }
}

void GPIO_SetPinValue(int port, int pin, int value)
{
    if (pin < 0 || pin > 7)
        return;

    if (value == HIGH)
        {
            switch (port)
            {
                case GPIOA: SETBIT(GPIO_PORTA_DATA_R, pin); break;

                case GPIOB: SETBIT(GPIO_PORTB_DATA_R, pin); break;

                case GPIOC: SETBIT(GPIO_PORTC_DATA_R, pin); break;

                case GPIOD: SETBIT(GPIO_PORTD_DATA_R, pin); break;

                case GPIOF: SETBIT(GPIO_PORTF_DATA_R, pin); break;
            }
        }
    else if (value == LOW)
        {
            switch (port)
            {
                case GPIOA: CLRBIT(GPIO_PORTA_DATA_R, pin); break;

                case GPIOB: CLRBIT(GPIO_PORTB_DATA_R, pin); break;

                case GPIOC: CLRBIT(GPIO_PORTC_DATA_R, pin); break;

                case GPIOD: CLRBIT(GPIO_PORTD_DATA_R, pin); break;

                case GPIOF: CLRBIT(GPIO_PORTF_DATA_R, pin); break;
            }
        }
    else
        return;         // invalid value
}

int GPIO_GetPinValue(int port, int pin)
{
    if (pin < 0 || pin > 7)
        return 0;

    switch (port)
    {
        case GPIOA: return GETBIT(GPIO_PORTA_DATA_R, pin);

        case GPIOB: return GETBIT(GPIO_PORTB_DATA_R, pin);

        case GPIOC: return GETBIT(GPIO_PORTC_DATA_R, pin);

        case GPIOD: return GETBIT(GPIO_PORTD_DATA_R, pin);

        case GPIOF: return GETBIT(GPIO_PORTF_DATA_R, pin);

        default: return 0; // invalid port
    }
}





/********** PORT fn **********/
static void initPort(port)
{
    SETBIT(SYSCTL_RCGCGPIO_R, port);
    while ((SYSCTL_PRGPIO_R & (1 << port)) == 0);

    switch (port) {
            case GPIOA:
                GPIO_PORTA_LOCK_R = Lock_key;
                GPIO_PORTA_CR_R = 0xFF;       // Allow all PA7-0 changes
                GPIO_PORTA_AMSEL_R = 0x00;    // Disable analog
                GPIO_PORTA_PCTL_R = 0x00000000; // Clear PCTL
                GPIO_PORTA_AFSEL_R = 0x00;    // GPIO mode
                GPIO_PORTA_DEN_R = 0xFF;      // Digital enable all
                break;
                
            case GPIOB:
                GPIO_PORTB_LOCK_R = Lock_key;
                GPIO_PORTB_CR_R = 0xFF;
                GPIO_PORTB_AMSEL_R = 0x00;
                GPIO_PORTB_PCTL_R = 0x00000000;
                GPIO_PORTB_AFSEL_R = 0x00;
                GPIO_PORTB_DEN_R = 0xFF;
                break;
                
            case GPIOC:
                GPIO_PORTC_LOCK_R = Lock_key;
                GPIO_PORTC_CR_R = 0xFF;
                GPIO_PORTC_AMSEL_R = 0x00;
                GPIO_PORTC_PCTL_R = 0x00000000;
                GPIO_PORTC_AFSEL_R = 0x00;
                GPIO_PORTC_DEN_R = 0xF0;      // Only PC7-4 on TM4C123
                break;
                
            case GPIOD:
                GPIO_PORTD_LOCK_R = Lock_key;
                GPIO_PORTD_CR_R = 0xFF;
                GPIO_PORTD_AMSEL_R = 0x00;
                GPIO_PORTD_PCTL_R = 0x00000000;
                GPIO_PORTD_AFSEL_R = 0x00;
                GPIO_PORTD_DEN_R = 0xFF;
                break;
                
            case GPIOF:
                GPIO_PORTF_LOCK_R = Lock_key;
                GPIO_PORTF_CR_R = 0x1F;       // Only allow PF4-0 changes
                GPIO_PORTF_AMSEL_R = 0x00;
                GPIO_PORTF_PCTL_R = 0x00000000;
                GPIO_PORTF_AFSEL_R = 0x00;
                GPIO_PORTF_DEN_R = 0x1F;      // Only PF4-0
                GPIO_PORTF_PUR_R = 0x11;      // Enable pull-up on PF0 and PF4
                break;
                
        default: break;                       // Handle error if needed 
    }
}

static void PD_INPUT_PORT(int port){
    switch (port)
    {
        case GPIOA:
            GPIO_PORTA_DIR_R = 0x00;      // All pins input
            GPIO_PORTA_PUR_R = 0x00;      // Disable pull-up
            GPIO_PORTA_PDR_R = 0xFF;      // Enable pull-down
            break;

        case GPIOB:
            GPIO_PORTB_DIR_R = 0x00;
            GPIO_PORTB_PUR_R = 0x00;
            GPIO_PORTB_PDR_R = 0xFF;
            break;

        case GPIOC:
            GPIO_PORTC_DIR_R = 0x00;
            GPIO_PORTC_PUR_R = 0x00;
            GPIO_PORTC_PDR_R = 0xFF;
            break;

        case GPIOD:
            GPIO_PORTD_DIR_R = 0x00;
            GPIO_PORTD_PUR_R = 0x00;
            GPIO_PORTD_PDR_R = 0xFF;
            break;

        case GPIOF:
            GPIO_PORTF_DIR_R = 0x00;
            GPIO_PORTF_PUR_R = 0x00;
            GPIO_PORTF_PDR_R = 0x1F; // Only PF0–PF4 exist
            break;

        default:
            return; // Invalid port
    }
}

static void PU_INPUT_PORT(int port)
{
    switch (port)
    {
        case GPIOA:
            GPIO_PORTA_DIR_R = 0x00;      // All pins input
            GPIO_PORTA_PUR_R = 0xff;      // Enable pull-up
            GPIO_PORTA_PDR_R = 0x00;      // Disable pull-down
            break;

        case GPIOB:
            GPIO_PORTB_DIR_R = 0x00;
            GPIO_PORTB_PUR_R = 0xff;      // Enable pull-up
            GPIO_PORTB_PDR_R = 0x00;      // Disable pull-down
            break;

        case GPIOC:
            GPIO_PORTC_DIR_R = 0x00;
            GPIO_PORTC_PUR_R = 0xff;      // Enable pull-up
            GPIO_PORTC_PDR_R = 0x00;      // Disable pull-down
            break;

        case GPIOD:
            GPIO_PORTD_DIR_R = 0x00;
            GPIO_PORTD_PUR_R = 0xff;      // Enable pull-up
            GPIO_PORTD_PDR_R = 0x00;      // Disable pull-down
            break;

        case GPIOF:
            GPIO_PORTF_DIR_R = 0x00;
            GPIO_PORTF_PUR_R = 0x1F;
            GPIO_PORTF_PDR_R = 0x00; // Only PF0–PF4 exist
            break;

        default:
            return; // Invalid port
    }
}



void GPIO_SetPortDir(int port, int direction)
{
    initPort(port);

    switch (direction)
    {
        case OUTPUT:
            switch (port)
            {
                case GPIOA: GPIO_PORTA_DIR_R = 0xff; break;

                case GPIOB: GPIO_PORTB_DIR_R = 0xff; break;

                case GPIOC: GPIO_PORTC_DIR_R = 0xff; break;

                case GPIOD: GPIO_PORTD_DIR_R = 0xff; break;

                case GPIOF: GPIO_PORTF_DIR_R = 0xff; break;

                default: return; // invalid port
            }
            break;
            
        case INPUT_PD: PD_INPUT_PORT(port); break;

        case INPUT_PU: PU_INPUT_PORT(port); break;
    
    default: break;
    }
}

void GPIO_SetPortValue(int port , int value)
{
    switch (port)
    {
        case GPIOA: GPIO_PORTA_DATA_R = value; break;

        case GPIOB: GPIO_PORTB_DATA_R = value; break;

        case GPIOC: GPIO_PORTC_DATA_R = value; break;

        case GPIOD: GPIO_PORTD_DATA_R = value; break;

        case GPIOF: GPIO_PORTF_DATA_R = value; break;
    }
}

int GPIO_GetPortValue(int port)
{
    switch (port)
    {
        case GPIOA: return GETBIT(GPIO_PORTA_DATA_R, 0xff);

        case GPIOB: return GETBIT(GPIO_PORTB_DATA_R, 0xff);

        case GPIOC: return GETBIT(GPIO_PORTC_DATA_R, 0xff);

        case GPIOD: return GETBIT(GPIO_PORTD_DATA_R, 0xff);

        case GPIOF: return GETBIT(GPIO_PORTF_DATA_R, 0x11);

        default: return 0; // invalid port
    }
}
