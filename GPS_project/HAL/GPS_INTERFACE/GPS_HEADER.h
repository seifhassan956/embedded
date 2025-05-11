#ifndef GPS_Interface_H
#define GPS_Interface_H

typedef unsigned char U_CHAR;

#define LOG_NAME "$GPRMC"
#define LOG_NAME_LEN 6
#define max_buffer_size 20

#define EARTH_RADIUS 6371000.0f
#define M_PI 3.14159265358979323846

#define To_Radians(angle) ((angle) * M_PI / 180)

typedef struct {
    U_CHAR status;                       // 'A' or 'V'
    U_CHAR latitude[20];                    // Store latitude as a string (e.g., "5109.0262308")
    U_CHAR latitude_dir;                  // 'N'/'S'
	
    U_CHAR longitude[20];                 // Store longitude as a string (e.g., "11401.8407342")
    U_CHAR longitude_dir;                 // 'E'/'W'
    U_CHAR speed[10];                     // Store speed as a string (e.g., "0.004")
    U_CHAR buffer[max_buffer_size];       // Buffer for other data
} GPS_Data;

typedef struct {
    float latitude;                  // Store latitude as a string (e.g., "5109.0262308")
    U_CHAR latitude_dir;                  // 'N'/'S'
    float longitude;                 // Store longitude as a string (e.g., "11401.8407342")
    U_CHAR longitude_dir;                 // 'E'/'W'
    U_CHAR name[max_buffer_size];       // Buffer for other data
} DESTINATION;


float To_Degrees(float angle);
float stringToFloatManual(const char* str);
float GPS_CalculateDistance(const GPS_Data* point1, const DESTINATION* point2);
// float GPS_CalculateDistance(float lat1 , float lon1 , char lat_dir1 , char lon_dir1 , float lat2 , float lon2 , char lat_dir2 , char lon_dir2); void readField(U_CHAR *buffer);
void GPS_READ(GPS_Data *data);
void float_to_string(float number, char* buffer, int precision);

#endif
