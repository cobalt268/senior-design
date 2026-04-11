#ifndef DISTANCE_H
#define DISTANCE_H

#include <stdint.h>

#define LED_RIGHT 16
#define LED_FORWARD_RIGHT 17
#define LED_FORWARD_LEFT 3
#define LED_LEFT 9

#define SENSOR_FORWARD_RIGHT 6
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

#endif
