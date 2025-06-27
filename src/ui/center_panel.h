// -----------------------------------------------------------------------------
// center_panel.h
//
// Declaração da função para renderizar o painel central (Área de Trabalho).
// -----------------------------------------------------------------------------

#pragma once

// Forward Declaration para a classe App.
namespace TrackieStudio {
    class App;
}

namespace UI {

    /**
     * @brief Desenha o conteúdo do painel central (Área de Trabalho).
     *
     * Este painel é o mais dinâmico, exibindo controles e informações
     * com base no estado atual da aplicação (modo, modelo, ferramentas ativas, etc.).
     *
     * @param app Uma referência ao objeto principal da aplicação.
     */
    void RenderCenterPanel(TrackieStudio::App& app);

} // namespace UI