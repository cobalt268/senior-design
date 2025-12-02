#include "motor.h"
#include "../hal/motor_hal.h"

static float left_duty;
static float right_duty;

void setup_motor(void){
    setup_motor_hal();
};

void set_speed_left(float duty){
    left_duty = duty;
};
void set_speed_right(float duty){
    right_duty = duty;
};

void right_set_forward(void){
    right_motor_forward_hal(right_duty);
};
void left_set_forward(void){
    left_motor_forward_hal(left_duty);
};

void right_set_backward(void){
    right_motor_backward_hal(right_duty);
};
void left_set_backward(void){
    left_motor_backward_hal(left_duty);
};

void right_stop(void){
    right_motor_stop_hal();
};
void left_stop(void){
    left_motor_stop_hal();
};