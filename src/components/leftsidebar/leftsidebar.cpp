// src/components/leftsidebar/leftsidebar.cpp
// Implementação da classe LeftSidebar.

#include "leftsidebar.h"

// Includes para os widgets e layouts do Qt.
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIcon>

LeftSidebar::LeftSidebar(QWidget *parent)
    : QFrame(parent),
      m_isCollapsed(false) // A barra começa expandida.
{
    // Define o objectName para que o QSS do tema escuro seja aplicado corretamente.
    setObjectName("LeftSidebar");

    // Chama a função auxiliar para criar a interface do usuário.
    setupUi();
}

LeftSidebar::~LeftSidebar()
{
    // A memória é gerenciada pelo sistema de parentesco do Qt.
}

void LeftSidebar::setupUi()
{
    // 1. Layout Principal
    // Um QVBoxLayout organiza os widgets verticalmente.
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(10, 20, 10, 10); // Margens: esq, topo, dir, baixo
    m_mainLayout->setSpacing(10);

    // 2. Botão de Colapso/Expansão
    m_collapseButton = new QPushButton("◄"); // Ícone de seta temporário
    m_collapseButton->setObjectName("CollapseButton"); // Para estilo específico
    m_collapseButton->setFixedSize(30, 30);
    // Conecta o clique do botão ao nosso slot privado que gerencia o estado.
    connect(m_collapseButton, &QPushButton::clicked, this, &LeftSidebar::handleCollapseToggle);

    // 3. Botões de Módulo
    m_trackieButton = new QPushButton("Trackie");
    m_trackieButton->setObjectName("ModuleButton"); // Nome de objeto para estilo
    m_trackieButton->setMinimumHeight(40);
    // Conecta o clique do botão diretamente à emissão do nosso sinal público.
    connect(m_trackieButton, &QPushButton::clicked, this, &LeftSidebar::trackieModuleClicked);

    m_spotwayButton = new QPushButton("Spotway");
    m_spotwayButton->setObjectName("ModuleButton");
    m_spotwayButton->setMinimumHeight(40);
    connect(m_spotwayButton, &QPushButton::clicked, this, &LeftSidebar::spotwayModuleClicked);

    // 4. Barra de Ferramentas Inferior (Placeholder)
    m_bottomToolbar = new QWidget(this);
    m_bottomToolbar->setFixedHeight(40);
    m_bottomToolbar->setObjectName("BottomToolbar"); // Para estilizar com fundo branco
    QHBoxLayout* toolbarLayout = new QHBoxLayout(m_bottomToolbar);
    toolbarLayout->setContentsMargins(5, 5, 5, 5);
    toolbarLayout->setSpacing(5);
    // Adicionando placeholders para os ícones
    toolbarLayout->addWidget(new QPushButton("G")); // Globo
    toolbarLayout->addWidget(new QPushButton("T")); // Telefone
    toolbarLayout->addWidget(new QPushButton("N")); // Nuvem
    toolbarLayout->addStretch(); // Empurra os próximos para a direita

    // 5. Montagem do Layout
    m_mainLayout->addWidget(m_collapseButton, 0, Qt::AlignRight); // Alinha o botão à direita
    m_mainLayout->addWidget(m_trackieButton);
    m_mainLayout->addWidget(m_spotwayButton);
    m_mainLayout->addStretch(); // Espaçador que empurra o que vem depois para baixo
    m_mainLayout->addWidget(m_bottomToolbar);

    // 6. Define o estado inicial da UI
    updateUiForState();
}

void LeftSidebar::handleCollapseToggle()
{
    // Inverte o estado booleano
    m_isCollapsed = !m_isCollapsed;
    // Chama a função que atualiza a aparência com base no novo estado
    updateUiForState();
}

void LeftSidebar::updateUiForState()
{
    if (m_isCollapsed) {
        // --- Estado Colapsado ---
        setFixedWidth(COLLAPSED_WIDTH);
        m_collapseButton->setText("►");
        m_trackieButton->setText(""); // Esconde o texto, deixando espaço para o ícone
        m_spotwayButton->setText("");
        m_bottomToolbar->setVisible(false); // Esconde a barra de ferramentas
    } else {
        // --- Estado Expandido ---
        setFixedWidth(EXPANDED_WIDTH);
        m_collapseButton->setText("◄");
        m_trackieButton->setText("Trackie");
        m_spotwayButton->setText("Spotway");
        m_bottomToolbar->setVisible(true); // Mostra a barra de ferramentas
    }
}