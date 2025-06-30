# Versão mínima do CMake necessária.
cmake_minimum_required(VERSION 3.16)

# Definição do projeto (nome, versão e linguagem).
project(TrackieStudio VERSION 1.0 LANGUAGES CXX)

# Define o padrão da linguagem para C++17 e exige que seja respeitado.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Habilita o processamento automático de arquivos do Qt:
# CMAKE_AUTOMOC: Roda o Meta-Object Compiler (essencial para Sinais e Slots).
# CMAKE_AUTOUIC: Compila arquivos .ui (Interface de Usuário) para código C++.
# CMAKE_AUTORCC: Compila arquivos .qrc (Recursos como imagens e folhas de estilo).
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Encontra o pacote do Qt6 e seus componentes necessários no sistema.
# Pedir por "Widgets" já inclui automaticamente "Core" e "Gui".
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# --- Gerenciamento Explícito de Arquivos Fonte ---
# Listar os arquivos explicitamente melhora a clareza e o controle sobre o build.
set(PROJECT_SOURCES
        # Ponto de entrada da aplicação
        src/main.cpp

        # Janela Principal
        src/windows/MainWindow.h
        src/windows/MainWindow.cpp

        # Componentes da UI
        src/components/LeftSidebar.h
        src/components/LeftSidebar.cpp
        src/components/CentralPanel.h
        src/components/CentralPanel.cpp
        src/components/RightSidebar.h
        src/components/RightSidebar.cpp

        # Arquivos de Recurso (descomente e adicione seu .qrc se tiver um)
        # "resources/resources.qrc"
)

# --- Definição do Executável ---
# Usa a função `qt_add_executable` que é otimizada para projetos Qt.
# Ela gerencia automaticamente os arquivos de header, fontes e recursos (.qrc).
qt_add_executable(TrackieStudio
        ${PROJECT_SOURCES}
)

# --- Definição de Diretórios de Inclusão ---
# Adiciona o diretório 'src' aos locais onde o compilador procurará por arquivos de cabeçalho (.h).
# Usar 'target_include_directories' é a prática moderna, pois aplica a configuração apenas a este alvo.
target_include_directories(TrackieStudio PRIVATE src)

# --- Vinculação de Bibliotecas (Linking) ---
# Vincula nosso executável com as bibliotecas do Qt que ele utiliza.
target_link_libraries(TrackieStudio PRIVATE Qt6::Widgets)

# --- Automação de Implantação (Cópia de DLLs) ---
# Esta seção só será ativada em compilações para Windows.
if(WIN32)
    # Adiciona um comando que será executado DEPOIS que a compilação do TrackieStudio for concluída.
    add_custom_command(
            TARGET TrackieStudio POST_BUILD
            COMMAND $<TARGET_FILE:Qt6::windeployqt>
            # CORREÇÃO: A flag --mingw foi removida nas versões recentes do Qt.
            # O windeployqt deve detectar o toolchain MinGW automaticamente.
            #
            # Define o diretório de destino para a pasta onde o .exe foi criado.
            --dir "$<TARGET_FILE_DIR:TrackieStudio>"
            # O executável que será analisado para descobrir as dependências.
            "$<TARGET_FILE:TrackieStudio>"
            # Mensagem que aparecerá no console durante a compilação.
            COMMENT "Copiando DLLs necessárias para a pasta de destino..."
    )
endif()

# --- Mensagens de Status (Opcional) ---
# Informa ao desenvolvedor que a configuração foi concluída com sucesso.
message(STATUS "CMake configurado com sucesso para o projeto TrackieStudio.")