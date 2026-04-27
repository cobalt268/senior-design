#include "ir_driver.h"
#include <Arduino.h>

uint8_t forward_right_led = 0, forward_left_led = 0, right_led = 0, left_led = 0;
uint8_t forward_right_photo = 0, forward_left_photo = 0, right_photo = 0, left_photo = 0;

void ir_sensor_setup(
    uint8_t init_left_led,
    uint8_t init_left_photo,
    uint8_t init_forward_left_led,
    uint8_t init_forward_left_photo,
    uint8_t init_forward_right_led,
    uint8_t init_forward_right_photo,
    uint8_t init_right_led,
    uint8_t init_right_photo)
{
    forward_left_led = init_forward_left_led;
    forward_right_led = init_forward_right_led;
    right_led = init_right_led;
    left_led = init_left_led;

    forward_right_photo = init_forward_right_photo;
    forward_left_photo = init_forward_left_photo;
    right_photo = init_right_photo;
    left_photo = init_left_photo;

    pinMode(init_left_led, OUTPUT);
    pinMode(init_forward_left_led, OUTPUT);
    pinMode(init_forward_right_led, OUTPUT);
    pinMode(init_right_led, OUTPUT);

    pinMode(init_left_photo, INPUT);
    pinMode(init_forward_left_photo, INPUT);
    pinMode(init_forward_right_photo, INPUT);
    pinMode(init_right_photo, INPUT);

    return;
}

uint16_t front_left_voltage(){
    digitalWrite(forward_left_led, HIGH);
    uint16_t voltage_value = analogRead(forward_left_photo);
    digitalWrite(forward_left_led, LOW);

    return voltage_value;
}

uint16_t front_right_voltage(){
    digitalWrite(forward_right_led, HIGH);
    uint16_t voltage_value = analogRead(forward_right_photo);
    digitalWrite(forward_right_led, LOW);

    return voltage_value;
}

uint16_t right_voltage(){
    digitalWrite(right_led, HIGH);
    uint16_t voltage_value = analogRead(right_photo);
    digitalWrite(right_led, LOW);

    return voltage_value;
}

uint16_t left_voltage(){
    digitalWrite(left_led, HIGH);
    uint16_t voltage_value = analogRead(left_photo);
    digitalWrite(left_led, LOW);

    return voltage_value;
}