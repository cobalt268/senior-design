#include "motor_hal.h"
#include "../drv/motor_driver.h"

void setup_motor_hal(void){
    motor_setup();
};

void left_motor_forward_hal(float duty){
    left_motor_forward(duty);
};
void left_motor_backward_hal(float duty){
    left_motor_reverse(duty);
};
void left_motor_stop_hal(void){
    left_motor_stop();
};

void right_motor_forward_hal(float duty){
    right_motor_forward(duty);
};
void right_motor_backward_hal(float duty){
    right_motor_reverse(duty);
};
void right_motor_stop_hal(void){
    right_motor_stop();
};