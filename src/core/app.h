// -----------------------------------------------------------------------------
// app.h (Versão 2)
//
// Declaração da classe principal da aplicação, TrackieStudio::App.
// Agora expandida para gerenciar todo o estado da UI.
// -----------------------------------------------------------------------------

#pragma once

#include <string>

namespace TrackieStudio {

    // Enum para o modo de operação principal
    enum class OperatingMode {
        Trackie,
        Spotway
    };

    // Enum para o modelo de IA principal
    enum class AIModel {
        TrackieLLM,
        TrackieIntelligence
    };

    // Enum para o modo de entrada de dados
    enum class InputMode {
        AudioOnly,
        CameraOnly,
        AudioAndCamera
    };

    class App {
    public:
        App();
        ~App();

        void renderUI();

        // --- Getters e Setters para o estado da UI ---
        // (Permitem que os módulos de UI leiam e modifiquem o estado de forma controlada)

        OperatingMode getOperatingMode() const { return m_operatingMode; }
        void setOperatingMode(OperatingMode mode) { m_operatingMode = mode; }

        AIModel getAIModel() const { return m_aiModel; }
        void setAIModel(AIModel model) { m_aiModel = model; }

        InputMode getInputMode() const { return m_inputMode; }
        void setInputMode(InputMode mode) { m_inputMode = mode; }

        // Exemplo para um switch. Faremos isso para todos.
        bool& getTurnCoverage() { return m_turnCoverage; }
        bool& getAffectiveDialog() { return m_affectiveDialog; }
        bool& getProactiveAudio() { return m_proactiveAudio; }

        // Tools
        bool& getToolDistanceMeasurement() { return m_toolDistanceMeasurement; }
        bool& getToolAdvancedDetection() { return m_toolAdvancedDetection; }
        bool& getToolFaceRecognition() { return m_toolFaceRecognition; }


    private:
        // O estado da tela (Splash/Main)
        enum class ScreenState { SplashScreen, MainView } m_currentScreen;

        // --- Variáveis de Estado da UI Principal ---

        // Painel Esquerdo
        OperatingMode m_operatingMode;

        // Painel Direito
        AIModel m_aiModel;
        InputMode m_inputMode;

        // Alavancas
        bool m_turnCoverage;
        bool m_affectiveDialog;
        bool m_proactiveAudio;

        // Ferramentas (Tools)
        bool m_toolDistanceMeasurement;
        bool m_toolAdvancedDetection;
        bool m_toolFaceRecognition;

        // Variáveis para os seletores (dropdowns)
        int m_selectedCoreModel; // Índice do modelo selecionado

        // Adicionaremos mais estados aqui conforme necessário
    };

} // namespace TrackieStudio