#include <Arduino.h>
#include "sys/distance.h"
#include "sys/motor.h"

#define GRID_SPACING 180 // distance between maze grid coordinates in millimeters

void setup()
{
  // standard arduino serial init
  Serial.begin(115200);

  // module setup methods
  setup_distance();
  setup_motor();

  // delay to allow positioning of mouse
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}

void loop()
{
  // movement debug code
  //  proceed_forward(720);
  //  vTaskDelay(3000 / portTICK_PERIOD_MS);
  //  rotate_right();
  //  vTaskDelay(200 / portTICK_PERIOD_MS);
  //  rotate_right();
  //  vTaskDelay(3000 / portTICK_PERIOD_MS);

  // this block clears previous output and resets the cursor to make the serial terminal look nice
  Serial.write(27);
  Serial.print("[2J");
  Serial.write(27);
  Serial.print("[H");

  // call distance refresh every time you want a new set of measurements from the sensors
  distance_refresh();
  // store current measurement from each sensor
  uint16_t right_dist = rightDistance();
  uint16_t left_dist = leftDistance();
  uint16_t forward_dist = forwardDistance();
  uint16_t forward_left_dist = forwardLeftDistance();

  // get current encoder counts, refreshes automatically unlike distance sensors
  uint32_t right_encoder_counts = get_right_encoder_count();
  uint32_t left_encoder_counts = get_left_encoder_count();

  // output measurements to serial
  Serial.printf("Distance (mm):\n\rRIGHT:\t\t\t%d\n\rFORWARD (right):\t%d\n\rFORWARD (left):\t\t%d\n\rLEFT:\t\t\t%d\n\r-------------------------------------------------------\n\rENCODER DATA (counts):\n\rRIGHT:\t\t%d\n\rLEFT:\t\t%d\n\r", right_dist, forward_dist, forward_left_dist, left_dist, right_encoder_counts, left_encoder_counts);
  // delay
  vTaskDelay(50 / portTICK_PERIOD_MS);
}
