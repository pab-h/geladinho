#include <Arduino.h>
#include "tasks/task_temperature.hpp"
#include "tasks/task_control.hpp"
#include <iostream>
#include "tasks/task_temperature.hpp"
#include "tasks/task_control.hpp"
#include "tasks/task_peltier.hpp"
#include "app/state.hpp"
#include "hal/hal_temperature.hpp"
#include "hal/hal_peltier.hpp"

void setup() {

    Serial.begin(9600);

    delay(1000);
    
    Serial.println("\n--- INICIANDO SISTEMA GELADINHO ---");
    
    state::init();
    hal::temperature::init();
    hal::peltier::init();

    tasks::peltier::startPeltierTask();
    tasks::temperature::startReadTemperatureTask();
    tasks::temperature::startControlTask();

    Serial.println("Setup concluído. Tasks rodando...");
    
}

void loop() {
    // Como estamos usando FreeRTOS, o loop do Arduino não faz nada
    // Deletamos esta task padrão para economizar memória RAM
    vTaskDelete(NULL);
}