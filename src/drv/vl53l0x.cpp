#include "vl53l0x.h"
#include <Arduino.h>
#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox_forward = Adafruit_VL53L0X();
Adafruit_VL53L0X lox_left = Adafruit_VL53L0X();
Adafruit_VL53L0X lox_right = Adafruit_VL53L0X();

#define FORWARD_I2C 0x30
#define LEFT_I2C 0x31
#define RIGHT_I2C 0x32

/// @brief configures pins and I2C interface for the ToF sensors, begins continuous ranging
/// @param forward pin number of forward sensor shutdowm
/// @param left pin number of left sensor shutdowm
/// @param right pin number of right sensor shutdowm
void setupVL53LOX(uint8_t forward, uint8_t left, uint8_t right)
{
  pinMode(forward, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);

  // all reset
  digitalWrite(forward, LOW);
  digitalWrite(left, LOW);
  digitalWrite(right, LOW);
  delay(10);
  // all unreset
  digitalWrite(forward, HIGH);
  digitalWrite(left, HIGH);
  digitalWrite(right, HIGH);
  delay(10);

  // activating forward, resetting all else
  digitalWrite(forward, HIGH);
  digitalWrite(left, LOW);
  digitalWrite(right, LOW);

  // initing forward
  if (!lox_forward.begin(FORWARD_I2C))
  {
    Serial.println(F("Failed to boot first VL53L0X"));
    while (1)
      ;
  }
  delay(10);

  // activating right
  digitalWrite(right, HIGH);
  delay(10);

  // initing right
  if (!lox_right.begin(RIGHT_I2C))
  {
    Serial.println(F("Failed to boot second VL53L0X"));
    while (1)
      ;
  }

  // activating left
  digitalWrite(left, HIGH);
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

/// @brief returns sensor measurements in a struct
/// @param x struct
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