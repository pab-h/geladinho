#include <Arduino.h>
#include <iostream>

// state
#include "app/state.hpp"                // global states

// hal
#include "hal/hal_temperature.hpp"      // temperature
#include "hal/hal_peltier.hpp"          // peltier 
#include "hal/hal_display.hpp"          // display

// tasks
#include "tasks/task_ui.hpp"            // ui (display)
#include "tasks/task_temperature.hpp"   // temperature
#include "tasks/task_control.hpp"       // control
#include "tasks/task_peltier.hpp"       // peltier

void setup() {

    Serial.begin(9600);

    delay(1000);
    
    Serial.println("\n--- INICIANDO SISTEMA GELADINHO ---");
    
    state::init();
    hal::temperature::init();
    hal::peltier::init();
    hal::display::init();

    tasks::peltier::startPeltierTask();
    tasks::temperature::startReadTemperatureTask();
    tasks::temperature::startControlTask();
    tasks::ui::startUiTask();

    
    Serial.println("Setup concluído. Tasks rodando...");
    
}

void loop() {
    // Como estamos usando FreeRTOS, o loop do Arduino não faz nada
    // Deletamos esta task padrão para economizar memória RAM
    vTaskDelete(NULL);
}