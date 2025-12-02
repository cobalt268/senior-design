#include <stdint.h>

typedef struct distances
{
    uint16_t right;
    uint16_t left;
    uint16_t forward;
} distances_t;

void setupVL53LOX(void);

void getMeasurements(distances_t *);