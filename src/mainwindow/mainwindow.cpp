// src/mainwindow/mainwindow.cpp
// Implementação final da classe MainWindow, que monta e conecta todos os componentes.

#include "mainwindow.h"

// 1. Includes para os componentes modulares.
#include "components/leftsidebar/leftsidebar.h"
#include "components/centralpanel/centralpanel.h"
#include "components/rightsidebar/rightsidebar.h"

// Includes essenciais do Qt para o layout.
#include <QHBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_centralWidget(nullptr)
    , m_mainLayout(nullptr)
    , m_leftSidebar(nullptr)
    , m_centralPanel(nullptr)
    , m_rightSidebar(nullptr)
{
    // O construtor agora chama as duas funções auxiliares na ordem correta.
    // Primeiro cria a UI, depois conecta os sinais.
    setupUI();
    connectSignalsAndSlots();
}

MainWindow::~MainWindow()
{
    // O sistema de parentesco do Qt cuida da liberação da memória dos widgets filhos.
}

void MainWindow::setupUI()
{
    // --- 1. Configurações da Janela Principal ---
    setWindowTitle("Trackie Studio"); // Nome atualizado do projeto
    resize(1280, 720);

    // --- 2. Criação do Widget Central e do Layout Principal ---
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);

    m_mainLayout = new QHBoxLayout(m_centralWidget);
    m_mainLayout->setSpacing(0);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);

    // --- 3. Instanciação dos Componentes Reais ---
    // Criamos diretamente nossos componentes modulares.
    m_leftSidebar = new LeftSidebar(this);
    m_centralPanel = new CentralPanel(this);
    m_rightSidebar = new RightSidebar(this);

    // --- 4. Adição dos Componentes ao Layout ---
    // Adicionamos os três componentes ao layout na ordem correta.
    m_mainLayout->addWidget(m_leftSidebar);
    m_mainLayout->addWidget(m_centralPanel);
    m_mainLayout->addWidget(m_rightSidebar);
}

void MainWindow::connectSignalsAndSlots()
{
    // --- Conexão dos Sinais e Slots ---
    // Esta função centraliza toda a lógica de comunicação entre os componentes.
    // A MainWindow atua como a "central telefônica" que conecta os sinais
    // emitidos por um componente (RightSidebar) aos slots de outro (CentralPanel).

    // Conecta a mudança de modelo no RightSidebar ao slot correspondente no CentralPanel.
    connect(m_rightSidebar, &RightSidebar::modelChanged,
            m_centralPanel, &CentralPanel::updateForModel);

    // Conecta a mudança de modo no RightSidebar ao slot correspondente no CentralPanel.
    connect(m_rightSidebar, &RightSidebar::modeChanged,
            m_centralPanel, &CentralPanel::updateForMode);

    // COMENTÁRIO PARA O FUTURO:
    // Aqui é onde conectaríamos os sinais do LeftSidebar. Por exemplo, para
    // notificar o CentralPanel quando o módulo Spotway for ativado,
    // permitindo que ele habilite o botão "Night Vision".
    /*
    connect(m_leftSidebar, &LeftSidebar::spotwayModuleClicked,
            m_centralPanel, &CentralPanel::setSpotwayActive); // setSpotwayActive seria um novo slot
    */
}