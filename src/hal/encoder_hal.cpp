#include "encoder_hal.h"

void encoder_setup_hal(void){
    encoder_setup_drv(ENCODER_R_1,ENCODER_R_2,ENCODER_L_1,ENCODER_L_2);
}

uint64_t left_encoder_counts_hal(void){
    return counts_left_drv();
}

uint64_t right_encoder_counts_hal(void){
    return counts_right_drv();
}