#include "hal_display.hpp"
#include "hal_display_assets.hpp"
#include "pins.hpp"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


static constexpr int SCREEN_WIDTH = 128;
static constexpr int SCREEN_HEIGHT = 64;
static constexpr int SCREEN_ADDRESS = 0x3C; 


// Objeto OLED (static para ningueem mexer nele fora daqui)
static Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void hal::display::init() {
    Wire.begin(pins::I2C_SDA_PIN, pins::I2C_SCL_PIN);
    if(!oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println("Erro no OLED");
        return;
    }
    oled.clearDisplay();
    oled.setTextColor(SSD1306_WHITE); // 'WHITE' acende o pixel (seja amarelo ou azul)
    oled.display();
}

void hal::display::clear() {
    oled.clearDisplay();
}

void hal::display::show() {
    oled.display();
}

void hal::display::drawStatusBar(bool peltierOn, bool fanOn, bool motorOn) {
    // Line to split areas
    oled.drawLine(0, 15, SCREEN_WIDTH, 15, SSD1306_WHITE);

    // shows the icons when ON
    if (peltierOn) {
        // drawBitmap(x, y, array_de_bytes, largura, altura, cor)
        oled.drawBitmap(2, 4, assets::icon_snow, 8, 8, SSD1306_WHITE);
    }

    if (fanOn) {
        // Colocamos no X = 14 (dá um espacinho do primeiro ícone)
        oled.drawBitmap(14, 4, assets::icon_fan, 8, 8, SSD1306_WHITE);
    }

    if (motorOn) {
        oled.drawBitmap(26, 4, assets::icon_motor, 8, 8, SSD1306_WHITE);
    }

    oled.drawLine(81, 2 , 81, 12, SSD1306_WHITE);

    oled.setTextSize(1);
    oled.setCursor(85, 5); 
    oled.print("ArduLab");



}

// Mantenha sua showTestScreen aqui embaixo se quiser, para não quebrar o código
void hal::display::showTestScreen() {
    // ... seu código antigo ...
}

void hal::display::drawMainScreen(float current, float target) {
    
    oled.setTextColor(SSD1306_WHITE);

    // --- BLOCO 1: TEMPERATURA ATUAL (DESTAQUE) ---
    // Label pequena
    oled.setTextSize(1);
    oled.setCursor(0, 20); 
    oled.print("Temp Atual:");

    // Valor GRANDE
    oled.setTextSize(2);      // Fonte 2x maior
    oled.setCursor(0, 32);    // Pulei 12 pixels pra baixo
    oled.print(current, 1);   // Ex: "25.5"
    
    // Unidade pequena ao lado do número grande
    oled.setTextSize(1);
    oled.print(" C"); 

    // --- BLOCO 2: ALVO (DISCRETO) ---
    // Vamos desenhar uma linhazinha pra separar?
    oled.drawLine(70, 20, 70, 50, SSD1306_WHITE); // Linha vertical no meio

    oled.setCursor(75, 20);
    oled.print("Alvo:");
    
    oled.setCursor(75, 38);
    oled.setTextSize(1); // Garante que voltou pro pequeno
    oled.print(target, 1);
    oled.print(" C");
}

void hal::display::drawSplashScreen() {
    // drawBitmap(x, y, bitmap, w, h, color)
    // X = 0 (começo da linha)
    // Y = 16 (pula a barra amarela)
    oled.drawBitmap(0, 16, assets::logo_splash, 128, 48, SSD1306_WHITE);
}