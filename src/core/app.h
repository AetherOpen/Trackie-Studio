// -----------------------------------------------------------------------------
// app.h
//
// Declaração da classe principal da aplicação, TrackieStudio::App.
//
// Responsabilidades:
// 1. Manter o estado geral da aplicação (ex: qual tela está ativa).
// 2. Expor um método público `renderUI()` que será chamado pelo `main.cpp`
//    a cada frame para desenhar a interface.
// -----------------------------------------------------------------------------

#pragma once // Garante que este arquivo seja incluído apenas uma vez

namespace TrackieStudio {

    class App {
    public:
        // Construtor: chamado quando o objeto App é criado em main.cpp.
        // Usado para inicializar o estado da aplicação.
        App();

        // Destrutor: chamado quando a aplicação está prestes a fechar.
        // Usado para limpar quaisquer recursos que a classe App possa ter alocado.
        ~App();

        // Método principal de renderização da UI.
        // O loop em main.cpp chama esta função a cada frame.
        void renderUI();

    private:
        // Um enum para representar os diferentes "estados" ou "telas" da nossa UI.
        // Isso nos permite controlar facilmente o que está sendo exibido.
        enum class ScreenState {
            SplashScreen,
            MainView
        };

        // Variável que armazena a tela atual.
        // O 'm_' é uma convenção comum para indicar que é uma variável membro (member).
        ScreenState m_currentScreen;

        // No futuro, podemos adicionar mais variáveis de estado aqui,
        // como dados do projeto, configurações do usuário, etc.
    };

} // namespace TrackieStudio