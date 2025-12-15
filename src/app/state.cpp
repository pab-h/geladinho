#include <Arduino.h>
#include "state.hpp"

namespace state {

    //Variáveis privadas - valor inicial padrão
    static float _targetTemperature = 10.0f;
    static float _currentTemperature = 25.0f; 

    static SemaphoreHandle_t _stateMutex = nullptr;

    void init() {
        _stateMutex = xSemaphoreCreateMutex();

        if (_stateMutex == NULL) {
            Serial.println("[CRITICAL] (state.cpp) Falha ao criar Mutex! em memória RAM (Heap exausted).");
        }
    }


    //Setters e Getters

    void setTargetTemperature(float temp) {

        if (xSemaphoreTake(_stateMutex, portMAX_DELAY) == pdTRUE) {
            _targetTemperature = temp;
            
            xSemaphoreGive(_stateMutex);
        }
    }

    float getTargetTemperature() {
        float val = 0.0f;
        if (xSemaphoreTake(_stateMutex, portMAX_DELAY) == pdTRUE) {
            val = _targetTemperature;
            xSemaphoreGive(_stateMutex);
        }
        return val;
    }

    void setCurrentTemperature(float temp) {
        if (xSemaphoreTake(_stateMutex, portMAX_DELAY) == pdTRUE) {
            _currentTemperature = temp;
            xSemaphoreGive(_stateMutex);
        }
    }

    float getCurrentTemperature() {
        float val = 0.0f;
        if (xSemaphoreTake(_stateMutex, portMAX_DELAY) == pdTRUE) {
            val = _currentTemperature;
            xSemaphoreGive(_stateMutex);
        }
        return val;
    }
}