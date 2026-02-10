#include "distance_sensor_hal.h"
#include "../drv/vl53l0x.h"

static distances_t distances;

/// @brief 
/// @param  
void setup_dist_sensor(void)
{
    setupVL53LOX(SENSOR_FORWARD, SENSOR_LEFT, SENSOR_RIGHT, SENSOR_FORWARD_LEFT);
}

/// @brief 
/// @deprecated remove once interrupt-based polling is completed
/// @param  
void refresh(void)
{
    getMeasurements(&distances);
}

/// @brief 
/// @param  
/// @return 
uint16_t getLeft(void)
{
    return distances.left;
}

/// @brief 
/// @param  
/// @return 
uint16_t getRight(void)
{
    return distances.right;
}

/// @brief 
/// @param  
/// @return 
uint16_t getForward(void)
{
    return distances.forward;
}

uint16_t getForwardLeft(void){
    return distances.forward_left;
}