#include <Arduino.h>
#include "motor.h"
#include "../drv/motor_driver.h"
#include "../drv/encoder_driver.h"
#include "distance.h"

// how many encoder counts the right motor logs while traveling 1 millimeter
#define RIGHT_COUNTS_PER_MM 39.3f
// how many motor counts per 90 degree turn
#define COUNTS_PER_90 2700

#define RUNNING_SPEED 45.0
#define STARTING_SPEED 100.0
#define TURNING_SPEED 40.0

#define AVERSION_DISTANCE 35   // side wall distance in mm that triggers a micro-correction
#define AVERSION_TURN_DEG 3    // degrees to pivot away from a side wall
#define AVERSION_MIN_MM   40   // minimum travel before aversion is allowed to trigger

float motor_ratio = 1.00;

// pivot left by AVERSION_TURN_DEG degrees then resume — called when too close to right wall
static void avert_from_right(void)
{
    int32_t target = (int32_t)((AVERSION_TURN_DEG / 90.0f) * (COUNTS_PER_90 / 2));
    int32_t start_count = get_right_encoder_count();
    right_set_forward(TURNING_SPEED);
    left_set_backward(TURNING_SPEED);
    while ((get_right_encoder_count() - start_count) < target)
        vTaskDelay(1 / portTICK_PERIOD_MS);
    right_set_forward(RUNNING_SPEED);
    left_set_forward(RUNNING_SPEED);
}

// pivot right by AVERSION_TURN_DEG degrees then resume — called when too close to left wall
static void avert_from_left(void)
{
    int32_t target = (int32_t)((AVERSION_TURN_DEG / 90.0f) * (COUNTS_PER_90 / 2));
    int32_t start_count = get_left_encoder_count();
    left_set_forward(TURNING_SPEED);
    right_set_backward(TURNING_SPEED);
    while ((get_left_encoder_count() - start_count) < target)
        vTaskDelay(1 / portTICK_PERIOD_MS);
    right_set_forward(RUNNING_SPEED);
    left_set_forward(RUNNING_SPEED);
}

/// @brief configures motor pwm and encoders
/// @param
void setup_motor(void)
{
    motor_setup(PWM_R_1, PWM_R_2, PWM_L_1, PWM_L_2);
    encoder_setup_drv(ENCODER_R_1, ENCODER_R_2, ENCODER_L_1, ENCODER_L_2);
};

/// @brief sets right motor to go forward at set duty cycle
/// @param
void right_set_forward(float duty)
{
    right_motor_forward(duty);

};

/// @brief sets left motor to go forward at set duty cycle
/// @param
void left_set_forward(float duty)
{
    left_motor_reverse(duty);

};

/// @brief sets right motor to go backward at set duty cycle
/// @param
void right_set_backward(float duty)
{
    right_motor_reverse(duty);

};
/// @brief sets left motor to go backward at set duty cycle
/// @param
void left_set_backward(float duty)
{
    left_motor_forward(duty);

};

/// @brief stops right motor movement
/// @param
void right_stop(void)
{
    right_motor_stop();
};

/// @brief stops right motor movement
/// @param
void left_stop(void)
{
    left_motor_stop();
};

/// @brief
/// @param
/// @return encoder count for left motor
int32_t get_left_encoder_count(void)
{
    return -counts_left();
}

/// @brief
/// @param
/// @return encoder count for right motor
int32_t get_right_encoder_count(void)
{
    return -counts_right();
}

/// @brief
/// @param mm distance to proceed forward in millimeters
void proceed_forward(uint16_t mm)
{
    // reset drift correction for each new move
    motor_ratio = 1.0f;

    // capture start position before any movement
    int32_t start_count = get_right_encoder_count();
    int32_t last_count_right = start_count;
    int32_t last_count_left = get_left_encoder_count();

    // briefly high initial torque
    left_set_forward(STARTING_SPEED);
    right_set_forward(STARTING_SPEED);
    vTaskDelay(20 / portTICK_PERIOD_MS);

    // running speed
    left_set_forward(RUNNING_SPEED);
    right_set_forward(RUNNING_SPEED);

    while ((get_right_encoder_count() - start_count) < mm * RIGHT_COUNTS_PER_MM)
    {
        int32_t temp_left = get_left_encoder_count();
        int32_t temp_right = get_right_encoder_count();

        int32_t delta_right = temp_right - last_count_right;
        int32_t delta_left = temp_left - last_count_left;

        if (delta_right != 0)
        {
            float err_ratio = ((float)delta_left) / ((float)delta_right);
            motor_ratio = (motor_ratio + err_ratio) / 2.0;
            if (motor_ratio > 1.3f) motor_ratio = 1.3f;
            if (motor_ratio < 0.7f) motor_ratio = 0.7f;
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);

        bool past_threshold = (get_right_encoder_count() - start_count) > AVERSION_MIN_MM * RIGHT_COUNTS_PER_MM;
        if (past_threshold && rightDistance() < AVERSION_DISTANCE)
            avert_from_left();
        else if (past_threshold && leftDistance() < AVERSION_DISTANCE)
            avert_from_right();
        else
        {
            // apply motor_ratio to right motor to correct straight-line drift
            right_set_forward(RUNNING_SPEED * motor_ratio);
            left_set_forward(RUNNING_SPEED);
        }
        last_count_left = temp_left;
        last_count_right = temp_right;
    };

    // brake after traveling
    left_stop();
    right_stop();
}

/// @brief turn the bot 90 degrees to the right
/// @param
void rotate_right(void)
{
    // briefly high initial torque
    left_set_forward(STARTING_SPEED);
    right_set_backward(STARTING_SPEED);
    vTaskDelay(20 / portTICK_PERIOD_MS);

    // running speed
    left_set_forward(TURNING_SPEED);
    right_set_backward(TURNING_SPEED);

    // use left encoder — left motor goes forward (increments) during a right turn
    int32_t start_count = get_left_encoder_count();
    while ((get_left_encoder_count() - start_count) < COUNTS_PER_90 / 2)
        vTaskDelay(1 / portTICK_PERIOD_MS);

    // brake after traveling
    left_stop();
    right_stop();
}

/// @brief turn the bot 180 degrees (two consecutive right turns)
/// @param
void rotate_180(void)
{
    rotate_right();
    rotate_right();
}

/// @brief turn the bot 90 degrees to the left
/// @param
void rotate_left(void)
{
    // briefly high initial torque
    right_set_forward(STARTING_SPEED);
    left_set_backward(STARTING_SPEED);
    vTaskDelay(20 / portTICK_PERIOD_MS);

    // running speed
    right_set_forward(TURNING_SPEED);
    left_set_backward(TURNING_SPEED);

    // proceed until distance reached
    int32_t start_count = get_right_encoder_count();
    while ((get_right_encoder_count() - start_count) < COUNTS_PER_90 / 2)
        vTaskDelay(1 / portTICK_PERIOD_MS);

    // brake after traveling
    right_stop();
    left_stop();
}
