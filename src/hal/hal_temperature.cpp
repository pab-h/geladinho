// leitura ADC (0–4095) → tensão (0–3.3V) → resistência da NTC → temperatura em °C

#include "pins.hpp"
#include <Arduino.h>
#include <cmath>
#include "hal_temperature.hpp"

// constantes do seu circuito
namespace {
    constexpr float VCC = 3.3f;
    constexpr float R_FIXED = 10000.0f;
    constexpr float R0 = 10000.0f;
    constexpr float BETA = 3380.0f;
    // constexpr float T0 = 25.0f + 273.15f;
}
// ------------ Inicialização ------------
void temperature::init() {
    pinMode(pins::TEMP_SENSOR_PIN, INPUT);
}

// ------------ Converte RAW → tensão em volts ------------
static float rawToVoltage(int raw) {
    return (raw / 4095.0f) * VCC;
}

// ------------ Converte tensão → resistência da NTC ------------
static float voltageToRntc(float Vout) {
    if (Vout <= 0.0f) return INFINITY;
    if (Vout >= VCC) return 1e9f;

    // Vout = VCC * Rntc / (Rntc + R_FIXED)
    // Rntc = R_FIXED * Vout / (VCC - Vout)
    return R_FIXED * (Vout / (VCC - Vout));
}

// ------------ Converte resistência → temperatura ------------
static float rToCelsius(float Rntc) {
    float invT = (1.0f / T0) + (1.0f / BETA) * logf(Rntc / R0);
    float Tk = 1.0f / invT;
    return Tk - 273.15f;
}

// ------------ Leitura completa ------------
float temperature::readCelsius(uint8_t samples) {
    float acc = 0;

    for (int i = 0; i < samples; i++) {
        acc += analogRead(pins::TEMP_SENSOR_PIN);
        delay(2); // curto delay p/ estabilizar
    }

    int raw = acc / samples;

    float V = rawToVoltage(raw);
    float Rntc = voltageToRntc(V);
    float Tc = rToCelsius(Rntc);

    return Tc;
}
