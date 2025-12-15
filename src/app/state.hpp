#pragma once
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

namespace state {

    void init();

    //Target Temperature 
    void setTargetTemperature(float temp);
    float getTargetTemperature();

    //Current Temperature (Sensor)
    void setCurrentTemperature(float temp);
    float getCurrentTemperature();

}