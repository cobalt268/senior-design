#include <Arduino.h>
#include "sys/distance.h"
#include "sys/motor.h"

void setup()
{
  Serial.begin(115200);
  // wait until serial port opens for native USB devices
  while (!Serial)
  {
    delay(1);
  }

  setup_distance();
  setup_motor();

  delay(100);

  set_speed_right(100.0);
  set_speed_left(100.0);

  right_set_forward();
  left_set_forward();
}

void loop()
{
  distance_refresh();
  uint16_t right_dist = rightDistance();
  uint16_t left_dist = leftDistance();
  uint16_t forward_dist = forwardDistance();

  // clear previous output
  Serial.write(27);
  Serial.print("[2J");
  Serial.write(27);
  Serial.print("[H");

  Serial.printf("Distance (mm):\n\rRIGHT:\t\t%d\n\rFORWARD:\t%d\n\rLEFT:\t\t%d", right_dist, forward_dist, left_dist);
  delay(50);
}