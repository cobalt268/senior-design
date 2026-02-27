#include <Arduino.h>
#include "motor.h"
#include "../drv/motor_driver.h"
#include "../drv/encoder_driver.h"
#include "distance.h"


#define RIGHT_COUNTS_PER_MM 3.12
#define COUNTS_PER_90 420




#define AVERSION_FACTOR 1.1
#define AVERSION_DISTANCE 10


#define CENTER_OFFSET 5.0     // max duty adjustment for centering
#define WALL_CENTER_TARGET 48  // expected side reading when centered (mm)
#define WALL_SIDE_THRESHOLD 55  // mm — wall detected if side reading below this


#define MIN_DUTY 15.0
#define RUNNING_SPEED 22.0
#define STARTING_SPEED 60.0
#define TURNING_SPEED 26.0


static float clamp_duty(float duty)
{
   if (duty < MIN_DUTY) return MIN_DUTY;
   if (duty > 100.0) return 100.0;
   return duty;
}


float motor_ratio = 1;


void setup_motor(void)
{
   motor_setup(PWM_R_1, PWM_R_2, PWM_L_1, PWM_L_2);
   encoder_setup_drv(ENCODER_R_1, ENCODER_R_2, ENCODER_L_1, ENCODER_L_2);
}


void right_set_forward(float duty)
{
   right_motor_forward(clamp_duty(duty * motor_ratio));
}


void left_set_forward(float duty)
{
   left_motor_forward(clamp_duty(duty));
}


void right_set_backward(float duty)
{
   right_motor_reverse(clamp_duty(duty));
}


void left_set_backward(float duty)
{
   left_motor_reverse(clamp_duty(duty));
}


void right_stop(void)
{
   right_motor_stop();
}


void left_stop(void)
{
   left_motor_stop();
}


uint32_t get_left_encoder_count(void)
{
   return counts_left();
}


uint32_t get_right_encoder_count(void)
{
   return counts_right();
}


void proceed_forward(uint16_t mm)
{
   // briefly high initial torque
   const float base_left = RUNNING_SPEED;
    const float base_right = RUNNING_SPEED;

   left_set_forward(base_left);
   right_set_forward(base_right);
   vTaskDelay(20 / portTICK_PERIOD_MS);


   uint32_t last_count_right = get_right_encoder_count();
   uint32_t last_count_left = get_left_encoder_count();


   uint32_t start_count = get_right_encoder_count();
   int stop_flag = 0;
   while (((get_right_encoder_count() - start_count) < mm * RIGHT_COUNTS_PER_MM) && (stop_flag == 0))
   {
       uint32_t temp_left = get_left_encoder_count();
       uint32_t temp_right = get_right_encoder_count();


       uint32_t delta_right = temp_right - last_count_right;
       uint32_t delta_left = temp_left - last_count_left;


       vTaskDelay(10 / portTICK_PERIOD_MS);


       if (delta_right > 0) {
           float err_ratio = ((float)delta_left) / ((float)delta_right);
           motor_ratio = (motor_ratio + err_ratio) / 2.0;
       }


       distance_refresh();


       uint16_t left_dist = leftDistance();
       uint16_t right_dist = rightDistance();
       uint16_t forward_dist = forwardLeftDistance();

       float correction = 0.0;

    // (your existing centering logic here)
//if (left_dist < WALL_SIDE_THRESHOLD && right_dist < WALL_SIDE_THRESHOLD)
//{
    // Both walls visible — center at TARGET=33 on both sides
 //   float error = ((float)right_dist - (float)WALL_CENTER_TARGET)
                - ((float)left_dist  - (float)WALL_CENTER_TARGET);
    // (This simplifies to right_dist - left_dist, BUT keeping it written like this
    // makes it clear "center" is at 33/33 and helps you extend the logic.)

  //  correction = error * 0.05f;   // start smaller than 0.1
//}
//       else if (left_dist < WALL_SIDE_THRESHOLD)
    //   {
           // Only left wall — maintain distance from it
 //          float error = WALL_CENTER_TARGET - (float)left_dist;
   //        correction = error * 0.1;
 //      }
 //      else if (right_dist < WALL_SIDE_THRESHOLD)
 //      {
 //          // Only right wall — maintain distance from it
 //          float error = (float)right_dist - WALL_CENTER_TARGET;
 //          correction = error * 0.1;
 //      }
       // No walls visible — rely on encoder ratio only


       // Clamp correction
 //      if (correction > CENTER_OFFSET) correction = CENTER_OFFSET;
 //      if (correction < -CENTER_OFFSET) correction = -CENTER_OFFSET;


       // Apply: positive correction speeds up left / slows right (steer right)
   //    left_set_forward(base_left + correction);
//       right_set_forward(base_right - correction);


//       last_count_left = temp_left;
//       last_count_right = temp_right;
    
       if (forward_dist < 100){       // Stops if wall is in front.
        stop_flag = 1;
      }
  }


   left_stop();
   right_stop();
}


void rotate_right(void)
{
   left_set_forward(STARTING_SPEED);
   right_set_backward(STARTING_SPEED);
   vTaskDelay(20 / portTICK_PERIOD_MS);


   left_set_forward(TURNING_SPEED);
   right_set_backward(TURNING_SPEED);


   uint32_t start_count = get_right_encoder_count();
   while ((get_right_encoder_count() - start_count) < COUNTS_PER_90 / 2) {
       vTaskDelay(1 / portTICK_PERIOD_MS);  // yield to other tasks
   }


   left_stop();
   right_stop();
}


void rotate_left(void)
{
   right_set_forward(STARTING_SPEED);
   left_set_backward(STARTING_SPEED);
   vTaskDelay(20 / portTICK_PERIOD_MS);


   right_set_forward(TURNING_SPEED);
   left_set_backward(TURNING_SPEED);


   uint32_t start_count = get_right_encoder_count();
   while ((get_right_encoder_count() - start_count) < COUNTS_PER_90 / 2) {
       vTaskDelay(1 / portTICK_PERIOD_MS);  // yield to other tasks
   }


   right_stop();
   left_stop();
}
