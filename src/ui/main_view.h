// -----------------------------------------------------------------------------
// main_view.h (Versão 2)
//
// Declaração da função para renderizar a view principal.
// Agora aceita uma referência para o estado da aplicação.
// -----------------------------------------------------------------------------

#pragma once

// Forward Declaration:
// Diz ao compilador que uma classe chamada 'App' existe dentro do namespace
// 'TrackieStudio', sem precisar incluir o arquivo "core/app.h" inteiro.
// Isso previne erros de "inclusão circular" e acelera a compilação.
namespace TrackieStudio {
    class App;
}

namespace UI {

    /**
     * @brief Desenha a interface principal da aplicação.
     *
     * @param app Uma referência ao objeto principal da aplicação que contém todo o estado da UI.
     */
    void RenderMainView(TrackieStudio::App& app);

} // namespace UI