// src/components/RightSidebar.cpp

#include "components/RightSidebar.h"
#include <QVBoxLayout>
#include <QComboBox>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>

RightSidebar::RightSidebar(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
}

void RightSidebar::setupUi()
{
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 20, 10, 20);
    mainLayout->setSpacing(15);

    // --- Seletores de Modelo e Modo ---
    modelSelector = new QComboBox(this);
    modelSelector->addItem("TrackieLLM");
    modelSelector->addItem("TrackieIntelligence");

    modeSelector = new QComboBox(this);
    modeSelector->addItem("Audio only");
    modeSelector->addItem("Audio and Camera");
    modeSelector->addItem("Camera only");

    // --- Sliders ---
    gainSlider = new QSlider(Qt::Horizontal, this);
    gainSlider->setRange(0, 100);
    gainSlider->setValue(50);
    contrastSlider = new QSlider(Qt::Horizontal, this);
    contrastSlider->setRange(0, 100);
    contrastSlider->setValue(50);

    // --- Seção de Ferramentas ---
    toolsLabel = new QLabel("TOOLS", this);
    toolsLabel->setObjectName("titleLabel"); // Usa o estilo de título do QSS
    toolsLabel->setAlignment(Qt::AlignCenter);

    distanceToolToggle = new QCheckBox("Medição de distâncias", this);
    detectionToolToggle = new QCheckBox("Detecção avançada de objetos", this);
    faceToolToggle = new QCheckBox("Reconhecer Rostos", this);

    // --- Adiciona widgets ao layout ---
    mainLayout->addWidget(new QLabel("Modelo:", this));
    mainLayout->addWidget(modelSelector);
    mainLayout->addWidget(new QLabel("Modo:", this));
    mainLayout->addWidget(modeSelector);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(new QLabel("Ganho:", this));
    mainLayout->addWidget(gainSlider);
    mainLayout->addWidget(new QLabel("Contraste:", this));
    mainLayout->addWidget(contrastSlider);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(toolsLabel);
    mainLayout->addWidget(distanceToolToggle);
    mainLayout->addWidget(detectionToolToggle);
    mainLayout->addWidget(faceToolToggle);
    mainLayout->addStretch(1); // Empurra tudo para cima

    // --- CONEXÕES INTERNAS ---
    // Conecta o sinal de mudança do QComboBox ao nosso slot privado.
    connect(modelSelector, &QComboBox::currentIndexChanged, this, &RightSidebar::onModelSelectionChanged);
    connect(modeSelector,  &QComboBox::currentIndexChanged, this, &RightSidebar::onModeSelectionChanged);
}

// --- Implementação dos Slots Privados ---

void RightSidebar::onModelSelectionChanged(int index)
{
    // Pega o texto do item selecionado.
    QString selectedModel = modelSelector->itemText(index);
    // EMITE o sinal público para que a MainWindow possa ouvi-lo.
    emit modelChanged(selectedModel);
}

void RightSidebar::onModeSelectionChanged(int index)
{
    QString selectedMode = modeSelector->itemText(index);
    // EMITE o sinal público.
    emit modeChanged(selectedMode);
}