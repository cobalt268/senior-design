#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

void motor_setup(uint8_t r1, uint8_t r2, uint8_t l1, uint8_t l2);

void left_motor_forward(float);
void left_motor_reverse(float);
void left_motor_stop(void);

void right_motor_forward(float);
void right_motor_reverse(float);
void right_motor_stop(void);

#endif