// -----------------------------------------------------------------------------
// splash_screen.cpp
//
// Implementação da tela de splash.
// -----------------------------------------------------------------------------

#include "ui/splash_screen.h"
#include "imgui.h"
#include <chrono> // Para o temporizador

namespace UI {

    bool RenderSplashScreen() {
        // Usamos variáveis estáticas para que seus valores persistam entre as chamadas da função.
        // Isso é essencial para o nosso temporizador.
        static auto startTime = std::chrono::steady_clock::now();
        static const float splashDuration = 3.0f; // Duração da splash screen em segundos

        // 1. Obter o viewport principal para centralizar nossa janela
        const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
        ImVec2 center = main_viewport->GetCenter();

        // 2. Definir a posição e o tamanho da nossa janela de splash antes de criá-la
        ImVec2 window_size(400, 200);
        ImGui::SetNextWindowPos(ImVec2(center.x - window_size.x * 0.5f, center.y - window_size.y * 0.5f));
        ImGui::SetNextWindowSize(window_size);

        // 3. Definir o estilo da janela de splash (sem borda, sem título, etc.)
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoTitleBar;
        window_flags |= ImGuiWindowFlags_NoResize;
        window_flags |= ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoScrollbar;
        window_flags |= ImGuiWindowFlags_NoCollapse;

        // 4. Desenhar a janela
        bool window_open = true; // Necessário para a função Begin
        ImGui::Begin("Splash Screen", &window_open, window_flags);

        // --- Conteúdo da Splash Screen ---

        // Centraliza o texto horizontalmente
        const char* title = "TrackieStudio";
        ImVec2 titleSize = ImGui::CalcTextSize(title);
        ImGui::SetCursorPosX((window_size.x - titleSize.x) * 0.5f);
        ImGui::SetCursorPosY(window_size.y * 0.3f); // Posiciona verticalmente
        ImGui::Text("%s", title);

        const char* loadingText = "Carregando...";
        ImVec2 loadingTextSize = ImGui::CalcTextSize(loadingText);
        ImGui::SetCursorPosX((window_size.x - loadingTextSize.x) * 0.5f);
        ImGui::SetCursorPosY(window_size.y * 0.6f); // Posiciona verticalmente
        ImGui::Text("%s", loadingText);

        // (Futuramente, aqui poderíamos desenhar o logo da aplicação)

        ImGui::End();

        // 5. Lógica do temporizador
        auto currentTime = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsedTime = currentTime - startTime;

        // Se o tempo decorrido for maior que a duração definida, retornamos 'true'.
        if (elapsedTime.count() > splashDuration) {
            return true;
        }

        // Caso contrário, retornamos 'false' para continuar mostrando a tela.
        return false;
    }

} // namespace UI