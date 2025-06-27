// -----------------------------------------------------------------------------
// left_sidebar.cpp
//
// Implementação do painel da barra lateral esquerda.
// -----------------------------------------------------------------------------

#include "ui/left_sidebar.h"
#include "core/app.h" // Incluímos o header completo para usar os métodos da App
#include "imgui.h"

namespace UI {

    void RenderLeftSidebar(TrackieStudio::App& app) {
        // Cria a janela da sidebar. O nome "Ferramentas" deve ser o mesmo
        // usado no DockBuilder em main_view.cpp.
        ImGui::Begin("Ferramentas");

        // Obtém o modo de operação atual do estado da aplicação
        TrackieStudio::OperatingMode current_mode = app.getOperatingMode();

        // --- Lógica de Estilo para Botão Ativo ---
        // Vamos "empurrar" uma cor para o botão ativo e usar a cor padrão para o inativo.
        // A cor de um botão ativo será um cinza mais claro.
        const ImVec4 active_color = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
        const ImVec4 inactive_color = ImGui::GetStyle().Colors[ImGuiCol_Button]; // Pega a cor padrão do tema

        // --- Desenho dos Botões ---

        // Calcula o tamanho dos botões para preencher o espaço verticalmente
        float available_height = ImGui::GetContentRegionAvail().y;
        float spacing = ImGui::GetStyle().ItemSpacing.y;
        ImVec2 button_size(ImGui::GetContentRegionAvail().x, (available_height - spacing) / 2.0f);

        // Botão Trackie
        // Se o modo atual NÃO é Trackie, usamos a cor inativa.
        // Se for, não empurramos cor nenhuma (deixamos o padrão de "ativo") ou podemos forçar uma.
        if (current_mode != TrackieStudio::OperatingMode::Trackie) {
            ImGui::PushStyleColor(ImGuiCol_Button, inactive_color);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered]);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);
        } else {
             ImGui::PushStyleColor(ImGuiCol_Button, active_color);
             ImGui::PushStyleColor(ImGuiCol_ButtonHovered, active_color);
             ImGui::PushStyleColor(ImGuiCol_ButtonActive, active_color);
        }

        if (ImGui::Button("Trackie", button_size)) {
            // Se o botão for clicado, atualiza o estado da aplicação
            app.setOperatingMode(TrackieStudio::OperatingMode::Trackie);
        }
        ImGui::PopStyleColor(3); // Remove as 3 cores que empurramos


        // Botão Spotway
        if (current_mode != TrackieStudio::OperatingMode::Spotway) {
            ImGui::PushStyleColor(ImGuiCol_Button, inactive_color);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered]);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);
        } else {
             ImGui::PushStyleColor(ImGuiCol_Button, active_color);
             ImGui::PushStyleColor(ImGuiCol_ButtonHovered, active_color);
             ImGui::PushStyleColor(ImGuiCol_ButtonActive, active_color);
        }

        if (ImGui::Button("Spotway", button_size)) {
            // Se o botão for clicado, atualiza o estado da aplicação
            app.setOperatingMode(TrackieStudio::OperatingMode::Spotway);
        }
        ImGui::PopStyleColor(3);

        ImGui::End(); // Finaliza a janela "Ferramentas"
    }

} // namespace UI