// -----------------------------------------------------------------------------
// main_view.h
//
// Declaração da função para renderizar a view principal da aplicação,
// inspirada no layout do Google AI Studio.
// -----------------------------------------------------------------------------

#pragma once // Garante que este arquivo seja incluído apenas uma vez

namespace UI {

    /**
     * @brief Desenha a interface principal da aplicação.
     *
     * Esta função é chamada a cada frame depois que a tela de splash
     * é concluída. Ela é responsável por desenhar a barra lateral (sidebar)
     * e a área de conteúdo principal.
     */
    void RenderMainView();

} // namespace UI