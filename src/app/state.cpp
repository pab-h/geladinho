#include <Arduino.h>
#include "state.hpp"

namespace state {

    // Variáveis privadas - valor inicial padrão
    static float _targetTemperature = 12.0f;
    static float _currentTemperature = 25.0f;

    // Status
    static bool _peltierActive = false;
    static bool _fanActive = true;
    static bool _motorActive = false;

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
    
    namespace StatusBar{

        void setPeltierActive(bool active){
            if (xSemaphoreTake(_stateMutex, portMAX_DELAY) == pdTRUE) {
                _peltierActive = active;
                xSemaphoreGive(_stateMutex);
            }
        }

        void setFanActive(bool active){
            if (xSemaphoreTake(_stateMutex, portMAX_DELAY) == pdTRUE) {
                _fanActive = active;
                xSemaphoreGive(_stateMutex);
            }
        }

        void setMotorActive(bool active){
            if (xSemaphoreTake(_stateMutex, portMAX_DELAY) == pdTRUE) {
                _motorActive = active;
                xSemaphoreGive(_stateMutex);
            }
        }

        bool isPeltierActive() {
            return _peltierActive;
        }

        bool isFanActive() {
            return _fanActive;
        }

        bool isMotorActive() {
            return _motorActive;
        }
    }
    
}