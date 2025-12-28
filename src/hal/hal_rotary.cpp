#include <Arduino.h>
#include "drivers/RotaryEncoder.hpp"
#include "pins.hpp"


static constexpr int sigA = 0;
static constexpr int sigB = 0;
static constexpr int position = 0;
static constexpr bool lastSigaState = false;
static constexpr bool currentSigaState = false;


void RotaryEncoder::setup(uint8_t siga, uint8_t sigb) {

    this->siga = siga;
    this->sigb = sigb;
    
    this->position         = 0;
    this->lastSigaState    = false;
    this->currentSigaState = false;

    pinMode(this->siga, INPUT);
    pinMode(this->sigb, INPUT);

}

void hal::rotatory::init(uint8_t siga, uint8_t sigb) {

    pinMode(pins::PELTIER_PIN, OUTPUT);
    pinMode(pins::sigA_PIN, INPUT);
    pinMode(pins::sigB_PIN, INPUT);

}

int RotaryEncoder::getPosition() {
    return this->position;
}

void RotaryEncoder::read() {
    
    this->currentSigaState = digitalRead(this->siga);

    // check rising edge 
    if (!this->lastSigaState && this->currentSigaState) {
        // check direction
        if (digitalRead(this->sigb)) {
            this->position ++;
        } else {
            this->position --;
        }
    }

    this->lastSigaState = this->currentSigaState;

}