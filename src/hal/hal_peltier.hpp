#pragma once
#include <cstdint>

namespace hal {

    namespace peltier {
        
        void init();

        void setPower(uint8_t intensity);

    }

}