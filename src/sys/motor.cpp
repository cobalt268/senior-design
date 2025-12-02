#include "motor.h"
#include "../hal/motor_hal.h"
#include "../hal/encoder_hal.h"

static float left_duty = 0.0;
static float right_duty = 0.0;

/// @brief
/// @param
void setup_motor(void)
{
    setup_motor_hal();
};

/// @brief
/// @param duty
void set_speed_left(float duty)
{
    left_duty = duty;
};

/// @brief
/// @param duty
void set_speed_right(float duty)
{
    right_duty = duty;
};

/// @brief
/// @param
void right_set_forward(void)
{
    right_motor_forward_hal(right_duty);
};

/// @brief
/// @param
void left_set_forward(void)
{
    left_motor_forward_hal(left_duty);
};

/// @brief
/// @param
void right_set_backward(void)
{
    right_motor_backward_hal(right_duty);
};
/// @brief
/// @param
void left_set_backward(void)
{
    left_motor_backward_hal(left_duty);
};

/// @brief
/// @param
void right_stop(void)
{
    right_motor_stop_hal();
};
/// @brief
/// @param
void left_stop(void)
{
    left_motor_stop_hal();
};

/// @brief
/// @param
/// @return
uint32_t get_left_encoder_count(void)
{
    return left_encoder_counts_hal();
}

/// @brief
/// @param
/// @return
uint32_t get_right_encoder_count(void)
{
    return right_encoder_counts_hal();
}