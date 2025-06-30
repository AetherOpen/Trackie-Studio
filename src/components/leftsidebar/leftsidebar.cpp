// src/mainwindow/mainwindow.cpp

// ... (outros includes)
// Substitua o comentário pelo include real:
#include "components/leftsidebar/leftsidebar.h"

// ... (no construtor)

void MainWindow::setupUI()
{
    // ... (código de configuração da janela)

    // 3. Criação dos Componentes
    // O placeholder do LeftSidebar será substituído.

    // --- Instancia o LeftSidebar REAL ---
    m_leftSidebar = new LeftSidebar(this); // <-- NOVA LINHA

    // --- Placeholder para o CentralPanel (continua o mesmo por enquanto) ---
    QFrame *centralPlaceholder = new QFrame(this);
    centralPlaceholder->setObjectName("CentralPanel");

    // --- Placeholder para o RightSidebar (continua o mesmo por enquanto) ---
    QFrame *rightPlaceholder = new QFrame(this);
    rightPlaceholder->setObjectName("RightSidebar");
    rightPlaceholder->setFixedWidth(200);

    // 4. Adiciona os componentes ao layout principal
    m_mainLayout->addWidget(m_leftSidebar); // <-- MUDANÇA AQUI
    m_mainLayout->addWidget(centralPlaceholder);
    m_mainLayout->addWidget(rightPlaceholder);

    // O código antigo que criava 'leftPlaceholder' deve ser REMOVIDO.
}