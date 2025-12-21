#include "task_peltier.hpp"
#include "hal/hal_peltier.hpp"
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

static QueueHandle_t peltierQueue = nullptr;

static void peltierTaskRoutine(void* parameter);

namespace tasks {

    namespace peltier {

        void startPeltierTask() {

            peltierQueue = xQueueCreate(1, sizeof(uint8_t));

            xTaskCreatePinnedToCore(
                peltierTaskRoutine, "PeltierTask", 4096, nullptr, 1, nullptr, 1
            );
        }

        void setTargetPower(uint8_t targetPercent) {

            if (peltierQueue != nullptr) {

                xQueueOverwrite(peltierQueue, &targetPercent);

            }
            
        }

    }

}

// Configurações da Rampa
static constexpr int RAMP_DELAY_MS = 50;  // Atualiza a cada 50ms
static constexpr int RAMP_STEP = 1;       // Sobe 1% por vez

static void peltierTaskRoutine(void* parameter) {
    
    int currentPower = 0; // Potência real aplicada agora
    uint8_t targetPower = 0; // Onde queremos chegar

    for (;;) {
        
        uint8_t newCommand;
        if (xQueueReceive(peltierQueue, &newCommand, 0) == pdTRUE) {
            targetPower = newCommand;
            Serial.printf("[PeltierTask] Novo alvo recebido: %d%%\n", targetPower);
        }

        // (Soft Start / Soft Stop)
        if (currentPower < targetPower) {
            currentPower += RAMP_STEP;
            if (currentPower > targetPower) currentPower = targetPower;
        } 
        else if (currentPower > targetPower) {
            currentPower -= RAMP_STEP;
            if (currentPower < targetPower) currentPower = targetPower;
        }

        hal::peltier::setPower((uint8_t)currentPower);

        vTaskDelay(pdMS_TO_TICKS(RAMP_DELAY_MS));
    }
}