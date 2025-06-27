// -----------------------------------------------------------------------------
// right_sidebar.h
//
// Declaração da função para renderizar o painel da barra lateral direita.
// -----------------------------------------------------------------------------

#pragma once

// Forward Declaration para a classe App.
namespace TrackieStudio {
    class App;
}

namespace UI {

    /**
     * @brief Desenha o painel de configurações na barra lateral direita.
     *
     * Este painel contém os controles principais para o modelo de IA,
     * modo de entrada, e outras configurações e ferramentas.
     *
     * @param app Uma referência ao objeto principal da aplicação.
     */
    void RenderRightSidebar(TrackieStudio::App& app);

} // namespace UI