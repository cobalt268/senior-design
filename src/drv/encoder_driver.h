#ifndef ENCODER_DRIVER_H
#define ENCODER_DRIVER_H

#include <stdint.h>

void encoder_setup_drv(uint8_t er1, uint8_t er2, uint8_t el1, uint8_t el2);

uint32_t counts_left(void);
uint32_t counts_right(void);

#endif