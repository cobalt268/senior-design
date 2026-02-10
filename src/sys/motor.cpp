#include <Arduino.h>
#include "motor.h"
#include "../drv/motor_driver.h"
#include "../drv/encoder_driver.h"
#include "distance.h"

//how many encoder counts the right motor logs while traveling 1 millimeter
#define RIGHT_COUNTS_PER_MM 2.5    // todo fix this
//how many motor counts per 90 degree turn
#define COUNTS_PER_90 395

#define RUNNING_SPEED 20.0
#define STARTING_SPEED 100.0
#define TURNING_SPEED 18.0

float motor_ratio = .92;

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
    right_motor_forward(duty * motor_ratio);
};

/// @brief sets left motor to go forward at set duty cycle
/// @param
void left_set_forward(float duty)
{
    left_motor_forward(duty);
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
    left_motor_reverse(duty);
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
uint32_t get_left_encoder_count(void)
{
    return counts_left();
}

/// @brief
/// @param
/// @return encoder count for right motor
uint32_t get_right_encoder_count(void)
{
    return counts_right();
}

/// @brief 
/// @param mm distance to proceed forward in millimeters
void proceed_forward(uint16_t mm)
{
    // briefly high initial torque
    left_set_forward(STARTING_SPEED);
    right_set_forward(STARTING_SPEED);
    vTaskDelay(20 / portTICK_PERIOD_MS);

    // running speed
    left_set_forward(RUNNING_SPEED);
    right_set_forward(RUNNING_SPEED);

    uint32_t last_count_right = 0;
    uint32_t last_count_left = 0;

    //proceed until distance reached
    uint32_t start_count = get_right_encoder_count();
    while ((get_right_encoder_count() - start_count) < mm * RIGHT_COUNTS_PER_MM){
        uint32_t temp_left = get_left_encoder_count();
        uint32_t temp_right = get_right_encoder_count();

        uint32_t delta_right = temp_right-last_count_right;
        uint32_t delta_left = temp_left-last_count_left;
        float err_ratio = ((float) delta_left)/((float) delta_right);

        vTaskDelay(10/portTICK_PERIOD_MS);

        motor_ratio = (motor_ratio + err_ratio)/2.0;
        right_set_forward(RUNNING_SPEED);               //update the speed of the right motor
        last_count_left = temp_left;
        last_count_right = temp_right;
    };

    //brake after traveling
    left_stop();
    right_stop();
}

/// @brief turn the bot 90 degrees to the right
/// @param  
void rotate_right(void){
    // briefly high initial torque
    left_set_forward(STARTING_SPEED);
    right_set_backward(STARTING_SPEED);
    vTaskDelay(20 / portTICK_PERIOD_MS);

    // running speed
    left_set_forward(TURNING_SPEED);
    right_set_backward(TURNING_SPEED);

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
    right_set_forward(STARTING_SPEED);
    left_set_backward(STARTING_SPEED);
    vTaskDelay(20 / portTICK_PERIOD_MS);

    // running speed
    right_set_forward(TURNING_SPEED);
    left_set_backward(TURNING_SPEED);

    //proceed until distance reached
    uint32_t start_count = get_right_encoder_count();
    while ((get_right_encoder_count() - start_count) < COUNTS_PER_90/2)
        ;

    //brake after traveling
    right_stop();
    left_stop();
}

void align(void){

    distance_refresh();
    while (abs(forwardDistance()-forwardLeftDistance())>(1)){
    
        if (forwardDistance()-forwardLeftDistance()>0){
            right_set_forward(100.0);
            left_set_backward(100.0);
        }
        else {
            left_set_forward(100.0);
            right_set_backward(100.0);
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
        right_stop();
        left_stop();

        distance_refresh();
    };

}