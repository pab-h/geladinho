#include <unity.h>
#include "app/state.hpp"
void setUp() {}
void tearDown() {}
void test_temperature_store() {
    state::currentTemperature.store(42.0f);
    TEST_ASSERT_EQUAL_FLOAT(42.0f, state::currentTemperature.load());
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_temperature_store);
    return UNITY_END();
}

