#pragma once

#include <cstdint>

namespace hal {

    namespace temperature {

        void init();

        // Lê temperatura em graus Celsius
        float readCelsius(uint8_t samples = 10);
        
    }

}
