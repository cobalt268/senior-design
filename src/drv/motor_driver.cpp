#include "motor_driver.h"
#include <Arduino.h>
#include "driver/mcpwm.h"

#define PWM_R_1 21
#define PWM_R_2 47
#define PWM_L_1 48
#define PWM_L_2 45

void motor_setup(void){
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, PWM_R_1);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, PWM_R_2);
    mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM1A, PWM_L_1);
    mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM1B, PWM_L_2);

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

void left_motor_forward(float duty){
    mcpwm_set_signal_low(MCPWM_UNIT_1,MCPWM_TIMER_1,MCPWM_OPR_B);
    mcpwm_set_duty(MCPWM_UNIT_1,MCPWM_TIMER_1,MCPWM_OPR_A, duty);
    mcpwm_set_duty_type(MCPWM_UNIT_1,MCPWM_TIMER_1, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
}
void left_motor_reverse(float duty){
    mcpwm_set_signal_low(MCPWM_UNIT_1,MCPWM_TIMER_1,MCPWM_OPR_A);
    mcpwm_set_duty(MCPWM_UNIT_1,MCPWM_TIMER_1,MCPWM_OPR_B, duty);
    mcpwm_set_duty_type(MCPWM_UNIT_1,MCPWM_TIMER_1, MCPWM_OPR_B, MCPWM_DUTY_MODE_0);
}
void left_motor_stop(void){
    mcpwm_set_signal_low(MCPWM_UNIT_1,MCPWM_TIMER_1,MCPWM_OPR_A);
    mcpwm_set_signal_low(MCPWM_UNIT_1,MCPWM_TIMER_1,MCPWM_OPR_B);
}

void right_motor_forward(float duty){
    mcpwm_set_signal_low(MCPWM_UNIT_0,MCPWM_TIMER_0,MCPWM_OPR_B);
    mcpwm_set_duty(MCPWM_UNIT_0,MCPWM_TIMER_0,MCPWM_OPR_A, duty);
    mcpwm_set_duty_type(MCPWM_UNIT_0,MCPWM_TIMER_0, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
}
void right_motor_reverse(float duty){
    mcpwm_set_signal_low(MCPWM_UNIT_0,MCPWM_TIMER_0,MCPWM_OPR_A);
    mcpwm_set_duty(MCPWM_UNIT_0,MCPWM_TIMER_0,MCPWM_OPR_B, duty);
    mcpwm_set_duty_type(MCPWM_UNIT_0,MCPWM_TIMER_0, MCPWM_OPR_B, MCPWM_DUTY_MODE_0);
}
void right_motor_stop(void){
    mcpwm_set_signal_low(MCPWM_UNIT_0,MCPWM_TIMER_0,MCPWM_OPR_A);
    mcpwm_set_signal_low(MCPWM_UNIT_0,MCPWM_TIMER_0,MCPWM_OPR_B);
}