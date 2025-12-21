#include "task_control.hpp"
#include "task_peltier.hpp"
#include "app/state.hpp"
#include <Arduino.h>

static void controlTask(void* parameter);

namespace tasks {

    namespace control {

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

static void controlTask(void* parameter) {

    for (;;) {

        float current = state::getCurrentTemperature();
        float target = state::getTargetTemperature();

        float diff = current - target;

        if (diff > 0.5f) {
            // temperatura está acima → precisa resfriar
            Serial.println("Controle: Acima do alvo -> Deve resfriar");
            tasks::peltier::setTargetPower(100);
        }
        else if (diff < -0.5f) {
            // temperatura está abaixo → está frio demais
            Serial.println("Controle: Abaixo do alvo -> Desligar Peltier");
            tasks::peltier::setTargetPower(0);

            // aqui vamos desligar o Peltier futuramente
        }
        else {
            Serial.println("Controle: Dentro da faixa -> manter");
        }

        vTaskDelay(pdMS_TO_TICKS(1000)); // roda a cada 1 segundo
    }

}
