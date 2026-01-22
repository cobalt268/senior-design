#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

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

#endif