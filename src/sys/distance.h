#ifndef DISTANCE_H
#define DISTANCE_H

#include <stdint.h>

#define SENSOR_FORWARD 6
#define SENSOR_LEFT 4
#define SENSOR_RIGHT 7
#define SENSOR_FORWARD_LEFT 5

void setup_distance(void);
uint16_t rightDistance(void);
uint16_t leftDistance(void);
uint16_t forwardDistance(void);
uint16_t forwardLeftDistance(void);
void distance_refresh(void);

#endif