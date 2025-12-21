#include "hal_display.hpp"
#include "pins.hpp"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "app/state.hpp"
// Configurações do OLED
namespace {
    constexpr int SCREEN_WIDTH = 128;
    constexpr int SCREEN_HEIGHT = 64;
    constexpr int OLED_RESET = -1; 
    constexpr int SCREEN_ADDRESS = 0x3C; 
}

// MUDANÇA AQUI: Renomeado de 'display' para 'oled' para não conflitar com o namespace
static Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void hal::display::init() {
    // Inicia o I2C
    Wire.begin(pins::I2C_SDA_PIN, pins::I2C_SCL_PIN);

    // Tenta iniciar o display usando o objeto 'oled'
    if(!oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("[Display] Falha na alocação do SSD1306"));
        return;
    }

    oled.clearDisplay();
    oled.display();
    
    oled.setTextSize(1);
    oled.setTextColor(SSD1306_WHITE);
}

void hal::display::showTestScreen() {
    oled.clearDisplay();

    // Desenha uma borda
    oled.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);

    // Escreve um texto
    oled.setCursor(10, 20); 
    oled.setTextSize(2);   
    oled.print("Geladinho");

    oled.setCursor(20, 45); 
    oled.setTextSize(1);   
    oled.print("Temperatura atual ^^");

    oled.display();
}

// ... includes anteriores ...

void hal::display::showStatus(float currentTemp, float targetTemp) {
    oled.clearDisplay();

    // --- TÍTULO ---
    oled.setCursor(0, 0);
    oled.setTextSize(1);
    oled.print("GELADINHO SYS");

    // --- TEMPERATURA ATUAL (Grande) ---
    oled.setCursor(0, 15);
    oled.setTextSize(2);
    oled.print("T: ");
    oled.print(currentTemp, 1); // 1 casa decimal
    oled.print(" C");

    // --- ALVO (Menor) ---
    oled.setCursor(0, 40);
    oled.setTextSize(1);
    oled.print("Alvo: ");
    oled.print(targetTemp, 1);
    oled.print(" C");

    // --- STATUS DO PELTIER (Visual Extra) ---
    // Podemos desenhar uma bolinha se estiver gelando, mas por enquanto vamos só de texto
    // (Isso exigiria passar o status do peltier como parametro tambem)

    oled.display();
}