# CMakeLists.txt para o projeto TrackieStudio

# 1. Definição Mínima do CMake e Nome do Projeto
# --------------------------------------------------
cmake_minimum_required(VERSION 3.16)
project(TrackieStudio VERSION 1.0 LANGUAGES CXX)


# 2. Encontrar o Pacote Qt6
# --------------------------------------------------
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)


# 3. Configuração da Integração com Qt
# --------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


# 4. Coleta dos Arquivos-Fonte do Projeto
# --------------------------------------------------
set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow/mainwindow.cpp
        src/components/leftsidebar/leftsidebar.cpp
        src/components/rightsidebar/rightsidebar.cpp
        src/components/centralpanel/centralpanel.cpp
        src/components/rightsidebar/ToggleSwitch.cpp
        src/components/loadingscreen/loadingscreen.cpp
)

set(PROJECT_HEADERS
        src/mainwindow/mainwindow.h
        src/components/leftsidebar/leftsidebar.h
        src/components/rightsidebar/rightsidebar.h
        src/components/centralpanel/centralpanel.h
        src/components/rightsidebar/ToggleSwitch.h
        src/components/loadingscreen/loadingscreen.h
)

set(PROJECT_RESOURCES
        resources/resources.qrc
)


# 5. Criação do Executável
# --------------------------------------------------
add_executable(TrackieStudio
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        ${PROJECT_RESOURCES}
)


# 6. Vinculação e Diretórios de Inclusão
# --------------------------------------------------
target_link_libraries(TrackieStudio PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

target_include_directories(TrackieStudio PRIVATE src)


# 7. LÓGICA DE DEPLOYMENT PARA WINDOWS (RESOLVE O PROBLEMA DAS DLLS)
# --------------------------------------------------------------------
if(WIN32)
    # Define o diretório onde o .exe será colocado.
    set(RUNTIME_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)
    set_target_properties(TrackieStudio PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIR})

    # Pega o caminho completo para a ferramenta windeployqt.
    # Qt6::windeployqt é um "alvo importado" que o find_package(Qt6) nos dá.
    get_target_property(WINDEPLOYQT_EXECUTABLE Qt6::windeployqt LOCATION)

    # Adiciona um comando que roda após a compilação para copiar as dependências.
    add_custom_command(TARGET TrackieStudio POST_BUILD
            # Comando: Executa a ferramenta windeployqt usando o caminho completo que encontramos.
            COMMAND ${WINDEPLOYQT_EXECUTABLE}

            # Argumentos para o windeployqt:
            ARGS
            # Aponta para o nosso executável.
            $<TARGET_FILE:TrackieStudio>

            # Comentário que aparecerá no log de compilação.
            COMMENT "Copiando dependências do Qt com windeployqt..."
    )
endif()