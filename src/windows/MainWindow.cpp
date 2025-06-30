// src/windows/MainWindow.cpp

#include "windows/MainWindow.h"

// --- Inclusões dos Componentes ---
// Agora que todos os componentes foram criados, incluímos seus cabeçalhos.
#include "components/LeftSidebar.h"
#include "components/CentralPanel.h"
#include "components/RightSidebar.h"

// Inclusões de classes Qt necessárias para o layout.
#include <QHBoxLayout>
#include <QWidget>

// Construtor da MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) // Chama o construtor da classe base
{
    // Chama nossas funções de configuração para manter o construtor limpo.
    setupUi();
    setupConnections();
}

// Destrutor da MainWindow
MainWindow::~MainWindow()
{
    // O Qt gerencia a memória dos widgets filhos automaticamente.
    // Nenhum código de exclusão manual é necessário aqui.
}

// Função para configurar a interface gráfica.
void MainWindow::setupUi()
{
    // 1. Configurações da Janela Principal
    this->setWindowTitle("Google AI Studio");
    this->resize(1280, 720); // Tamanho inicial

    // 2. Criação do Widget Central e do Layout Principal
    // QMainWindow só pode ter um widget central. Criamos um QWidget genérico
    // para ser este container, e colocamos nosso layout de 3 colunas dentro dele.
    mainCentralWidget = new QWidget(this);
    mainLayout = new QHBoxLayout(mainCentralWidget); // Layout horizontal
    mainLayout->setContentsMargins(0, 0, 0, 0); // Sem margens, os painéis controlam isso
    mainLayout->setSpacing(0);                  // Sem espaçamento, as bordas dos painéis se tocarão

    // --- 3. Instanciação dos Painéis ---
    // Substituímos todos os placeholders QFrame pelas nossas classes de componentes reais.
    leftSidebar = new LeftSidebar(this);
    centralPanel = new CentralPanel(this);
    rightSidebar = new RightSidebar(this);

    // Define as larguras fixas para os sidebars, conforme a especificação.
    leftSidebar->setFixedWidth(200);
    rightSidebar->setFixedWidth(200);

    // Para que o estilo do .qss se aplique corretamente, damos nomes de objeto aos painéis.
    // No .qss, podemos usar seletores de ID como `QWidget#leftSidebarPanel { ... }`
    leftSidebar->setObjectName("leftSidebarPanel");
    centralPanel->setObjectName("centralPanelWidget");
    rightSidebar->setObjectName("rightSidebarPanel");

    // 4. Adiciona os painéis ao layout
    mainLayout->addWidget(leftSidebar);
    mainLayout->addWidget(centralPanel);
    mainLayout->addWidget(rightSidebar);

    // 5. Define a proporção de redimensionamento (stretch factor).
    // O valor '1' para o painel central significa que ele será o único a
    // expandir ou encolher quando a janela for redimensionada. Os outros (com fator 0)
    // manterão seu tamanho (neste caso, a largura fixa que definimos).
    mainLayout->setStretch(0, 0); // Sidebar esquerdo não estica
    mainLayout->setStretch(1, 1); // Painel central estica
    mainLayout->setStretch(2, 0); // Sidebar direito não estica

    // 6. Define o widget central da janela
    this->setCentralWidget(mainCentralWidget);
}

// Função para conectar sinais e slots entre os componentes.
void MainWindow::setupConnections()
{
    // Esta é a cola que torna nossa aplicação interativa.
    // Conectamos os SINAIS emitidos pelo RightSidebar aos SLOTS do CentralPanel.

    // Conexão para a mudança de MODELO:
    // Quando o sinal modelChanged(QString) do rightSidebar é emitido,
    // o slot onModelChanged(QString) do centralPanel é chamado com o mesmo valor.
    connect(rightSidebar, &RightSidebar::modelChanged,
            centralPanel, &CentralPanel::onModelChanged);

    // Conexão para a mudança de MODO:
    // Da mesma forma, conectamos a mudança de modo.
    connect(rightSidebar, &RightSidebar::modeChanged,
            centralPanel, &CentralPanel::onModeChanged);

    // --- COMENTÁRIO PARA INTEGRAÇÃO FUTURA ---
    // Se o botão "Spotway" no LeftSidebar precisasse controlar o botão "Night Vision"
    // no CentralPanel, adicionaríamos um sinal em LeftSidebar e a conexão aqui:
    //
    // Em LeftSidebar.h:
    // signals:
    //     void spotwayStatusChanged(bool isActive);
    //
    // Em LeftSidebar.cpp (no clique do botão):
    //     emit spotwayStatusChanged(true);
    //
    // E a conexão aqui em MainWindow.cpp:
    // connect(leftSidebar, &LeftSidebar::spotwayStatusChanged,
    //         centralPanel, &CentralPanel::onSpotwayStatusChanged);
}