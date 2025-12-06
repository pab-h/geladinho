#pragma once
#include <atomic>

namespace state {

    // Temperatura atual lida pelo sensor
    extern std::atomic<float> currentTemperature;

    // Setpoint definido pelo usuário (pode editar de outra task)
    extern std::atomic<float> targetTemperature;

}
