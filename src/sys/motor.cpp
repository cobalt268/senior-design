#include <Arduino.h>
#include "motor.h"
#include "../hal/motor_hal.h"
#include "../hal/encoder_hal.h"

#define LEFT_RIGHT_RATIO 1 // todo fix this
#define COUNTS_PER_MM 5    // todo fix this

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
    vTaskDelay(5 / portTICK_PERIOD_MS);

    // running speed
    left_set_forward(20.0);
    right_set_forward(20.0);

    uint8_t start_count = get_right_encoder_count();
    while ((get_right_encoder_count() - start_count) < mm * COUNTS_PER_MM)
        ;

    left_stop();
    right_stop();
}