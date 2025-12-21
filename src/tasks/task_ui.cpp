#include "task_ui.hpp"
#include "hal/hal_display.hpp"
#include "app/state.hpp" // <--- Importante: Incluir o State
#include <Arduino.h>

static void uiTaskRoutine(void* parameter);

namespace tasks {
    namespace ui {
        void startUiTask() {
            xTaskCreatePinnedToCore(
                uiTaskRoutine, "UiTask", 
                4096, nullptr, 1, nullptr, 1
            );
        }
    }
}

static void uiTaskRoutine(void* parameter) {
    vTaskDelay(pdMS_TO_TICKS(100));
    
    // Mostra tela de boas vindas rápida
    hal::display::showTestScreen();
    vTaskDelay(pdMS_TO_TICKS(2000));

    for (;;) {
        // 1. Coleta os dados do Estado Global (Thread-Safe)
        float current = state::getCurrentTemperature();
        float target = state::getTargetTemperature();

        // 2. Manda o HAL desenhar
        hal::display::showStatus(current, target);

        // 3. Atualiza a tela a cada 500ms (não precisa ser super rápido)
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}