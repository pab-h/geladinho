#include "state.hpp"

namespace state {

std::atomic<float> currentTemperature{25.0f};  
std::atomic<float> targetTemperature{10.0f};

}
