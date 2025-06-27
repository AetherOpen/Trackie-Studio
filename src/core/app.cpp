// -----------------------------------------------------------------------------
// app.cpp
//
// Implementação da classe principal da aplicação, TrackieStudio::App.
// -----------------------------------------------------------------------------

#include "core/app.h"

// Incluímos os cabeçalhos dos nossos módulos de UI.
// Estes arquivos ainda não existem, mas os criaremos nos próximos passos.
// Eles conterão as funções que desenham as telas específicas.
#include "ui/splash_screen.h"
#include "ui/main_view.h"

#include <stdio.h> // Para printf (debug)

namespace TrackieStudio {

    // Implementação do construtor
    App::App() {
        // Ao criar a aplicação, definimos a tela inicial como a Splash Screen.
        m_currentScreen = ScreenState::SplashScreen;
        printf("TrackieStudio::App inicializada. Tela atual: SplashScreen\n");
    }

    // Implementação do destrutor
    App::~App() {
        // Este espaço pode ser usado para limpeza de recursos no futuro.
        printf("TrackieStudio::App finalizada.\n");
    }


    // Implementação do método principal de renderização
    void App::renderUI() {
        // Usamos um switch para controlar qual tela renderizar
        // com base no valor de m_currentScreen.
        switch (m_currentScreen) {
            case ScreenState::SplashScreen: {
                // Chamamos a função que desenha a tela de splash.
                // Esta função (que criaremos a seguir) retornará 'true' quando sua
                // animação/tempo de espera terminar.
                bool splashFinished = UI::RenderSplashScreen();

                // Se a tela de splash terminou, mudamos o estado para a tela principal.
                if (splashFinished) {
                    m_currentScreen = ScreenState::MainView;
                    printf("Mudando de SplashScreen para MainView\n");
                }
                break;
            }

            case ScreenState::MainView: {
                // Uma vez no estado MainView, simplesmente chamamos a função
                // que desenha a interface principal da aplicação.
                UI::RenderMainView();
                break;
            }
        }
    }

} // namespace TrackieStudio