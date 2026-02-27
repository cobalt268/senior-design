#include <Arduino.h>
#include <Wire.h>
#include "sys/motor.h"
#include "sys/distance.h"

// Tune thresholds based on YOUR sensor readings
#define WALL_FRONT_THRESHOLD   80
#define WALL_SIDE_THRESHOLD    60
#define DRIVE_SEGMENT          900

// Optional: prevent repeated turn decisions due to noisy readings
#define TURN_COOLDOWN_MS       250

static inline bool wallFront()
{
  return (forwardLeftDistance() < WALL_FRONT_THRESHOLD);
}

static inline bool wallLeft()
{
  return leftDistance() < WALL_SIDE_THRESHOLD;
}

static inline bool wallRight()
{
  return rightDistance() < WALL_SIDE_THRESHOLD;
}

void setup()
{
  Serial.begin(115200);

  // I2C init (your variant may already do this, but it's fine)
  Wire.begin(40, 39);
  delay(100);

  Serial.println("Initializing sensors...");
  setup_distance();
  Serial.println("Sensors ready.");

  Serial.println("Initializing motors...");
  setup_motor();
  right_stop();
  left_stop();
  Serial.println("Motors ready.");

  Serial.println("Starting in 3 seconds...");
  delay(3000);
  Serial.println("GO!");
}

void loop()
{
  // Refresh once per loop
  distance_refresh();

  //uint16_t f  = forwardDistance();
  uint16_t fl = forwardLeftDistance();
  uint16_t l  = leftDistance();
  uint16_t r  = rightDistance();

  //Serial.printf("F:%u FL:%u L:%u R:%u | ", f, fl, l, r);

  if (wallFront())
  {
    right_stop();
    left_stop();
    delay(150);

    // Refresh again AFTER stopping for a cleaner decision
    distance_refresh();

    if (!wallRight())
    {
      Serial.println("TURN RIGHT");
      rotate_right();
    }
    else
    {
      Serial.println("TURN LEFT");
      rotate_left();
    }

    right_stop();
    left_stop();
    delay(TURN_COOLDOWN_MS);
  }
  else
  {
    Serial.println("FORWARD");
    proceed_forward(DRIVE_SEGMENT);
    right_stop();
    left_stop();
    delay(10);
  }
}