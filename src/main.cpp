// -----------------------------------------------------------------------------
// main.cpp
//
// Ponto de entrada da aplicação TrackieStudio.
// Responsabilidades:
// 1. Inicializar a biblioteca de janelas (GLFW).
// 2. Criar uma janela com um contexto OpenGL.
// 3. Inicializar a biblioteca de GUI (Dear ImGui).
// 4. Instanciar a classe principal da aplicação (App).
// 5. Executar o loop principal que processa eventos, renderiza a UI e
//    atualiza a janela.
// 6. Limpar todos os recursos ao sair.
// -----------------------------------------------------------------------------

#include <stdio.h>

// Headers do Dear ImGui
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// Header do GLFW (biblioteca para criar janelas e gerenciar inputs)
#include <GLFW/glfw3.h>

// Header da nossa lógica de aplicação principal
// (Este arquivo será criado no próximo passo)
#include "core/app.h"

// Função de callback para erros do GLFW
static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main(int, char**) {
    // --- 1. Inicialização do GLFW ---
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        return 1;
    }

    // Definimos a versão do OpenGL que queremos usar (OpenGL 3.3)
    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Usar perfil "Core"
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Necessário para macOS
    #endif

    // --- 2. Criação da Janela ---
    // Criamos a janela com 1280x720 de resolução e o título "TrackieStudio"
    GLFWwindow* window = glfwCreateWindow(1280, 720, "TrackieStudio", nullptr, nullptr);
    if (window == nullptr) {
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Ativa o V-Sync (sincronização vertical)

    // --- 3. Inicialização do Dear ImGui ---
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Habilita navegação por teclado
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Habilita Docking (essencial para layouts complexos)
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Habilita janelas ImGui fora da janela principal

    // Define o estilo visual do ImGui
    ImGui::StyleColorsDark();

    // Ajusta o estilo quando viewports estão ativadas
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Inicializa os backends do ImGui para GLFW e OpenGL
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // --- 4. Instanciação da Aplicação ---
    // Aqui criamos o objeto que conterá toda a lógica e estado do nosso app.
    TrackieStudio::App app;

    // --- 5. Loop Principal (Render Loop) ---
    while (!glfwWindowShouldClose(window)) {
        // Processa todos os eventos pendentes (teclado, mouse, etc.)
        glfwPollEvents();

        // Inicia um novo frame do Dear ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // ** Chamada para renderizar a nossa UI. Toda a lógica de qual tela mostrar
        // ** e como desenhá-la está encapsulada dentro do método `app.renderUI()`
        app.renderUI();

        // Renderiza o frame do ImGui
        ImGui::Render();

        // Limpa a tela com uma cor de fundo
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Cinza escuro, bom para ferramentas dev
        glClear(GL_COLOR_BUFFER_BIT);

        // Desenha os dados do ImGui na tela
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Atualiza e renderiza as viewports adicionais (se houver)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        // Troca os buffers da janela (mostra o que foi renderizado)
        glfwSwapBuffers(window);
    }

    // --- 6. Finalização e Limpeza ---
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}