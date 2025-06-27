// -----------------------------------------------------------------------------
// center_panel.cpp
//
// Implementação do painel central (Área de Trabalho).
// -----------------------------------------------------------------------------

#include "ui/center_panel.h"
#include "core/app.h"
#include "imgui.h"

namespace UI {

    void RenderCenterPanel(TrackieStudio::App& app) {
        // Cria a janela "Área de Trabalho", o mesmo nome usado no DockBuilder.
        ImGui::Begin("Área de Trabalho");

        // --- Seletor do CoreModel (dependente do AIModel selecionado) ---
        ImGui::Text("CoreModel");
        ImGui::Separator();

        TrackieStudio::AIModel current_ai_model = app.getAIModel();
        if (current_ai_model == TrackieStudio::AIModel::TrackieLLM) {
            const char* trackie_llm_models[] = { "Gemma1bTRCK" };
            int selected_item = 0; // Como só há uma opção, é sempre o índice 0.
            ImGui::Combo("Modelo TrackieLLM", &selected_item, trackie_llm_models, IM_ARRAYSIZE(trackie_llm_models));

        } else if (current_ai_model == TrackieStudio::AIModel::TrackieIntelligence) {
            const char* trackie_intel_models[] = {
                "gemini-2.5 (flash preview native audio dialog)",
                "gemini-2.0 (flash live)",
                "gemini-2.5(flash live preview)"
            };
            int selected_item = 0; // Você precisaria de uma variável em App para guardar isso
            ImGui::Combo("Modelo TrackieIntelligence", &selected_item, trackie_intel_models, IM_ARRAYSIZE(trackie_intel_models));
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();


        // --- Botões e Funções Condicionais ---
        ImGui::Text("Ações");
        ImGui::Separator();

        // Para desabilitar um botão, verificamos a condição. Se não for atendida,
        // usamos ImGui::BeginDisabled() e ImGui::EndDisabled().

        // Botão: Pesquisar na Internet
        bool is_intel_model = (app.getAIModel() == TrackieStudio::AIModel::TrackieIntelligence);
        if (!is_intel_model) ImGui::BeginDisabled();
        ImGui::Button("Pesquisar na Internet");
        if (!is_intel_model) ImGui::EndDisabled();
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) ImGui::SetTooltip("Só funciona com o modelo TrackieIntelligence");

        // Botões que dependem da câmera
        bool has_camera = (app.getInputMode() == TrackieStudio::InputMode::CameraOnly || app.getInputMode() == TrackieStudio::InputMode::AudioAndCamera);
        const char* camera_tooltip = "Requer modo de entrada com Câmera";

        if (!has_camera) ImGui::BeginDisabled();
        ImGui::Button("Object Viewer");
        if (!has_camera) ImGui::EndDisabled();
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) ImGui::SetTooltip(camera_tooltip);

        if (!has_camera) ImGui::BeginDisabled();
        ImGui::Button("Distance Preview");
        if (!has_camera) ImGui::EndDisabled();
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) ImGui::SetTooltip(camera_tooltip);

        if (!has_camera) ImGui::BeginDisabled();
        ImGui::Button("Camera Feed");
        if (!has_camera) ImGui::EndDisabled();
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) ImGui::SetTooltip(camera_tooltip);

        if (!has_camera) ImGui::BeginDisabled();
        ImGui::Button("Segmentation Filter");
        if (!has_camera) ImGui::EndDisabled();
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) ImGui::SetTooltip(camera_tooltip);

        if (!has_camera) ImGui::BeginDisabled();
        ImGui::Button("Navigation Mode");
        if (!has_camera) ImGui::EndDisabled();
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) ImGui::SetTooltip(camera_tooltip);

        // Botão: Silent Mode (sempre ativo)
        ImGui::Button("Silent Mode");

        // Botão: Night Vision (só para Spotway)
        bool is_spotway_mode = (app.getOperatingMode() == TrackieStudio::OperatingMode::Spotway);
        if (!is_spotway_mode) ImGui::BeginDisabled();
        ImGui::Button("Night Vision");
        if (!is_spotway_mode) ImGui::EndDisabled();
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) ImGui::SetTooltip("Só funciona com o módulo Spotway");


        ImGui::End(); // Finaliza a janela "Área de Trabalho"
    }

} // namespace UI