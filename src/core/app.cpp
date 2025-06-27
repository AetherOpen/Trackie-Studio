// -----------------------------------------------------------------------------
// app.cpp (Versão 2)
//
// Implementação da classe App. Agora inicializa todo o estado da UI
// e passa a si mesma como referência para a função de renderização da MainView.
// -----------------------------------------------------------------------------

#include "core/app.h"
#include "ui/splash_screen.h"
#include "ui/main_view.h" // Este arquivo será modificado a seguir

#include <stdio.h>

namespace TrackieStudio {

    // Implementação do construtor usando lista de inicialização
    App::App() :
        m_currentScreen(ScreenState::SplashScreen),
        m_operatingMode(OperatingMode::Trackie), // Modo padrão: Trackie
        m_aiModel(AIModel::TrackieLLM),          // Modelo padrão: TrackieLLM
        m_inputMode(InputMode::AudioAndCamera),  // Entrada padrão: Audio e Camera
        m_turnCoverage(true),                    // Alavancas (valores padrão)
        m_affectiveDialog(false),
        m_proactiveAudio(true),
        m_toolDistanceMeasurement(true),         // Ferramentas (valores padrão)
        m_toolAdvancedDetection(false),
        m_toolFaceRecognition(false),
        m_selectedCoreModel(0)                   // Nenhum modelo do dropdown selecionado por padrão
    {
        printf("TrackieStudio::App (V2) inicializada. Estado padrão configurado.\n");
    }

    App::~App() {
        printf("TrackieStudio::App finalizada.\n");
    }

    void App::renderUI() {
        switch (m_currentScreen) {
            case ScreenState::SplashScreen: {
                bool splashFinished = UI::RenderSplashScreen();
                if (splashFinished) {
                    m_currentScreen = ScreenState::MainView;
                    printf("Mudando de SplashScreen para MainView\n");
                }
                break;
            }

            case ScreenState::MainView: {
                // MUDANÇA CRÍTICA:
                // Agora passamos uma referência do objeto 'App' inteiro para a MainView.
                // Isso dá a toda a UI acesso ao estado centralizado.
                UI::RenderMainView(*this);
                break;
            }
        }
    }

} // namespace TrackieStudio