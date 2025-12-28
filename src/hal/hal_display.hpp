#pragma once

namespace hal {

    namespace display {
        
        void init();
        
        // Limpa a tela inteira (útil para o inicio do loop)
        void clear();

        // Manda o que desenhamos para o hardware
        void show();

        // Desenha a barra amarela baseada no status
        void drawStatusBar(bool peltierOn, bool fanOn, bool motorOn);

        // (Mantenha a showStatus antiga ou a de teste por enquanto, 
        // depois a gente muda ela para desenhar só na parte azul)
        void showTestScreen(); 

        void drawMainScreen(float current, float target);

        void drawSplashScreen();
    }

}