#include "task_temperature.hpp"
#include "task_peltier.hpp"
#include "hal/hal_temperature.hpp"
#include "app/state.hpp"
#include <Arduino.h>

static void readTemperatureTask(void* parameter);
static void controlTask(void* parameter);

namespace tasks {

    namespace temperature {

        void startReadTemperatureTask() {
            xTaskCreatePinnedToCore(
                readTemperatureTask,
                "ReadTemperatureTask",
                4096,
                nullptr,
                1,
                nullptr,
                1
            );
        }

        void startControlTask() {
            xTaskCreatePinnedToCore(
                controlTask,
                "ControlTask",
                4096,
                nullptr,
                1,
                nullptr,
                1
            );

        }

    }

}

static void readTemperatureTask(void* parameter) {
    vTaskDelay(pdMS_TO_TICKS(100));

    for (;;) {
        float temp = hal::temperature::readCelsius(10);
        Serial.printf("[TempTask] Leitura Raw/Calc: %.2f °C\n", temp);
        state::setCurrentTemperature(temp);

        // Aguarda 2000ms antes da próxima leitura
        vTaskDelay(pdMS_TO_TICKS(1000)); 
    }
}

static void controlTask(void* parameter) {

    for (;;) {

        float current = state::getCurrentTemperature();
        float target = state::getTargetTemperature();

        float diff = current - target;

        if (diff > 0.5f) {
            // temperatura está acima → precisa resfriar
            Serial.println("Controle: Acima do alvo -> Deve resfriar");
            tasks::peltier::setTargetPower(100);

            state::StatusBar::setPeltierActive(true);
        }
        else if (diff < -0.5f) {
            // temperatura está abaixo → está frio demais
            Serial.println("Controle: Abaixo do alvo -> Desligar Peltier");
            tasks::peltier::setTargetPower(0);
            state::StatusBar::setPeltierActive(false);
        }
        else {
            Serial.println("Controle: Dentro da faixa -> manter");
        }

        vTaskDelay(pdMS_TO_TICKS(1000)); // roda a cada 1 segundo
    }

}
