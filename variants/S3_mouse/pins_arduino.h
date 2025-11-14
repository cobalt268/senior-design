#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>
/* definitions for mouse practice board */
#define EESD_S3

// User LED
static const uint8_t LED_BUILTIN = 42;
#define BUILTIN_LED LED_BUILTIN // backward compatibility
#define LED_BUILTIN LED_BUILTIN // allow testing #ifdef LED_BUILTIN

/* TX and RX not connected */
// static const uint8_t TX = 43;
// static const uint8_t RX = 44;

/* Switch 41. Note internal port pullup must be used.*/
static const uint8_t SW41 = 41;
static const uint8_t Boot_Pin = 0;

/* I2C OLED, sensors*/
static const uint8_t SDA = 40;
static const uint8_t SCL = 39;

/* motor - hbridge connections */

static const uint8_t PWM_1L = 48;
static const uint8_t PWM_2L = 45;
static const uint8_t PWM_1R = 21;
static const uint8_t PWM_2R = 47;

/* encoder inputs */

static const uint8_t ENC_1L = 13;
static const uint8_t ENC_2L = 14;
static const uint8_t ENC_1R = 11;
static const uint8_t ENC_2R = 12;

// left analog sensor
static const uint8_t L_X_ON = 10;
static const uint8_t L_AN_IN = 4;
// front left analog sensor
static const uint8_t FL_X_ON = 9;
static const uint8_t FL_AN_IN = 5;
// front right analog sensor
static const uint8_t FR_X_ON = 17;
static const uint8_t FR_AN_IN = 6;
// right analog sensor
static const uint8_t R_X_ON = 16;
static const uint8_t R_AN_IN = 7;

/* TOF Sensors */
/* board solder jumpers connect to analog sensors
* To use TOF sensors pins below, jumpers must be changed
* by cutting the jumper on the analog side and bridging
* it on the TOF side
*/
static const uint8_t L_INT = 10;
static const uint8_t L_SHT = 4;

static const uint8_t FL_INT = 9;
static const uint8_t FL_SHT = 5;

static const uint8_t FR_INT = 17;
static const uint8_t FR_SHT = 6;

static const uint8_t R_INT = 16;
static const uint8_t R_SHT = 7;

static const uint8_t SCK = -1;
static const uint8_t MISO = -1;
static const uint8_t MOSI = -1;
static const uint8_t SS = -1;

#endif /* Pins_Arduino_h */
