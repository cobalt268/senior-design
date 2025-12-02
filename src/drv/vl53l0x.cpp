#include "vl53l0x.h"
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

void setupVL53LOX(void)
{
  pinMode(SENSOR_FORWARD, OUTPUT);
  pinMode(SENSOR_LEFT, OUTPUT);
  pinMode(SENSOR_RIGHT, OUTPUT);

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
  if (!lox_forward.begin(FORWARD_I2C))
  {
    Serial.println(F("Failed to boot first VL53L0X"));
    while (1)
      ;
  }
  delay(10);

  // activating right
  digitalWrite(SENSOR_RIGHT, HIGH);
  delay(10);

  // initing right
  if (!lox_right.begin(RIGHT_I2C))
  {
    Serial.println(F("Failed to boot second VL53L0X"));
    while (1)
      ;
  }

  // activating left
  digitalWrite(SENSOR_LEFT, HIGH);
  delay(10);

  // initing left
  if (!lox_left.begin(LEFT_I2C))
  {
    Serial.println(F("Failed to boot second VL53L0X"));
    while (1)
      ;
  }

  lox_forward.startRangeContinuous();
  lox_left.startRangeContinuous();
  lox_right.startRangeContinuous();
}

void getMeasurements(distances_t *x)
{
  // get distances
  if (lox_left.isRangeComplete())
  {
    x->left = lox_left.readRange();
  }
  if (lox_right.isRangeComplete())
  {
    x->right = lox_right.readRange();
  }
  if (lox_forward.isRangeComplete())
  {
    x->forward = lox_forward.readRange();
  }
}