#pragma once
#include <cstdint>

namespace tasks {

    namespace peltier {

        void startPeltierTask();

        void setTargetPower(uint8_t targetPercent);

    }
    
}