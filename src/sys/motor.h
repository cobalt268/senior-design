#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

#define PWM_R_1 21
#define PWM_R_2 47
#define PWM_L_1 48
#define PWM_L_2 45

#define ENCODER_R_1 11
#define ENCODER_R_2 12
#define ENCODER_L_1 13
#define ENCODER_L_2 14

void setup_motor(void);

void right_set_forward(float duty);
void left_set_forward(float duty);

void right_set_backward(float duty);
void left_set_backward(float duty);

void right_stop(float duty);
void left_stop(float duty);

uint32_t get_left_encoder_count(void);
uint32_t get_right_encoder_count(void);

void proceed_forward(uint16_t mm);
void rotate_right(void);
void rotate_left(void);

void align(void);

#endif