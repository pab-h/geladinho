#include <Arduino.h>
#include "state.hpp"

namespace state {

    // Variáveis privadas - valor inicial padrão
    static float targetTemperature = 12.0f;
    static float currentTemperature = 25.0f;

    // Status
    static bool peltierActive = false;
    static bool fanActive = true;
    static bool motorActive = false;

    // Encoder 
    static long position = 12.0f;

    static SemaphoreHandle_t stateMutex = nullptr;

    void init() {
        stateMutex = xSemaphoreCreateMutex();

        if (stateMutex == NULL) {
            Serial.println("[CRITICAL] (state.cpp) Falha ao criar Mutex! em memória RAM (Heap exausted).");
        }
    }


    //Setters e Getters

    void setTargetTemperature(float temp) {

        if (xSemaphoreTake(stateMutex, portMAX_DELAY) == pdTRUE) {
            targetTemperature = temp;
            
            xSemaphoreGive(stateMutex);
        }
    }

    float getTargetTemperature() {
        float val = 0.0f;
        if (xSemaphoreTake(stateMutex, portMAX_DELAY) == pdTRUE) {
            val = targetTemperature;
            xSemaphoreGive(stateMutex);
        }
        return val;
    }

    void setCurrentTemperature(float temp) {
        if (xSemaphoreTake(stateMutex, portMAX_DELAY) == pdTRUE) {
            currentTemperature = temp;
            xSemaphoreGive(stateMutex);
        }
    }

    float getCurrentTemperature() {
        float val = 0.0f;
        if (xSemaphoreTake(stateMutex, portMAX_DELAY) == pdTRUE) {
            val = currentTemperature;
            xSemaphoreGive(stateMutex);
        }
        return val;
    }
    
    namespace statusBar{

        void setPeltierActive(bool active){
            if (xSemaphoreTake(stateMutex, portMAX_DELAY) == pdTRUE) {
                peltierActive = active;
                xSemaphoreGive(stateMutex);
            }
        }

        void setFanActive(bool active){
            if (xSemaphoreTake(stateMutex, portMAX_DELAY) == pdTRUE) {
                fanActive = active;
                xSemaphoreGive(stateMutex);
            }
        }

        void setMotorActive(bool active){
            if (xSemaphoreTake(stateMutex, portMAX_DELAY) == pdTRUE) {
                motorActive = active;
                xSemaphoreGive(stateMutex);
            }
        }

        bool isPeltierActive() {
            return peltierActive;
        }

        bool isFanActive() {
            return fanActive;
        }

        bool isMotorActive() {
            return motorActive;
        }
    }

    namespace rotatory {

        long getPosition() {
            long val = 0;
            if (xSemaphoreTake(stateMutex, portMAX_DELAY) == pdTRUE) {
                val = position;
                xSemaphoreGive(stateMutex);
            }
            return val;
        }
        
        void setPosition(int position) {
            if (xSemaphoreTake(stateMutex, portMAX_DELAY) == pdTRUE) {
                position = position;
                xSemaphoreGive(stateMutex);
            }
        }

    }
    
}