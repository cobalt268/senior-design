#include "encoder_driver.h"
#include <Arduino.h>

volatile static uint64_t er_count = 0;
volatile static uint64_t el_count = 0;

static void er1_int_handler(void){
    er_count++;
};
static void er2_int_handler(void){
    er_count++;
};
static void el1_int_handler(void){
    el_count++;
};
static void el2_int_handler(void){
    el_count++;
};

void encoder_setup_drv(uint8_t er1, uint8_t er2, uint8_t el1, uint8_t el2){
    pinMode(er1, INPUT);
    pinMode(er2, INPUT);
    pinMode(el1, INPUT);
    pinMode(el2, INPUT);

    attachInterrupt(digitalPinToInterrupt(er1), er1_int_handler, RISING);
    attachInterrupt(digitalPinToInterrupt(er2), er2_int_handler, RISING);
    attachInterrupt(digitalPinToInterrupt(el1), el1_int_handler, RISING);
    attachInterrupt(digitalPinToInterrupt(el2), el2_int_handler, RISING);
};

uint64_t counts_left_drv(void) {
    return el_count;
}

uint64_t counts_right_drv(void){
    return er_count;
}