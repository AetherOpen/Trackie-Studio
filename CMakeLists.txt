# CMakeLists.txt para o projeto TrackieStudio

# 1. Definição Mínima do CMake e Nome do Projeto
# --------------------------------------------------
# Define a versão mínima do CMake necessária. 3.16 é um bom padrão para Qt6.
cmake_minimum_required(VERSION 3.16)

# Define o nome do projeto, versão e linguagem.
project(TrackieStudio VERSION 1.0 LANGUAGES CXX)


# 2. Encontrar o Pacote Qt6
# --------------------------------------------------
# Procura pela instalação do Qt6 no sistema.
# O comando falhará se o Qt6 não for encontrado.
# COMPONENTS especifica quais módulos do Qt nós precisamos (Core, Gui, Widgets).
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)


# 3. Configuração da Integração com Qt
# --------------------------------------------------
# Define o padrão da linguagem C++ para C++17, conforme nosso .pro anterior.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Habilita funcionalidades automáticas do CMake para o Qt, que são essenciais:
# CMAKE_AUTOMOC: Executa o Meta-Object Compiler (para Q_OBJECT, sinais/slots).
# CMAKE_AUTORCC: Executa o Resource Compiler (para arquivos .qrc).
# CMAKE_AUTOUIC: Executa o UI Compiler (para arquivos .ui, se usarmos no futuro).
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


# 4. Coleta dos Arquivos-Fonte do Projeto
# --------------------------------------------------
# Criamos uma lista com todos os nossos arquivos .cpp e .h.
# Isso mantém a seção de criação do executável mais limpa.
set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow/mainwindow.cpp
        src/components/leftsidebar/leftsidebar.cpp
        src/components/rightsidebar/rightsidebar.cpp
        src/components/centralpanel/centralpanel.cpp
        src/components/loadingscreen/loadingscreen.cpp
)

set(PROJECT_HEADERS
        src/mainwindow/mainwindow.h
        src/components/leftsidebar/leftsidebar.h
        src/components/rightsidebar/rightsidebar.h
        src/components/centralpanel/centralpanel.h
        src/components/loadingscreen/loadingscreen.h
)

# Adiciona nosso arquivo de recursos. CMAKE_AUTORCC cuidará dele.
set(PROJECT_RESOURCES
        resources/resources.qrc
)


# 5. Criação do Executável
# --------------------------------------------------
# Cria o alvo do executável chamado "TrackieStudio".
# Incluímos todos os arquivos para que eles apareçam corretamente em IDEs.
add_executable(TrackieStudio
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        ${PROJECT_RESOURCES}
)


# 6. Vinculação e Diretórios de Inclusão
# --------------------------------------------------
# Vincula (linka) nosso executável com os módulos do Qt que encontramos.
# Usamos 'PRIVATE' porque essas dependências são internas ao nosso executável.
target_link_libraries(TrackieStudio PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

# Adiciona o diretório 'src' aos caminhos de busca de includes para o nosso alvo.
# Esta é a linha que corrige o erro de compilação "No such file or directory".
target_include_directories(TrackieStudio PRIVATE src)


# 7. LÓGICA DE DEPLOYMENT PARA WINDOWS (RESOLVE O PROBLEMA DAS DLLS)
# --------------------------------------------------------------------
# Esta seção só será executada se o sistema operacional for Windows.
if(WIN32)
    # Define o diretório de saída para o executável.
    # Todos os executáveis serão colocados em uma pasta "bin" dentro do diretório de build.
    set_target_properties(TrackieStudio PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )

    # Pega o caminho para a ferramenta 'windeployqt' fornecida pelo Qt.
    get_target_property(WINDEPLOYQT_PATH Qt6::windeployqt LOCATION)

    # Adiciona um comando customizado que será executado APÓS a compilação do nosso alvo.
    # Este comando executa o 'windeployqt' para copiar TODAS as DLLs necessárias
    # (incluindo plugins de plataforma como qwindows.dll) para a pasta do nosso executável.
    add_custom_command(TARGET TrackieStudio POST_BUILD
            COMMAND ${WINDEPLOYQT_PATH}
            ARGS
            --dir ${CMAKE_BINARY_DIR}/bin
            --plugindir plugins
            $<TARGET_FILE:TrackieStudio>
            COMMENT "Executando windeployqt para copiar as dependências do Qt..."
    )
endif()