    // src/components/centralpanel/centralpanel.cpp
// Implementação da classe CentralPanel.

#include "centralpanel.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QFrame>
#include <QLabel>

CentralPanel::CentralPanel(QWidget *parent)
    : QFrame(parent),
      m_currentModel("TrackieLLM"), // Estado inicial padrão
      m_currentMode("Audio only"),    // Estado inicial padrão
      m_isSpotwayActive(false)
{
    // Define o objectName para aplicar o fundo branco da área central via QSS.
    setObjectName("CentralPanel");

    setupUi();
    updateButtonStates(); // Chama a lógica uma vez para definir o estado inicial da UI.
}

CentralPanel::~CentralPanel() {}

void CentralPanel::setupUi()
{
    // Layout principal para centralizar o painel interno.
    // Usamos um truque com stretch para manter o painel centralizado verticalmente.
    auto *outerLayout = new QVBoxLayout(this);
    outerLayout->addStretch();

    // 1. Painel Interno (o contêiner cinza escuro)
    m_innerPanel = new QFrame(this);
    m_innerPanel->setObjectName("InnerPanel"); // Para estilização (fundo #222, borda, etc.)
    m_innerPanel->setFixedWidth(500); // Largura fixa para o painel de botões.

    outerLayout->addWidget(m_innerPanel, 0, Qt::AlignHCenter); // Centraliza horizontalmente
    outerLayout->addStretch();

    // 2. Layout do Painel Interno
    m_mainLayout = new QVBoxLayout(m_innerPanel);
    m_mainLayout->setContentsMargins(20, 20, 20, 20);
    m_mainLayout->setSpacing(10);

    // 3. Criação de TODOS os botões e controles.
    // Eles serão apenas mostrados ou escondidos, não criados/destruídos.

    m_coreModelDropdown = new QComboBox(this);
    m_coreModelDropdown->setObjectName("CoreModelDropdown");
    // As opções serão preenchidas dinamicamente em updateButtonStates()

    m_searchInternetButton = new QPushButton("Pesquisar na Internet", this);
    m_objectViewerButton = new QPushButton("Object Viewer", this);
    m_distancePreviewButton = new QPushButton("Distance Preview", this);
    m_cameraFeedButton = new QPushButton("Camera Feed", this);
    m_segmentationFilterButton = new QPushButton("Segmentation Filter", this);
    m_navigationModeButton = new QPushButton("Navigation Mode", this);
    m_silentModeButton = new QPushButton("Silent Mode", this);
    m_nightVisionButton = new QPushButton("Night Vision", this);

    // Adiciona todos os widgets ao layout do painel interno.
    m_mainLayout->addWidget(m_coreModelDropdown);
    m_mainLayout->addWidget(m_searchInternetButton);
    m_mainLayout->addWidget(m_objectViewerButton);
    m_mainLayout->addWidget(m_distancePreviewButton);
    m_mainLayout->addWidget(m_cameraFeedButton);
    m_mainLayout->addWidget(m_segmentationFilterButton);
    m_mainLayout->addWidget(m_navigationModeButton);
    m_mainLayout->addWidget(m_silentModeButton);
    m_mainLayout->addWidget(m_nightVisionButton);
}

// --- Implementação dos Slots Públicos ---

void CentralPanel::updateForModel(const QString &modelName)
{
    m_currentModel = modelName;
    updateButtonStates(); // Atualiza a UI com base no novo modelo.
}

void CentralPanel::updateForMode(const QString &modeName)
{
    m_currentMode = modeName;
    updateButtonStates(); // Atualiza a UI com base no novo modo.
}

// --- O Cérebro do Painel ---

void CentralPanel::updateButtonStates()
{
    // Lógica para o Dropdown de CoreModel
    m_coreModelDropdown->clear(); // Limpa opções antigas
    if (m_currentModel == "TrackieLLM") {
        m_coreModelDropdown->addItem("Gemma1bTRCK");
    } else if (m_currentModel == "TrackieIntelligence") {
        m_coreModelDropdown->addItem("gemini-2.5 (flash preview native audio dialog)");
        m_coreModelDropdown->addItem("gemini-2.0 (flash live)");
        m_coreModelDropdown->addItem("gemini-2.5 (flash live preview)");
    }

    // Lógica para habilitar/desabilitar botões
    bool isIntelligenceModel = (m_currentModel == "TrackieIntelligence");
    bool isCameraMode = (m_currentMode == "Audio and Camera" || m_currentMode == "Camera only");

    m_searchInternetButton->setEnabled(isIntelligenceModel);

    m_objectViewerButton->setEnabled(isCameraMode);
    m_distancePreviewButton->setEnabled(isCameraMode);
    m_cameraFeedButton->setEnabled(isCameraMode);
    m_segmentationFilterButton->setEnabled(isCameraMode);
    m_navigationModeButton->setEnabled(isCameraMode);

    m_silentModeButton->setEnabled(true); // Sempre habilitado

    // COMENTÁRIO: A lógica do Spotway será conectada no futuro.
    // Por enquanto, ele fica sempre desabilitado.
    m_nightVisionButton->setEnabled(m_isSpotwayActive);
}