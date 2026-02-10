#ifndef VL53LOX_H
#define VL53LOX_H

#include <stdint.h>

/** @struct distances
 *  @brief struct for holding distance measurements in mm
 */
struct distances
{
    uint16_t right;
    uint16_t left;
    uint16_t forward;
    uint16_t forward_left;
};

/// @brief struct for holding distance measurements in mm
typedef struct distances distances_t;

void setupVL53LOX(uint8_t forward, uint8_t left, uint8_t right, uint8_t forward_left);

void getMeasurements(distances_t *);

#endif