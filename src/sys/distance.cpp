#include "../hal/distance_sensor_hal.h"

/// @brief configures distance sensors and relevant pins, boots sensors
/// @param
void setup_distance(void)
{
    setup_dist_sensor();
}

/// @brief refreshes distance measurements. will be removed once interrupt-based sensing is implemented
/// @deprecated to be removed once interrupt-based sensing is completed
/// @param
void distance_refresh(void)
{
    refresh();
}

/// @brief
/// @param
/// @return right sensor measurement in mm
uint16_t rightDistance(void)
{
    return getRight();
}

/// @brief
/// @param
/// @return left sensor measurement in mm
uint16_t leftDistance(void)
{
    return getLeft();
}

/// @brief
/// @param
/// @return forward sensor measurement in mm
uint16_t forwardDistance(void)
{
    return getForward();
}