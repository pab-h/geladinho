#include "task_temperature.hpp"
#include "hal/hal_temperature.hpp"
#include "app/state.hpp"
#include <Arduino.h>

void temperatureTask(void* parameter);

namespace tasks {

void startTemperatureTask() {
    xTaskCreatePinnedToCore(
        temperatureTask,
        "TemperatureTask",
        4096,
        nullptr,
        1,
        nullptr,
        1
    );
}

}

    void temperatureTask(void* parameter) {
        vTaskDelay(pdMS_TO_TICKS(100));

        for (;;) {
            float temp = temperature::readCelsius(10);
            Serial.printf("[TempTask] Leitura Raw/Calc: %.2f °C\n", temp);
            state::setCurrentTemperature(temp);

            // Aguarda 2000ms antes da próxima leitura
            vTaskDelay(pdMS_TO_TICKS(2000)); 
        }
    }