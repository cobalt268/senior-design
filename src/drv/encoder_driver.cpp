#include "encoder_driver.h"
#include <Arduino.h>

volatile static int32_t er_count = 0;
volatile static int32_t el_count = 0;

static uint8_t er1_pin, er2_pin, el1_pin, el2_pin;

static void er1_int_handler(void)
{
    // Channel A edge: inverted motor mount — if A != B, forward; else reverse
    if (digitalRead(er1_pin) != digitalRead(er2_pin))
        er_count++;
    else
        er_count--;
};

static void er2_int_handler(void)
{
    // Channel B edge: inverted motor mount — if A == B, forward; else reverse
    if (digitalRead(er1_pin) == digitalRead(er2_pin))
        er_count++;
    else
        er_count--;
};

static void el1_int_handler(void)
{
    if (digitalRead(el1_pin) == digitalRead(el2_pin))
        el_count++;
    else
        el_count--;
};

static void el2_int_handler(void)
{
    if (digitalRead(el1_pin) != digitalRead(el2_pin))
        el_count++;
    else
        el_count--;
};

/// @brief
/// @param er1 encoder right channel A input pin
/// @param er2 encoder right channel B input pin
/// @param el1 encoder left channel A input pin
/// @param el2 encoder left channel B input pin
void encoder_setup_drv(uint8_t er1, uint8_t er2, uint8_t el1, uint8_t el2)
{
    er1_pin = er1;
    er2_pin = er2;
    el1_pin = el1;
    el2_pin = el2;

    pinMode(er1, INPUT);
    pinMode(er2, INPUT);
    pinMode(el1, INPUT);
    pinMode(el2, INPUT);

    attachInterrupt(digitalPinToInterrupt(er1), er1_int_handler, CHANGE);
    attachInterrupt(digitalPinToInterrupt(er2), er2_int_handler, CHANGE);
    attachInterrupt(digitalPinToInterrupt(el1), el1_int_handler, CHANGE);
    attachInterrupt(digitalPinToInterrupt(el2), el2_int_handler, CHANGE);
};

/// @brief
/// @param
/// @return
int32_t counts_left(void)
{
    return el_count;
}

/// @brief
/// @param
/// @return
int32_t counts_right(void)
{
    return er_count;
}
