// -----------------------------------------------------------------------------
// left_sidebar.h
//
// Declaração da função para renderizar o painel da barra lateral esquerda.
// -----------------------------------------------------------------------------

#pragma once

// Forward Declaration para a classe App, evitando inclusão completa do header.
namespace TrackieStudio {
    class App;
}

namespace UI {

    /**
     * @brief Desenha o painel da barra lateral esquerda.
     *
     * Este painel é responsável por mostrar e controlar o modo de
     * operação principal (Trackie vs Spotway).
     *
     * @param app Uma referência ao objeto principal da aplicação.
     */
    void RenderLeftSidebar(TrackieStudio::App& app);

} // namespace UI