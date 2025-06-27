// -----------------------------------------------------------------------------
// main_view.cpp (Versão 2)
//
// Implementação da view principal, agora como um "maestro" de layout.
// Sua única responsabilidade é criar o DockSpace e chamar as funções
// que renderizam os painéis individuais.
// -----------------------------------------------------------------------------

#include "ui/main_view.h"

// Precisamos do cabeçalho da App para poder usar seus métodos (get/set).
#include "core/app.h"

// Incluímos os cabeçalhos dos nossos novos módulos de UI.
// Estes arquivos serão criados nos próximos passos.
#include "ui/left_sidebar.h"
#include "ui/center_panel.h"
#include "ui/right_sidebar.h"

#include "imgui.h"
#include "imgui_internal.h" // Necessário para alguns controles de docking avançados

namespace UI {

    void RenderMainView(TrackieStudio::App& app) {
        // 1. Configurar o Viewport Principal como um DockSpace
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGuiWindowFlags host_window_flags = 0;
        host_window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        host_window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        host_window_flags |= ImGuiWindowFlags_NoBackground;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        ImGui::Begin("DockSpace Host", nullptr, host_window_flags);
        ImGui::PopStyleVar(3);

        // 2. Criar o DockSpace e o Layout Inicial
        ImGuiID dockspace_id = ImGui::GetID("MainDockSpace");

        // Lógica para configurar o layout na primeira vez que a aplicação é aberta.
        static bool is_first_time = true;
        if (is_first_time) {
            is_first_time = false;

            ImGui::DockBuilderRemoveNode(dockspace_id); // Limpa qualquer layout salvo
            ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
            ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->WorkSize);

            // Divide o dockspace: um nó esquerdo, um direito, e o resto fica no centro
            ImGuiID dock_left, dock_right;
            ImGuiID dock_center = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.20f, &dock_left, nullptr); // 20% para a esquerda
            dock_center = ImGui::DockBuilderSplitNode(dock_center, ImGuiDir_Right, 0.25f, &dock_right, &dock_center); // 25% do restante para a direita

            // Diz a cada janela onde ela deve "nascer"
            ImGui::DockBuilderDockWindow("Ferramentas", dock_left);
            ImGui::DockBuilderDockWindow("Configurações", dock_right);
            ImGui::DockBuilderDockWindow("Área de Trabalho", dock_center);

            ImGui::DockBuilderFinish(dockspace_id);
        }

        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

        // 3. Chamar as funções que renderizam cada painel
        //    Passamos a referência 'app' para que eles possam ler e modificar o estado.
        RenderLeftSidebar(app);
        RenderCenterPanel(app);
        RenderRightSidebar(app);

        ImGui::End(); // Finaliza o Dockspace Host
    }

} // namespace UI