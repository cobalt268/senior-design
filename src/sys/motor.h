#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

void setup_motor(void);

void set_speed_left(float);
void set_speed_right(float);

void right_set_forward(void);
void left_set_forward(void);

void right_set_backward(void);
void left_set_backward(void);

void right_stop(void);
void left_stop(void);

uint32_t get_left_encoder_count(void);
uint32_t get_right_encoder_count(void);

#endif