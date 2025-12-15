#include <Arduino.h>
#include "tasks/task_temperature.hpp"
#include "tasks/task_control.hpp"
#include <iostream>
#include "tasks/task_temperature.hpp"
#include "tasks/task_control.hpp"
#include "app/state.hpp"
#include "hal/hal_temperature.hpp"

void setup() {

}

void loop() {
    // Como estamos usando FreeRTOS, o loop do Arduino não faz nada
    // Deletamos esta task padrão para economizar memória RAM
    vTaskDelete(NULL);
}