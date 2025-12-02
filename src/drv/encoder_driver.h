#ifndef ENCODER_DRIVER_H
#define ENCODER_DRIVER_H

#include <stdint.h>

void encoder_setup_drv(uint8_t er1, uint8_t er2, uint8_t el1, uint8_t el2);

uint64_t counts_left_drv(void);
uint64_t counts_right_drv(void);

#endif