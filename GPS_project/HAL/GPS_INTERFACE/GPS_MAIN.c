// #include "../../SERVICES/tm4c123gh6pm.h"
#include "../../SERVICES/BITMATH.h"
#include "../../MCAL/GPIO_DRIVER/GPIO_INT.h"
#include "../../MCAL/UART_DRIVER/UART_Interface.h"
#include "../../HAL/LED_DRIVER/LED_INT.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "GPS_HEADER.h" 

/*
0: $GPRMC
1: Time (HHMMSS)
2: Latitude (DDMM.MMMM)
3: N/S
4: Longitude (DDDMM.MMMM)
5: E/W
6: Speed
7: Course
8: Date
9: Magnetic variation
10: Checksum
*/

float stringToFloatManual(const char* str) {
    float result = 0.0f;
    float decimalPlace = 0.1f;
    int i = 0;

    // Convert integer part
    while (str[i] != '\0' && str[i] != '.') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    // Convert decimal part if exists
    if (str[i] == '.') {
        i++;  // Skip the decimal point
        while (str[i] != '\0') {
            result += (str[i] - '0') * decimalPlace;
            decimalPlace *= 0.1f;
            i++;
        }
    }

    return result;
}

void float_to_string(float number, char* buffer, int precision) {
    int i = 0;
    int int_part;
    float frac_part;
    int temp;
    int digits = 0;
    int j;
    int digit;

    // Limit precision to avoid overflow
    if (precision > 6) precision = 6;

    // Handle negative numbers
    if (number < 0) {
        buffer[i++] = '-';
        number = -number;
    }

    // Extract integer part
    int_part = (int)number;
    frac_part = number - int_part;

    // Convert integer part
    temp = int_part;
    // Count digits
    do {
        digits++;
        temp /= 10;
    } while (temp != 0);

    // Convert integer part in reverse order
    temp = int_part;
    for (j = digits - 1; j >= 0; j--) {
        buffer[i + j] = (temp % 10) + '0';
        temp /= 10;
    }
    i += digits;

    // Add decimal point
    buffer[i++] = '.';

    // Convert fractional part
    for (j = 0; j < precision; j++) {
        frac_part *= 10.0f;
        digit = (int)(frac_part + (j == precision - 1 ? 0.5f : 0.0f));  // Round last digit
        buffer[i++] = digit + '0';
        frac_part -= digit;
    }

    // Null-terminate the string
    buffer[i] = '\0';
}

float To_Degrees(float angle){
    int deg = (int)(angle) / 100;

    float min = angle - deg * 100.0f;

    return (deg + (min / 60.0f));
}

float GPS_CalculateDistance(const GPS_Data* point1, const DESTINATION* point2) {
    char buffer[32];  // Sufficient size for float conversion
    float lat1, lon1, lat2, lon2;
    float latDiff, lonDiff;
    float s1, s2, c1, c2;
    float a, c;

    UART0_SendChar('(');
    UART0_SendString(point1->latitude);
    UART0_SendChar(',');
    UART0_SendString(point1->longitude);
    UART0_SendChar(')');
    UART0_SendChar('\n');

    // Convert GPS strings to decimal degrees
    lat1 = To_Degrees(stringToFloatManual(point1->latitude));
    if (point1->latitude_dir == 'S') lat1 = -lat1;

    lon1 = To_Degrees(stringToFloatManual(point1->longitude));
    if (point1->longitude_dir == 'W') lon1 = -lon1;

    lat2 = To_Degrees(point2->latitude);
    if (point2->latitude_dir == 'S') lat2 = -lat2;

    lon2 = To_Degrees(point2->longitude);
    if (point2->longitude_dir == 'W') lon2 = -lon2;
    
    // UART0_SendChar('(');
    // float_to_string(lat1, buffer, 5);
    // UART0_SendString(buffer);
    // UART0_SendChar(',');
    // float_to_string(lon1, buffer, 5);
    // UART0_SendString(buffer);
    // UART0_SendChar(')');
    // UART0_SendChar('\n');

    // Convert degrees to radians
    lat1 = To_Radians(lat1);
    lon1 = To_Radians(lon1);
    lat2 = To_Radians(lat2);
    lon2 = To_Radians(lon2);

    // Haversine formula
    latDiff = lat2 - lat1;
    lonDiff = lon2 - lon1;

    s1 = sinf(latDiff / 2.0f);
    s2 = sinf(lonDiff / 2.0f);
    c1 = cosf(lat1);
    c2 = cosf(lat2);

    a = s1 * s1 + c1 * c2 * s2 * s2;

    // Clamp 'a' to [0, 1] to avoid sqrt of negative number
    if (a > 1.0f) a = 1.0f;
    if (a < 0.0f) a = 0.0f;

    c = 2.0f * atan2f(sqrtf(a), sqrtf(1.0f - a));

    // Debug output
    // UART0_SendString("c: ");
    // float_to_string(c, buffer, 5);
    // UART0_SendString(buffer);
    // UART0_SendString("\n");

    return EARTH_RADIUS * c;  // EARTH_RADIUS should be in km or meters as needed
}

static void readField(U_CHAR *buffer) {
    U_CHAR received_char;
    U_CHAR i = 0;

    while (i < max_buffer_size - 1) {
        received_char = UART0_ReadChar();
        // UART0_SendChar(received_char);

        if (received_char == ',' ) { break;}
        buffer[i++] = received_char;
    }

    buffer[i] = '\0';  // null-terminate
}

void GPS_READ(GPS_Data *data){

    U_CHAR received_char;
    U_CHAR match_index = 0;
    U_CHAR field = 0;

    // Step 1: Wait for "$GPRMC"
    while (1) {
        received_char = UART0_ReadChar();
        // LCD_Clear();

        if (received_char == LOG_NAME[match_index]) {
            match_index++;

            if (match_index == LOG_NAME_LEN)
                {
                // UART0_SendChar(received_char);
                break; }                         // Found "$GPRMC"         
        } 
        else {
            // match_index = (received_char == LOG_NAME[0]) ? 1 : 0;
            match_index = 0;
        }

        // UART0_SendChar(received_char);
        // LCD_VoidWriteData(received_char);
    }

    // get rid of field 1 ','
    received_char=UART0_ReadChar();
    // UART0_SendChar(received_char);

    // Step 2: Skip one field (UTC time)
    readField(data->buffer);                        // field 1 (UTC)

    
    // Step 3: Parse desired fields
    readField(data->buffer);                        // field 2: status
    data->status = data->buffer[0];
    if (data->status == 'V') {
        // Invalid data, exit function or handle it
        return;
    }

    readField(data->buffer);                        // field 3: latitude
    strcpy(data->latitude, data->buffer);


    readField(data->buffer);                        // field 4: N/S
    data->latitude_dir = data->buffer[0];
    // data->latitude = (data->latitude_dir == 'S') ? -data->latitude : data->latitude;


    readField(data->buffer);                        // field 5: longitude
    strcpy(data->longitude, data->buffer);


    readField(data->buffer);                        // field 6: E/W
    data->longitude_dir = data->buffer[0];
    // data->longitude = (data->longitude_dir == 'W') ? -data->longitude : data->longitude;


    readField(data->buffer);                        // field 7: speed in knots
    strcpy(data->speed, data->buffer);
    
}
