#include "../SERVICES/tm4c123gh6pm.h"
#include "../SERVICES/BITMATH.h"
#include "../MCAL/GPIO_DRIVER/GPIO_INT.h"
#include "../MCAL/UART_DRIVER/UART_Interface.h"
#include "../MCAL/SYSTICK_DRIVER/SYSTICK_HEADER.h"
#include "../HAL/LED_DRIVER/LED_INT.h"
#include "../HAL/LCD_DRIVER/LCD_CONFIG.h"
#include "../HAL/LCD_DRIVER/LCD_HELPER.h"
#include "../HAL/LCD_DRIVER/LCD_HEADER.h"
#include "../HAL/GPS_INTERFACE/GPS_HEADER.h"
#include <string.h>

int main()
{   
    char x=1000000;
    char buffer[20];
    float lat = 0;
    float lon = 0;
    char i;
    // char flag_idx;
    float distance , min_distance;
    char min_index;

    DESTINATION HALL_A;
    DESTINATION HALL_C;
    DESTINATION CREDIT_BUILDING;
    DESTINATION OLD_BUILDING;
    DESTINATION LOBAN;
    DESTINATION locations[5];

    GPS_Data current_coordinate;

    HALL_C.latitude = 3003.82127;
    HALL_C.latitude_dir = 'N';
    HALL_C.longitude = 3116.82863;
    HALL_C.longitude_dir = 'E';
    strcpy(HALL_C.name , "HALL C");
    
    HALL_A.latitude = 3003.85077;
    HALL_A.latitude_dir = 'N';
    HALL_A.longitude = 3116.82471;
    HALL_A.longitude_dir = 'E';
    strcpy(HALL_A.name , "HALL A");


    



    CREDIT_BUILDING.latitude = 3003.76598;
    CREDIT_BUILDING.latitude_dir = 'N';
    CREDIT_BUILDING.longitude = 3116.69671;
    CREDIT_BUILDING.longitude_dir = 'E';
    strcpy(CREDIT_BUILDING.name , "CREDIT BUILDING");


    LOBAN.latitude = 3003.79092;
    LOBAN.latitude_dir = 'N';
    LOBAN.longitude = 3116.77034;
    LOBAN.longitude_dir = 'E';
    strcpy(LOBAN.name , "LOBAN");


    OLD_BUILDING.latitude =  3003.89588;
    OLD_BUILDING.latitude_dir = 'N';
    OLD_BUILDING.longitude = 3116.78896;
    OLD_BUILDING.longitude_dir = 'E';
    strcpy(OLD_BUILDING.name , "OLD BUILDING");


    //assign to array
    locations[0] = HALL_A;
    locations[1] = HALL_C;
    locations[2] = CREDIT_BUILDING;
    locations[3] = LOBAN;
    locations[4] = OLD_BUILDING;

    LCD_Init();

    LCD_VoidWriteString("start:");
    
    _delay_ms(2000);
    LCD_Clear();
    // LCD_test();

    UART0_Init();

    GPIO_SetPinDir(GPIOF , PIN1 , OUTPUT);

    while (1)
    {   
        // for (i = 0; i < 200; i++)
        // {
        //     GPS_READ(&current_coordinate);
        //     lat += stringToFloatManual(current_coordinate.latitude);
        //     lon += stringToFloatManual(current_coordinate.longitude);
        // }

        // lat /= 200.0f;
        // lon /= 200.0f;
        
        // float_to_string(lat , buffer , 6);
        // strcpy(current_coordinate.latitude, buffer);

        // float_to_string(lon , buffer , 6);
        // strcpy(current_coordinate.longitude, buffer);


        GPS_READ(&current_coordinate);
    

        if(current_coordinate.status == 'A'){
           
            //min_distance = GPS_CalculateDistance(&current_coordinate, &locations[0]);
            min_distance = 10000;
            min_index = 0;

            for (i = 0; i < 5; i++)
            {
                distance = GPS_CalculateDistance(&current_coordinate , &locations[i]);
                if (distance < min_distance)
                {
                    min_distance = distance;
                    min_index = i;
                }
            }

            LCD_GoTo_ROW_COL(0, 0);
            LCD_VoidWriteString(locations[min_index].name);

            // LCD_GoTo_ROW_COL(1, 0);
            // LCD_VoidWriteFloat(min_distance);
        }

        if (min_distance <= 50)
        {   
            
            GPIO_SetPinValue(GPIOF , PIN1 , HIGH);
            _delay_ms(2000);
            GPIO_SetPinValue(GPIOF , PIN1 , LOW);
        }
        
        
        _delay_ms(1000);
        LCD_Clear();
    }
}
//$GPRMC,192734.00,,A,,3003.85283,,N,,03116.74838,,E,,0.440,,123.344,070525,,,A*7E