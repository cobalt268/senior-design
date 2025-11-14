#include <Arduino.h>
#include "Adafruit_VL53L0X.h"

#define SENSOR_FORWARD 6
#define SENSOR_LEFT 4
#define SENSOR_RIGHT 7

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  pinMode(SENSOR_FORWARD, OUTPUT);
  pinMode(SENSOR_LEFT, OUTPUT);
  pinMode(SENSOR_RIGHT, OUTPUT);

  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }

}

void loop() {
  uint16_t right_dist = 0;
  uint16_t left_dist = 0;
  uint16_t forward_dist = 0;

  //get right dist:
  digitalWrite(SENSOR_FORWARD, LOW);
  digitalWrite(SENSOR_LEFT, LOW);
  digitalWrite(SENSOR_RIGHT, HIGH);

  lox.begin();
  lox.startRangeContinuous();

  delay(50);

  if (lox.isRangeComplete()) {
    right_dist = lox.readRange();
  }

  //get left dist:
  digitalWrite(SENSOR_FORWARD, LOW);
  digitalWrite(SENSOR_LEFT, HIGH);
  digitalWrite(SENSOR_RIGHT, LOW);

  lox.begin();
  lox.startRangeContinuous();

  delay(50);

  if (lox.isRangeComplete()) {
    left_dist = lox.readRange();
  }

  //get forward dist:
  digitalWrite(SENSOR_FORWARD, HIGH);
  digitalWrite(SENSOR_LEFT, LOW);
  digitalWrite(SENSOR_RIGHT, LOW);

  lox.begin();
  lox.startRangeContinuous();

  delay(50);

  if (lox.isRangeComplete()) {
    forward_dist = lox.readRange();
  }

  //clear previous output
  Serial.write(27);
  Serial.print("[2J");
  Serial.write(27);
  Serial.print("[H");

  Serial.printf("Distance (mm):\n\rRIGHT:\t\t%d\n\rFORWARD:\t%d\n\rLEFT:\t\t%d",right_dist,forward_dist,left_dist);
  //delay(200);
}