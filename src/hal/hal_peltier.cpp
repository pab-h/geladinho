#include "hal_peltier.hpp"
#include "pins.hpp"
#include <Arduino.h>


void hal::peltier::init() {

    pinMode(pins::PELTIER_PIN, OUTPUT);

    analogWrite(pins::PELTIER_PIN, 0);

}

void hal::peltier::setPower(uint8_t intensity){

    // For protection
    if (intensity > 100) intensity = 100;

    int pwmValue = map(intensity, 0, 100, 0, 255);

    analogWrite(pins::PELTIER_PIN, pwmValue);

}