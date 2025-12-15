// leitura ADC (0–4095) → tensão (0–3.3V) → resistência da NTC → temperatura em °C

#include "pins.hpp"
#include <Arduino.h>
#include <cmath>
#include "hal_temperature.hpp"

// Constantes do circuito físico
// constexpr promete que essas variáveis NÃO IRÃO MUDAR
static constexpr float VCC = 3.3f;
static constexpr float R_FIXED = 10000.0f;
static constexpr float R0 = 10000.0f;
static constexpr float BETA = 3380.0f; // quando receber o sensor, tem que ver se os valores é de fato esse no datasheet.
static constexpr float T0_KELVIN = 298.15f; // (Temperatura de referência (25°C))

// Inicialização
void hal::temperature::init() {

    pinMode(pins::TEMP_SENSOR_PIN, INPUT);

}

// Converte RAW → tensão em volts 
static float rawToVoltage(int raw) {

    return (raw / 4095.0f) * VCC;
}

// Converte tensão → resistência da NTC 
static float voltageToRntc(float Vout) {

    if (Vout <= 0.0f) return INFINITY;
    if (Vout >= VCC) return 1e9f;

    return R_FIXED * (Vout / (VCC - Vout));
}

// Converte resistência → temperatura 
static float rToCelsius(float Rntc) {

    float invT = (1.0f / T0_KELVIN) + (1.0f / BETA) * logf(Rntc / R0);
    float Tk = 1.0f / invT;

    return Tk - 273.15f;
}

// Leitura completa
float hal::temperature::readCelsius(uint8_t samples) {

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
