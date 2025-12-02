#ifndef ENCODER_HAL_H
#define ENCODER_HAL_H

#include "../drv/encoder_driver.h"

#define ENCODER_R_1 11
#define ENCODER_R_2 12
#define ENCODER_L_1 13
#define ENCODER_L_2 14

void encoder_setup_hal(void);

uint64_t left_encoder_counts_hal(void);

uint64_t right_encoder_counts_hal(void);

#endif