#include "distance_sensor_hal.h"
#include "../drv/vl53l0x.h"

distances_t distances;

void setup_dist_sensor(void)
{
    setupVL53LOX();
}

void refresh(void)
{
    getMeasurements(&distances);
}

uint16_t getLeft(void)
{
    return distances.left;
}

uint16_t getRight(void)
{
    return distances.right;
}

uint16_t getForward(void)
{
    return distances.forward;
}