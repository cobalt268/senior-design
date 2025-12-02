#include "../hal/distance_sensor_hal.h"

/// @brief configures distance sensors and relevant pins, boots sensors
/// @param
void setup_distance(void)
{
    setup_dist_sensor();
}

/// @brief
/// @param
/// @return right sensor measurement in mm
uint16_t rightDistance(void)
{
    refresh();
    return getRight();
}

/// @brief
/// @param
/// @return left sensor measurement in mm
uint16_t leftDistance(void)
{
    refresh();
    return getLeft();
}

/// @brief
/// @param
/// @return forward sensor measurement in mm
uint16_t forwardDistance(void)
{
    refresh();
    return getForward();
}