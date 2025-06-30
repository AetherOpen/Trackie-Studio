// src/components/rightsidebar/rightsidebar.cpp
// Implementação da classe RightSidebar.

#include "rightsidebar.h"

// Includes para os widgets e layouts do Qt.
#include <QVBoxLayout>
#include <QComboBox>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>
#include <QGroupBox> // Usaremos QGroupBox para agrupar visualmente as seções.

RightSidebar::RightSidebar(QWidget *parent)
    : QFrame(parent)
{
    // Define o objectName para que o estilo da borda esquerda seja aplicado via QSS.
    setObjectName("RightSidebar");

    // Chama a função auxiliar para construir a UI.
    setupUi();
}

RightSidebar::~RightSidebar()
{
    // Memória gerenciada pelo sistema de parentesco do Qt.
}

void RightSidebar::setupUi()
{
    // 1. Layout Principal
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(15, 20, 15, 20);
    m_mainLayout->setSpacing(20); // Espaçamento maior entre as seções.

    // --- 2. Seção de Seleção de Modelo ---
    m_modelLabel = new QLabel("MODELO", this);
    m_modelLabel->setObjectName("SidebarLabel"); // Para estilização (maiúsculo, etc.)

    m_modelSelector = new QComboBox(this);
    m_modelSelector->setObjectName("ConfigSelector");
    m_modelSelector->addItem("TrackieLLM");
    m_modelSelector->addItem("TrackieIntelligence");
    // Conecta a mudança de item ao nosso slot, que emitirá o sinal global.
    connect(m_modelSelector, &QComboBox::textActivated, this, &RightSidebar::onModelSelectionChanged);

    m_mainLayout->addWidget(m_modelLabel);
    m_mainLayout->addWidget(m_modelSelector);

    // --- 3. Seção de Seleção de Modo ---
    m_modeLabel = new QLabel("MODO", this);
    m_modeLabel->setObjectName("SidebarLabel");

    m_modeSelector = new QComboBox(this);
    m_modeSelector->setObjectName("ConfigSelector");
    m_modeSelector->addItem("Audio only");
    m_modeSelector->addItem("Audio and Camera");
    m_modeSelector->addItem("Camera only");
    connect(m_modeSelector, &QComboBox::textActivated, this, &RightSidebar::onModeSelectionChanged);

    m_mainLayout->addWidget(m_modeLabel);
    m_mainLayout->addWidget(m_modeSelector);

    // --- 4. Seção de Sliders (Alavancas) ---
    m_gainLabel = new QLabel("Ganho", this);
    m_gainSlider = new QSlider(Qt::Horizontal, this);

    m_contrastLabel = new QLabel("Contraste", this);
    m_contrastSlider = new QSlider(Qt::Horizontal, this);

    m_mainLayout->addWidget(m_gainLabel);
    m_mainLayout->addWidget(m_gainSlider);
    m_mainLayout->addWidget(m_contrastLabel);
    m_mainLayout->addWidget(m_contrastSlider);

    // --- 5. Seção de Ferramentas (Tools) ---
    m_toolsLabel = new QLabel("TOOLS", this);
    m_toolsLabel->setObjectName("SidebarLabel");

    m_distanceToolToggle = new QCheckBox("Medição de distâncias", this);
    m_objectDetectionToolToggle = new QCheckBox("Detecção avançada de objetos", this);
    m_faceRecognitionToolToggle = new QCheckBox("Reconhecer Rostos", this);

    m_mainLayout->addWidget(m_toolsLabel);
    m_mainLayout->addWidget(m_distanceToolToggle);
    m_mainLayout->addWidget(m_objectDetectionToolToggle);
    m_mainLayout->addWidget(m_faceRecognitionToolToggle);

    // Adiciona um espaçador no final para empurrar todo o conteúdo para o topo.
    m_mainLayout->addStretch();
}

// --- Implementação dos Slots ---

void RightSidebar::onModelSelectionChanged(const QString &text)
{
    // Este slot é ativado pelo QComboBox. Sua única função é reemitir
    // a informação como um sinal público da classe RightSidebar.
    emit modelChanged(text);
}

void RightSidebar::onModeSelectionChanged(const QString &text)
{
    // Mesma lógica do slot acima.
    emit modeChanged(text);
}