#include <Arduino.h>
#include "pins.hpp"
#include "hal_rotary.hpp"
#include "app/state.hpp"


static bool lastSigAState = false;

void hal::rotatory::init() {

    pinMode(pins::sigA_PIN, INPUT_PULLUP);
    pinMode(pins::sigB_PIN, INPUT_PULLUP);

    lastSigAState = digitalRead(pins::sigA_PIN);

}

void hal::rotatory::readPosition(){
    bool currentSigA = digitalRead(pins::sigA_PIN);
    
    // check rising edge 

    if (!lastSigAState && currentSigA){

        long currentPos = 0;
        
        //check direction
        if(digitalRead(pins::sigB_PIN)){
            currentPos ++;
            Serial.print("Leitura feita, posicao ++");
        } else {
            currentPos --;            
            Serial.print("Leitura feita, posicao --");
        }
        state::setTargetTemperature(state::getTargetTemperature() + currentPos);
    }

    lastSigAState = currentSigA;

}
