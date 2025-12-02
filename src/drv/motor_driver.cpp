#include "motor_driver.h"
#include <Arduino.h>
#include "driver/mcpwm.h"

/// @brief 
/// @param r1 
/// @param r2 
/// @param l1 
/// @param l2 
void motor_setup(uint8_t r1, uint8_t r2, uint8_t l1, uint8_t l2){
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, r1);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, r2);
    mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM1A, l1);
    mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM1B, l2);

    mcpwm_config_t mcpwm_r_config = {
        .frequency = 1000,
        .cmpr_a = 0,
        .cmpr_b = 0,
        .duty_mode = MCPWM_DUTY_MODE_0,
        .counter_mode = MCPWM_UP_COUNTER
    };

    mcpwm_config_t mcpwm_l_config = {
        .frequency = 1000,
        .cmpr_a = 0,
        .cmpr_b = 0,
        .duty_mode = MCPWM_DUTY_MODE_0,
        .counter_mode = MCPWM_UP_COUNTER
    };

    mcpwm_init(MCPWM_UNIT_0,MCPWM_TIMER_0,&mcpwm_r_config);
    mcpwm_init(MCPWM_UNIT_1,MCPWM_TIMER_1,&mcpwm_l_config);
}

/// @brief 
/// @param duty 
void left_motor_forward(float duty){
    mcpwm_set_signal_low(MCPWM_UNIT_1,MCPWM_TIMER_1,MCPWM_OPR_B);
    mcpwm_set_duty(MCPWM_UNIT_1,MCPWM_TIMER_1,MCPWM_OPR_A, duty);
    mcpwm_set_duty_type(MCPWM_UNIT_1,MCPWM_TIMER_1, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
}

/// @brief 
/// @param duty 
void left_motor_reverse(float duty){
    mcpwm_set_signal_low(MCPWM_UNIT_1,MCPWM_TIMER_1,MCPWM_OPR_A);
    mcpwm_set_duty(MCPWM_UNIT_1,MCPWM_TIMER_1,MCPWM_OPR_B, duty);
    mcpwm_set_duty_type(MCPWM_UNIT_1,MCPWM_TIMER_1, MCPWM_OPR_B, MCPWM_DUTY_MODE_0);
}

/// @brief 
/// @param  
void left_motor_stop(void){
    mcpwm_set_signal_low(MCPWM_UNIT_1,MCPWM_TIMER_1,MCPWM_OPR_A);
    mcpwm_set_signal_low(MCPWM_UNIT_1,MCPWM_TIMER_1,MCPWM_OPR_B);
}

/// @brief 
/// @param duty 
void right_motor_forward(float duty){
    mcpwm_set_signal_low(MCPWM_UNIT_0,MCPWM_TIMER_0,MCPWM_OPR_B);
    mcpwm_set_duty(MCPWM_UNIT_0,MCPWM_TIMER_0,MCPWM_OPR_A, duty);
    mcpwm_set_duty_type(MCPWM_UNIT_0,MCPWM_TIMER_0, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
}

/// @brief 
/// @param duty 
void right_motor_reverse(float duty){
    mcpwm_set_signal_low(MCPWM_UNIT_0,MCPWM_TIMER_0,MCPWM_OPR_A);
    mcpwm_set_duty(MCPWM_UNIT_0,MCPWM_TIMER_0,MCPWM_OPR_B, duty);
    mcpwm_set_duty_type(MCPWM_UNIT_0,MCPWM_TIMER_0, MCPWM_OPR_B, MCPWM_DUTY_MODE_0);
}

/// @brief 
/// @param  
void right_motor_stop(void){
    mcpwm_set_signal_low(MCPWM_UNIT_0,MCPWM_TIMER_0,MCPWM_OPR_A);
    mcpwm_set_signal_low(MCPWM_UNIT_0,MCPWM_TIMER_0,MCPWM_OPR_B);
}