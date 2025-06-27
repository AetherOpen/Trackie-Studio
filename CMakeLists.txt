# Versão mínima do CMake e nome do projeto
cmake_minimum_required(VERSION 3.20)
project(TrackieStudio VERSION 1.0)

# Padrão do C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Dependências ---

# 1. Dear ImGui (usando o branch 'docking')
include(FetchContent)
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG docking
)
# Usamos MakeAvailable para baixar e nos dar a variável imgui_SOURCE_DIR
FetchContent_MakeAvailable(imgui)

# 2. Configuração do GLFW
if(WIN32)
    message(STATUS "Configurando para Windows (MinGW)")
    set(GLFW_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfwWIN64)
    message(STATUS "Usando GLFW de: ${GLFW_DIR}")
    set(GLFW_INCLUDE_DIR ${GLFW_DIR}/include)
    set(GLFW_LIBRARY ${GLFW_DIR}/lib-mingw-w64/libglfw3.a)
    set(GLFW_DLL ${GLFW_DIR}/lib-mingw-w64/glfw3.dll)
    if (NOT EXISTS ${GLFW_DLL})
        set(GLFW_DLL ${GLFW_DIR}/glfw3.dll)
    endif()
elseif(APPLE)
    # ... (código para macOS)
else()
    # ... (código para Linux)
endif()

# 3. OpenGL
find_package(OpenGL REQUIRED)

# --- Criação do Executável ---
add_executable(
        TrackieStudio
        src/main.cpp
        src/core/app.cpp
        src/ui/splash_screen.c
        src/ui/main_view.cpp
        src/ui/left_sidebar.cpp
        src/ui/right_sidebar.cpp
        src/ui/center_panel.cpp
)

# --- MUDANÇA 1: Adicionar os fontes do ImGui diretamente ao nosso executável ---
# Em vez de linkar uma biblioteca separada, compilamos os fontes do ImGui
# junto com os nossos. Isso resolve o erro "cannot find -limgui".
target_sources(
        TrackieStudio PRIVATE
        # Fontes do Core do ImGui
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        # E os backends
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

# Inclui os diretórios de cabeçalho necessários
target_include_directories(
        TrackieStudio PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
        ${GLFW_INCLUDE_DIR}
        src
)

# --- MUDANÇA 2: Remover a definição redundante ---
# O branch 'docking' já define IMGUI_HAS_DOCK, então não precisamos mais disso.
# target_compile_definitions(TrackieStudio PRIVATE IMGUI_HAS_DOCK) # REMOVIDO

# --- MUDANÇA 3: Simplificar a linkagem ---
# Agora só precisamos linkar com as dependências REAIS (GLFW, OpenGL),
# pois o ImGui já faz parte do nosso código.
target_link_libraries(
        TrackieStudio PUBLIC
        # A linha 'imgui' foi removida daqui!
        ${GLFW_LIBRARY}
        OpenGL::GL
        gdi32

        -static
)

# Comando para copiar a DLL do GLFW
if(WIN32 AND EXISTS ${GLFW_DLL})
    add_custom_command(
            TARGET TrackieStudio POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${GLFW_DLL}"
            $<TARGET_FILE_DIR:TrackieStudio>
            COMMENT "Copiando glfw3.dll para a pasta do executável"
    )
endif()