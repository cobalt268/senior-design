#include "distance.h"
#include "../drv/ir_driver.h"
#include <math.h>

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
    uint16_t millis = pow(volt/10417.0478,(1.0/-0.809747));
    return millis;
}

/// @brief
/// @param
/// @return left sensor measurement in mm
uint16_t leftDistance(void)
{
    uint16_t volt = left_voltage();
    uint16_t millis = pow(volt/12670.0822,(1.0/-0.80072));
    return millis;
}

/// @brief
/// @param
/// @return (right ) forward sensor measurement in mm
uint16_t forwardDistance(void)
{
    uint16_t volt = front_right_voltage();
    uint16_t millis = pow(volt/427574.3144,(1.0/-1.16168));
    return millis;
}

// left forward sensor distance in mm
uint16_t forwardLeftDistance(void)
{
    uint16_t volt = front_left_voltage();
    uint16_t millis = pow(volt/427574.3144,(1.0/-1.16168));
    return millis;
}
