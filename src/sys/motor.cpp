#include <Arduino.h>
#include "motor.h"
#include "../hal/motor_hal.h"
#include "../hal/encoder_hal.h"

//how much faster the right motor spins than the left one under "identical" duty cycle
#define LEFT_RIGHT_RATIO .9885 // todo fix this
//how many encoder counts the right motor logs while traveling 1 millimeter
#define RIGHT_COUNTS_PER_MM 5    // todo fix this
//how many motor counts per 90 degree turn
#define COUNTS_PER_90 360

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

/// @brief 
/// @param mm distance to proceed forward in millimeters
void proceed_forward(uint16_t mm)
{
    // briefly high initial torque
    left_set_forward(70.0);
    right_set_forward(70.0);
    vTaskDelay(20 / portTICK_PERIOD_MS);

    // running speed
    left_set_forward(20.0);
    right_set_forward(20.0);

    //proceed until distance reached
    uint32_t start_count = get_right_encoder_count();
    while ((get_right_encoder_count() - start_count) < mm * RIGHT_COUNTS_PER_MM)
        ;

    //brake after traveling
    left_stop();
    right_stop();
}

/// @brief turn the bot 90 degrees to the right
/// @param  
void rotate_right(void){
    // briefly high initial torque
    left_set_forward(70.0);
    right_set_backward(70.0);
    vTaskDelay(20 / portTICK_PERIOD_MS);

    // running speed
    left_set_forward(20.0);
    right_set_backward(20.0);

    //proceed until distance reached
    uint32_t start_count = get_right_encoder_count();
    while ((get_right_encoder_count() - start_count) < COUNTS_PER_90/2)
        ;

    //brake after traveling
    left_stop();
    right_stop();
}

/// @brief turn the bot 90 degrees to the left
/// @param  
void rotate_left(void){
    // briefly high initial torque
    right_set_forward(70.0);
    left_set_backward(70.0);
    vTaskDelay(20 / portTICK_PERIOD_MS);

    // running speed
    right_set_forward(20.0);
    left_set_backward(20.0);

    //proceed until distance reached
    uint32_t start_count = get_right_encoder_count();
    while ((get_right_encoder_count() - start_count) < COUNTS_PER_90/2)
        ;

    //brake after traveling
    right_stop();
    left_stop();
}