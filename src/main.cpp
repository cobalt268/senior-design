#include <Arduino.h>
#include "Adafruit_VL53L0X.h"

#define SENSOR_FORWARD 6
#define SENSOR_LEFT 4
#define SENSOR_RIGHT 7

Adafruit_VL53L0X lox_forward = Adafruit_VL53L0X();
Adafruit_VL53L0X lox_left = Adafruit_VL53L0X();
Adafruit_VL53L0X lox_right = Adafruit_VL53L0X();

#define FORWARD_I2C 0x30
#define LEFT_I2C 0x31
#define RIGHT_I2C 0x32

void setup() {
  pinMode(SENSOR_FORWARD, OUTPUT);
  pinMode(SENSOR_LEFT, OUTPUT);
  pinMode(SENSOR_RIGHT, OUTPUT);

  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }

   // all reset
  digitalWrite(SENSOR_FORWARD, LOW);    
  digitalWrite(SENSOR_LEFT, LOW);
  digitalWrite(SENSOR_RIGHT, LOW);
  delay(10);
  // all unreset
  digitalWrite(SENSOR_FORWARD, HIGH);    
  digitalWrite(SENSOR_LEFT, HIGH);
  digitalWrite(SENSOR_RIGHT, HIGH);
  delay(10);

  // activating forward, resetting all else
  digitalWrite(SENSOR_FORWARD, HIGH);    
  digitalWrite(SENSOR_LEFT, LOW);
  digitalWrite(SENSOR_RIGHT, LOW);

  // initing forward
  if(!lox_forward.begin(FORWARD_I2C)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while(1);
  }
  delay(10);

  // activating right
  digitalWrite(SENSOR_RIGHT, HIGH);
  delay(10);

  //initing right
  if(!lox_right.begin(RIGHT_I2C)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while(1);
  }

  // activating left
  digitalWrite(SENSOR_LEFT, HIGH);
  delay(10);

  //initing left
  if(!lox_left.begin(LEFT_I2C)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while(1);
  }

  lox_forward.startRangeContinuous();
  lox_left.startRangeContinuous();
  lox_right.startRangeContinuous();

  delay(100);

}

void loop() {
  uint16_t right_dist = 0;
  uint16_t left_dist = 0;
  uint16_t forward_dist = 0;

  //get distances
  if (lox_left.isRangeComplete()) {
    left_dist = lox_left.readRange();
  }
  if (lox_right.isRangeComplete()) {
    right_dist = lox_right.readRange();
  }
  if (lox_forward.isRangeComplete()) {
    forward_dist = lox_forward.readRange();
  }

  //clear previous output
  Serial.write(27);
  Serial.print("[2J");
  Serial.write(27);
  Serial.print("[H");

  Serial.printf("Distance (mm):\n\rRIGHT:\t\t%d\n\rFORWARD:\t%d\n\rLEFT:\t\t%d",right_dist,forward_dist,left_dist);
  delay(50);
}