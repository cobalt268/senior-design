#include "../hal/distance_sensor_hal.h"

/// @brief
/// @param
void setup_distance(void)
{
    setup_dist_sensor();
}

/// @brief
/// @param
void distance_refresh(void)
{
    refresh();
}

/// @brief
/// @param
/// @return
uint16_t rightDistance(void)
{
    return getRight();
}

/// @brief
/// @param
/// @return
uint16_t leftDistance(void)
{
    return getLeft();
}

/// @brief
/// @param
/// @return
uint16_t forwardDistance(void)
{
    return getForward();
}