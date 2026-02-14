#ifndef DISTANCE_H
#define DISTANCE_H

#include <stdint.h>

#define SENSOR_FORWARD 6
#define SENSOR_LEFT 4
#define SENSOR_RIGHT 7
#define SENSOR_FORWARD_LEFT 5

// initializes the sensors
void setup_distance(void);

// gives distance from the right sensor
uint16_t rightDistance(void);
// gives distance from the left sensor
uint16_t leftDistance(void);
// gives distance from the (right) forward sensor
uint16_t forwardDistance(void);
// gives distance from the left forward sensor
uint16_t forwardLeftDistance(void);
// refreshes all distance measurements
void distance_refresh(void);

#endif
