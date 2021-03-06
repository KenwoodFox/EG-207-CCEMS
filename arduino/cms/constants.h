// Water Sensor
#define ENABLE_WATER 12
#define ANALOG_WATER 0

// LEDs
#define STATUS_LED 11
#define WARN_LED 10
#define ERROR_LED 9

// CDS 55
#define ANALOG_CDS55 1

// UV Sensor
#define ANALOG_UVSENSOR 2

// Light Sensor Servo
#define LIGHT_SENSOR_SERVO 3
#define MAX_DOOR_ANGLE 147 // Last changed dec 7
#define MIN_DOOR_ANGLE 14  // Last changed dec 8

// DHT 11
#define DATA_DHT11 6
#define DHT_TYPE DHT11

// EEPROM Defs
#define WARN_ADDR 15
#define ERROR_ADDR 20

// EEPROM coeficent values
#define COEF_PHOTO_A 25
float COEF_PHOTO_A_DEFAULT = 0.0073;
#define COEF_PHOTO_B 30
float COEF_PHOTO_B_DEFAULT = 2.0616;
#define COEF_PHOTO_C 35
float COEF_PHOTO_C_DEFAULT = 308.12;

#define BIAS_TEMP 40
float BIAS_TEMP_DEFAULT = 0.00;
#define BIAS_HUMIDITY 45
float BIAS_HUMIDITY_DEFAULT = 0.00;
