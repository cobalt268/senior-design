#include "distance.h"
#include "../drv/ir_driver.h"
#include <math.h>

//#define CALIBRATE

/// @brief configures distance sensors and relevant pins, boots sensors
/// @param
void setup_distance(void)
{
    ir_sensor_setup(LED_LEFT, SENSOR_LEFT, LED_FORWARD_LEFT, SENSOR_FORWARD_LEFT, LED_FORWARD_RIGHT, SENSOR_FORWARD_RIGHT, LED_RIGHT, SENSOR_RIGHT);
}

/// @brief
/// @param
/// @return right sensor measurement in mm
uint16_t rightDistance(void)
{
    uint16_t volt = right_voltage();
    uint16_t millis = pow(volt/8424.1306,(1.0/-0.672933));
    #ifdef CALIBRATE
    return volt;
    #else
    return millis;
    #endif
}

/// @brief
/// @param
/// @return left sensor measurement in mm
uint16_t leftDistance(void)
{
    uint16_t volt = left_voltage();
    uint16_t millis = pow(volt/6855.13386,(1.0/-0.632692));
    #ifdef CALIBRATE
    return volt;
    #else
    return millis;
    #endif
}

/// @brief
/// @param
/// @return (right ) forward sensor measurement in mm
uint16_t forwardDistance(void)
{
    uint16_t volt = front_right_voltage();
    uint16_t millis = pow(volt/427574.3144,(1.0/-1.16168));
    #ifdef CALIBRATE
    return volt;
    #else
    return millis;
    #endif
}

// left forward sensor distance in mm
uint16_t forwardLeftDistance(void)
{
    uint16_t volt = front_left_voltage();
    uint16_t millis = pow(volt/17816.3608,(1.0/-0.930119));
    #ifdef CALIBRATE
    return volt;
    #else
    return millis;
    #endif
}
