#include "encoder_hal.h"

/// @brief
/// @param
void encoder_setup_hal(void)
{
    encoder_setup_drv(ENCODER_R_1, ENCODER_R_2, ENCODER_L_1, ENCODER_L_2);
}

/// @brief
/// @param
/// @return
uint32_t left_encoder_counts_hal(void)
{
    return counts_left_drv();
}

/// @brief
/// @param
/// @return
uint32_t right_encoder_counts_hal(void)
{
    return counts_right_drv();
}