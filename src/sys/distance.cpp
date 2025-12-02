#include "../hal/distance_sensor_hal.h"

void setup_distance(void){
    setup_dist_sensor();
}

void distance_refresh(void){
    refresh();
}

uint16_t rightDistance(void){
    return getRight();
}

uint16_t leftDistance(void){
    return getLeft();
}

uint16_t forwardDistance(void){
    return getForward();
}