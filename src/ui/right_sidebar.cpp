// -----------------------------------------------------------------------------
// right_sidebar.cpp
//
// Implementação do painel de configurações da barra lateral direita.
// -----------------------------------------------------------------------------

#include "ui/right_sidebar.h"
#include "core/app.h"
#include "imgui.h"

namespace UI {

    void RenderRightSidebar(TrackieStudio::App& app) {
        // Cria a janela "Configurações", o mesmo nome usado no DockBuilder.
        ImGui::Begin("Configurações");

        // --- Seletor de Modelo de IA Principal ---
        ImGui::Text("Run settings"); // Título da seção

        const char* model_names[] = { "TrackieLLM", "TrackieIntelligence" };
        int current_model_index = static_cast<int>(app.getAIModel());

        // CORREÇÃO DEFINITIVA: Adicionado o '&' que faltava.
        if (ImGui::Combo("Modelo de IA", ¤t_model_index, model_names, IM_ARRAYSIZE(model_names))) {
            app.setAIModel(static_cast<TrackieStudio::AIModel>(current_model_index));
        }

        ImGui::Separator();

        // --- Seletor de Modo de Entrada ---
        ImGui::Text("Output format");

        // Usamos botões selecionáveis para imitar o estilo do AI Studio
        int current_input_mode = static_cast<int>(app.getInputMode());

        if (ImGui::Selectable("Audio", current_input_mode == 0)) {
            app.setInputMode(TrackieStudio::InputMode::AudioOnly);
        }
        if (ImGui::Selectable("Camera", current_input_mode == 1)) {
            app.setInputMode(TrackieStudio::InputMode::CameraOnly);
        }
        if (ImGui::Selectable("Audio & Camera", current_input_mode == 2)) {
            app.setInputMode(TrackieStudio::InputMode::AudioAndCamera);
        }

        ImGui::Separator();

        // --- Alavancas de Configuração ---
        ImGui::Text("Configurações Gerais");

        // Como o getter em app.h retorna uma referência (bool&), o ImGui::Checkbox
        // pode modificar o valor diretamente.
        ImGui::Checkbox("Turn Coverage", &app.getTurnCoverage());
        ImGui::Checkbox("Affective Dialog", &app.getAffectiveDialog());
        ImGui::Checkbox("Proactive Audio", &app.getProactiveAudio());

        ImGui::Separator();

        // --- Ferramentas (Tools) ---
        ImGui::Text("Tools");

        // As ferramentas também são vinculadas diretamente às variáveis de estado.
        // A lógica de "só funcionar se..." será implementada no painel central.
        // Aqui, nós apenas permitimos que elas sejam ligadas/desligadas.
        ImGui::Checkbox("Medição de Distâncias", &app.getToolDistanceMeasurement());
        ImGui::Checkbox("Detecção Avançada", &app.getToolAdvancedDetection());
        ImGui::Checkbox("Reconhecer Rostos", &app.getToolFaceRecognition());

        ImGui::End(); // Finaliza a janela "Configurações"
    }

} // namespace UI