#include <Arduino.h>
#include "motor.h"
#include "../hal/motor_hal.h"
#include "../hal/encoder_hal.h"

#define LEFT_RIGHT_RATIO 1

/// @brief configures motor pwm and encoders
/// @param
void setup_motor(void)
{
    setup_motor_hal();
    encoder_setup_hal();
};

/// @brief sets right motor to go forward at set duty cycle
/// @param
void right_set_forward(float duty)
{
    right_motor_forward_hal(duty);
};

/// @brief sets left motor to go forward at set duty cycle
/// @param
void left_set_forward(float duty)
{
    left_motor_forward_hal(duty * LEFT_RIGHT_RATIO);
};

/// @brief sets right motor to go backward at set duty cycle
/// @param
void right_set_backward(float duty)
{
    right_motor_backward_hal(duty);
};
/// @brief sets left motor to go backward at set duty cycle
/// @param
void left_set_backward(float duty)
{
    left_motor_backward_hal(duty);
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

void proceed_forward(uint16_t mm)
{
    // briefly high initial torque
    left_set_forward(100.0);
    right_set_forward(100.0);
    vTaskDelay(20 / portTICK_PERIOD_MS);

    // running speed
    left_set_forward(20.0);
    right_set_forward(20.0);

    vTaskDelay(mm * 4.5 / portTICK_PERIOD_MS);  //TODO REPLACE THIS WITH SOME KINDA ENCODER SENSY THING

    left_stop();
    right_stop();
}