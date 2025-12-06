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


namespace {
    void temperatureTask(void* parameter) {
        for (;;) {
            float temp = temperature::readCelsius(10);
            state::currentTemperature.store(temp);

            vTaskDelay(pdMS_TO_TICKS(500)); // mede a cada 500ms
        }
    }
}