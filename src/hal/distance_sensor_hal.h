#include <stdint.h>

#define SENSOR_FORWARD 6
#define SENSOR_LEFT 4
#define SENSOR_RIGHT 7

void setup_dist_sensor(void);

void refresh(void);

uint16_t getLeft(void);

uint16_t getRight(void);

uint16_t getForward(void);