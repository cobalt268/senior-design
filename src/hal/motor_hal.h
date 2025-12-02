#define PWM_R_1 21
#define PWM_R_2 47
#define PWM_L_1 48
#define PWM_L_2 45

void setup_motor_hal(void);

void left_motor_forward_hal(float);
void left_motor_backward_hal(float);
void left_motor_stop_hal(void);

void right_motor_forward_hal(float);
void right_motor_backward_hal(float);
void right_motor_stop_hal(void);