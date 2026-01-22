#include <Arduino.h>
#include "sys/distance.h"
#include "sys/motor.h"

void setup()
{
  Serial.begin(115200);

  setup_distance();
  setup_motor();

  vTaskDelay(1000 / portTICK_PERIOD_MS);
}

void loop()
{
  proceed_forward(200);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  rotate_right();
  vTaskDelay(500 / portTICK_PERIOD_MS);
  rotate_right();
  vTaskDelay(1000 / portTICK_PERIOD_MS);

  // // clear previous output
  // Serial.write(27);
  // Serial.print("[2J");
  // Serial.write(27);
  // Serial.print("[H");

  // uint16_t right_dist = rightDistance();
  // uint16_t left_dist = leftDistance();
  // uint16_t forward_dist = forwardDistance();

  // uint32_t right_encoder_counts = get_right_encoder_count();
  // uint32_t left_encoder_counts = get_left_encoder_count();

  // Serial.printf("Distance (mm):\n\rRIGHT:\t\t%d\n\rFORWARD:\t%d\n\rLEFT:\t\t%d\n\r-------------------------------------------------------\n\rENCODER DATA (counts):\n\rRIGHT:\t\t%d\n\rLEFT:\t\t%d\n\r", right_dist, forward_dist, left_dist, right_encoder_counts, left_encoder_counts);
  // vTaskDelay(50 / portTICK_PERIOD_MS);
}