// -----------------------------------------------------------------------------
// main_view.cpp
//
// Implementação da view principal da aplicação.
// -----------------------------------------------------------------------------

#include "ui/main_view.h"
#include "imgui.h"

namespace UI {

    void RenderMainView() {
        // Variável estática para manter o estado da sidebar (aberta/fechada) entre os frames.
        static bool is_sidebar_open = true;

        // 1. Configurar o Viewport Principal como um DockSpace
        //    Isso transforma a janela principal em uma área onde outras janelas (docks) podem se encaixar.
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGuiWindowFlags host_window_flags = 0;
        host_window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        host_window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        host_window_flags |= ImGuiWindowFlags_NoBackground; // O dockspace já tem fundo

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        ImGui::Begin("DockSpace Host", nullptr, host_window_flags);

        ImGui::PopStyleVar(3);

        // Cria o DockSpace
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

        // 2. Renderizar a Sidebar (se estiver aberta)
        if (is_sidebar_open) {
            ImGui::Begin("Sidebar", &is_sidebar_open); // O &is_sidebar_open cria um 'x' para fechar

            // Botão para fechar a sidebar (opcional, já que temos o 'x')
            if (ImGui::Button("Fechar Sidebar")) {
                is_sidebar_open = false;
            }
            ImGui::Separator();

            // Lógica para os dois botões grandes
            float available_height = ImGui::GetContentRegionAvail().y;
            ImVec2 button_size(ImGui::GetContentRegionAvail().x, (available_height / 2.0f) - ImGui::GetStyle().ItemSpacing.y);

            // Botão de Cima
            if (ImGui::Button("Ação 1", button_size)) {
                // Lógica para quando o primeiro botão for clicado
            }

            // Botão de Baixo
            if (ImGui::Button("Ação 2", button_size)) {
                // Lógica para quando o segundo botão for clicado
            }

            ImGui::End();
        }

        // 3. Renderizar a janela de Conteúdo Principal
        ImGui::Begin("Conteúdo Principal");

        // Se a sidebar estiver fechada, mostramos um botão para abri-la
        if (!is_sidebar_open) {
            if (ImGui::Button("Abrir Sidebar")) {
                is_sidebar_open = true;
            }
        }

        ImGui::Text("Esta é a área de conteúdo principal.");
        ImGui::Text("A sua UI, similar ao Google AI Studio, aparecerá aqui.");
        ImGui::Separator();
        ImGui::Text("Frames por segundo: %.1f", ImGui::GetIO().Framerate);

        ImGui::End();

        // Finaliza o Dockspace Host
        ImGui::End();
    }

} // namespace UI