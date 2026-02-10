#include "distance.h"
#include "../drv/vl53l0x.h"

static distances_t distances;

/// @brief configures distance sensors and relevant pins, boots sensors
/// @param
void setup_distance(void)
{
    setupVL53LOX(SENSOR_FORWARD, SENSOR_LEFT, SENSOR_RIGHT, SENSOR_FORWARD_LEFT);
}

/// @brief
/// @param
/// @return right sensor measurement in mm
uint16_t rightDistance(void)
{
    return distances.right;
}

/// @brief
/// @param
/// @return left sensor measurement in mm
uint16_t leftDistance(void)
{
    return distances.left;
}

/// @brief
/// @param
/// @return forward sensor measurement in mm
uint16_t forwardDistance(void)
{
    return distances.forward;
}

void distance_refresh(void){
    getMeasurements(&distances);
}

uint16_t forwardLeftDistance(void){
    return distances.forward_left;
}