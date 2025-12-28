#include "task_input.hpp"
#include "hal/hal_rotary.hpp"
#include "app/state.hpp"      
#include <Arduino.h>

static void inputTaskRoutine(void* parameter);

namespace tasks {
    namespace input {
        void startInputTask() {
            // Priority 2 (Maior que a UI) para garantir leitura precisa
            xTaskCreatePinnedToCore(
                inputTaskRoutine, 
                "InputTask", 
                4096, 
                nullptr, 
                2, 
                nullptr, 
                1
            );
        }
    }
}

static void inputTaskRoutine(void* parameter) {
    
    // Variável local para saber se mudou e imprimir
    long lastPosition = 0;

    Serial.println("[InputTask] Iniciada. Aguardando comandos...");

    for (;;) {
        // 1. Chama sua função do HAL que lê os pinos e atualiza o State
        hal::rotatory::readPosition();

        // 2. Verifica se houve mudança para exibir no Serial (Debug)
        long currentPosition = state::rotatory::getPosition();
        
        if (currentPosition != lastPosition) {
            Serial.printf("Encoder Pos: %ld\n", currentPosition);
            lastPosition = currentPosition;
        }
        // 3. Delay curto (Polling)
        // 5ms é suficiente para botões manuais. 
        // Se fosse um encoder real girando rápido, talvez precisasse de 1ms ou interrupção.
        vTaskDelay(pdMS_TO_TICKS(5)); 
    }
}