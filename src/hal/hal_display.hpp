#pragma once

namespace hal {

    namespace display {
        
        void init();

        void showStatus(float currentTemp, float targetTemp);

        void showTestScreen();
    }

}