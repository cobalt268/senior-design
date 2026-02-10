#ifndef DISTANCE_H
#define DISTANCE_H

#include <stdint.h>

void setup_distance(void);
uint16_t rightDistance(void);
uint16_t leftDistance(void);
uint16_t forwardDistance(void);
uint16_t forwardLeftDistance(void);
void distance_refresh(void);

#endif