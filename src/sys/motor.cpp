#include "motor.h"
#include "../hal/motor_hal.h"
#include "../hal/encoder_hal.h"

static float left_duty = 0.0;
static float right_duty = 0.0;

/// @brief configures motor pwm and encoders
/// @param
void setup_motor(void)
{
    setup_motor_hal();
    encoder_setup_hal();
};

/// @brief sets duty cycle of left motor
/// @param duty percent duty cycle as a float (0.0 < duty < 100.0)
void set_speed_left(float duty)
{
    left_duty = duty;
};

/// @brief sets duty cycle of right motor
/// @param duty percent duty cycle as a float (0.0 < duty < 100.0)
void set_speed_right(float duty)
{
    right_duty = duty;
};

/// @brief sets right motor to go forward at set duty cycle
/// @param
void right_set_forward(void)
{
    right_motor_forward_hal(right_duty);
};

/// @brief sets left motor to go forward at set duty cycle
/// @param
void left_set_forward(void)
{
    left_motor_forward_hal(left_duty);
};

/// @brief sets right motor to go backward at set duty cycle
/// @param
void right_set_backward(void)
{
    right_motor_backward_hal(right_duty);
};
/// @brief sets left motor to go backward at set duty cycle
/// @param
void left_set_backward(void)
{
    left_motor_backward_hal(left_duty);
};

/// @brief stops right motor movement
/// @param
void right_stop(void)
{
    right_motor_stop_hal();
};

/// @brief stops right motor movement
/// @param
void left_stop(void)
{
    left_motor_stop_hal();
};

/// @brief
/// @param
/// @return encoder count for left motor
uint32_t get_left_encoder_count(void)
{
    return left_encoder_counts_hal();
}

/// @brief
/// @param
/// @return encoder count for right motor
uint32_t get_right_encoder_count(void)
{
    return right_encoder_counts_hal();
}