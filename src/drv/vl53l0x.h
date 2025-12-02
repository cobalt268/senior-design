#ifndef VL53LOX_H
#define VL53LOX_H

#include <stdint.h>

typedef struct distances
{
    uint16_t right;
    uint16_t left;
    uint16_t forward;
} distances_t;

void setupVL53LOX(uint8_t forward, uint8_t left, uint8_t right);

void getMeasurements(distances_t *);

#endif