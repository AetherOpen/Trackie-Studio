// -----------------------------------------------------------------------------
// splash_screen.h
//
// Declaração da função para renderizar a tela de splash.
// -----------------------------------------------------------------------------

#pragma once // Garante que este arquivo seja incluído apenas uma vez

namespace UI {

    /**
     * @brief Desenha a tela de splash no centro da janela.
     *
     * Esta função é projetada para ser chamada a cada frame enquanto o estado
     * da aplicação for SplashScreen.
     *
     * @return bool - Retorna 'true' quando a tela de splash deve ser fechada
     *                e a aplicação deve transicionar para o próximo estado.
     *                Retorna 'false' se a tela deve continuar sendo exibida.
     */
    bool RenderSplashScreen();

} // namespace UI