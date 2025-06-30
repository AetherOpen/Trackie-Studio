// src/components/rightsidebar/rightsidebar.cpp
// Implementação da classe RightSidebar com layout e widgets customizados.

#include "rightsidebar.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QButtonGroup>

RightSidebar::RightSidebar(QWidget *parent) : QFrame(parent)
{
    setObjectName("RightSidebar");
    setFixedWidth(300); // <-- MUDANÇA 1: Define uma largura fixa para a barra lateral.

    setupUi();
}

RightSidebar::~RightSidebar() {}

// A função createToggleRow permanece a mesma...
QWidget* RightSidebar::createToggleRow(const QString &text)
{
    QWidget *row = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(row);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(10);

    QLabel *label = new QLabel(text, row);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    ToggleSwitch *toggle = new ToggleSwitch(row);

    layout->addWidget(label);
    layout->addWidget(toggle);

    if (text == "Turn coverage") m_turnCoverageToggle = toggle;
    else if (text == "Affective dialog") m_affectiveDialogToggle = toggle;
    else if (text == "Proactive audio") m_proactiveAudioToggle = toggle;
    else if (text == "Medição de distâncias") m_distanceToolToggle = toggle;
    else if (text == "Detecção avançada de objetos") m_objectDetectionToolToggle = toggle;
    else if (text == "Reconhecer Rostos") m_faceRecognitionToolToggle = toggle;

    return row;
}


void RightSidebar::setupUi()
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(15, 20, 15, 20);
    m_mainLayout->setSpacing(15);

    QLabel *titleLabel = new QLabel("Run settings", this);
    titleLabel->setObjectName("SidebarTitle");
    m_mainLayout->addWidget(titleLabel);

    m_modelSelector = new QComboBox(this);
    m_modelSelector->setObjectName("ConfigSelector");
    m_modelSelector->addItem("TrackieLLM");
    m_modelSelector->addItem("TrackieIntelligence");
    connect(m_modelSelector, &QComboBox::textActivated, this, &RightSidebar::modelChanged);
    m_mainLayout->addWidget(m_modelSelector);

    // --- MUDANÇA 2: Substituição do seletor de formato de saída ---
    QLabel *outputLabel = new QLabel("Output format", this);
    outputLabel->setObjectName("SidebarLabel");
    m_mainLayout->addWidget(outputLabel);

    // Removemos o QButtonGroup e os QPushButtons e usamos um QComboBox.
    m_outputFormatSelector = new QComboBox(this);
    m_outputFormatSelector->setObjectName("OutputFormatSelector"); // Nome especial para QSS
    m_outputFormatSelector->addItem("Audio & camera");
    m_outputFormatSelector->addItem("Camera");
    m_outputFormatSelector->addItem("Audio");
    // Conectamos o novo seletor ao mesmo sinal de antes.
    connect(m_outputFormatSelector, &QComboBox::textActivated, this, &RightSidebar::outputFormatChanged);
    m_mainLayout->addWidget(m_outputFormatSelector);
    // --- FIM DA MUDANÇA 2 ---

    QLabel *voiceLabel = new QLabel("Voice", this);
    voiceLabel->setObjectName("SidebarLabel");
    m_mainLayout->addWidget(voiceLabel);
    m_voiceSelector = new QComboBox(this);
    m_voiceSelector->setObjectName("ConfigSelector");
    m_voiceSelector->addItem("mainmale");
    m_voiceSelector->addItem("Padrão Feminino");
    m_voiceSelector->addItem("Padrão Masculino");
    connect(m_voiceSelector, &QComboBox::textActivated, this, &RightSidebar::voiceChanged);
    m_mainLayout->addWidget(m_voiceSelector);

    m_mainLayout->addSpacing(20);

    m_mainLayout->addWidget(createToggleRow("Turn coverage"));
    m_mainLayout->addWidget(createToggleRow("Affective dialog"));
    m_mainLayout->addWidget(createToggleRow("Proactive audio"));

    m_mainLayout->addSpacing(20);

    QLabel *toolsLabel = new QLabel("Tools", this);
    toolsLabel->setObjectName("SidebarLabel");
    m_mainLayout->addWidget(toolsLabel);
    m_mainLayout->addWidget(createToggleRow("Medição de distâncias"));
    m_mainLayout->addWidget(createToggleRow("Detecção avançada de objetos"));
    m_mainLayout->addWidget(createToggleRow("Reconhecer Rostos"));

    m_mainLayout->addStretch();
}