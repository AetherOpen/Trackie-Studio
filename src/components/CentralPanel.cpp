// src/components/CentralPanel.cpp

#include "components/CentralPanel.h"
#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>

CentralPanel::CentralPanel(QWidget *parent)
    : QFrame(parent),
      m_currentModel("TrackieLLM"),      // Estado inicial padrão
      m_currentMode("Audio only"),       // Estado inicial padrão
      m_spotwayActive(false)             // Estado inicial padrão
{
    setupUi();
    updateButtonStates(); // Aplica o estado inicial aos botões na criação.
}

void CentralPanel::setupUi()
{
    // O layout principal deste widget (CentralPanel).
    // Seu único propósito é centralizar o 'contentPanel'.
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // O 'contentPanel' é o painel cinza escuro que contém todos os botões.
    contentPanel = new QFrame(this);
    contentPanel->setObjectName("contentPanel"); // Para estilização via QSS
    contentPanel->setMaximumWidth(600); // Limita a largura para não ficar muito grande

    panelLayout = new QVBoxLayout(contentPanel);
    panelLayout->setContentsMargins(20, 20, 20, 20);
    panelLayout->setSpacing(10);

    // --- Criação dos Widgets ---
    // 1. Dropdown CoreModel
    coreModelDropdown = new QComboBox(contentPanel);
    // As opções serão preenchidas dinamicamente em updateButtonStates

    // 2. Botões
    searchButton = new QPushButton("Pesquisar na Internet", contentPanel);
    objectViewerButton = new QPushButton("Object Viewer", contentPanel);
    distancePreviewButton = new QPushButton("Distance Preview", contentPanel);
    cameraFeedButton = new QPushButton("Camera Feed", contentPanel);
    segmentationFilterButton = new QPushButton("Segmentation Filter", contentPanel);
    navigationModeButton = new QPushButton("Navigation Mode", contentPanel);
    silentModeButton = new QPushButton("Silent Mode", contentPanel);
    nightVisionButton = new QPushButton("Night Vision", contentPanel);

    // --- Adição dos Widgets ao Layout do Painel ---
    panelLayout->addWidget(new QLabel("CoreModel", contentPanel));
    panelLayout->addWidget(coreModelDropdown);
    panelLayout->addSpacing(20); // Espaço entre seções
    panelLayout->addWidget(searchButton);
    panelLayout->addWidget(objectViewerButton);
    panelLayout->addWidget(distancePreviewButton);
    panelLayout->addWidget(cameraFeedButton);
    panelLayout->addWidget(segmentationFilterButton);
    panelLayout->addWidget(navigationModeButton);
    panelLayout->addWidget(silentModeButton);
    panelLayout->addWidget(nightVisionButton);
    panelLayout->addStretch(1); // Empurra tudo para cima

    // Adiciona o painel de conteúdo ao layout principal, alinhando-o ao centro.
    mainLayout->addWidget(contentPanel, 0, Qt::AlignHCenter | Qt::AlignVCenter);
}

// --- SLOTS ---

void CentralPanel::onModelChanged(const QString& modelName)
{
    m_currentModel = modelName;
    updateButtonStates();
}

void CentralPanel::onModeChanged(const QString& modeName)
{
    m_currentMode = modeName;
    updateButtonStates();
}

void CentralPanel::onSpotwayStatusChanged(bool isActive)
{
    m_spotwayActive = isActive;
    updateButtonStates();
}

// --- LÓGICA PRINCIPAL ---

void CentralPanel::updateButtonStates()
{
    // Lógica para o Dropdown de Modelos
    coreModelDropdown->clear();
    if (m_currentModel == "TrackieLLM") {
        coreModelDropdown->addItem("Gemma1bTRCK");
    } else if (m_currentModel == "TrackieIntelligence") {
        coreModelDropdown->addItem("gemini-2.5 (flash preview native audio dialog)");
        coreModelDropdown->addItem("gemini-2.0 (flash live)");
        coreModelDropdown->addItem("gemini-2.5 (flash live preview)");
    }

    // Lógica para habilitar/desabilitar botões
    searchButton->setEnabled(m_currentModel == "TrackieIntelligence");

    // Para os modos, é mais robusto verificar se a string contém "Camera".
    bool isCameraMode = m_currentMode.contains("Camera");
    objectViewerButton->setEnabled(isCameraMode);
    distancePreviewButton->setEnabled(isCameraMode);
    cameraFeedButton->setEnabled(isCameraMode);
    segmentationFilterButton->setEnabled(isCameraMode);
    navigationModeButton->setEnabled(isCameraMode);

    silentModeButton->setEnabled(true); // Sempre habilitado

    nightVisionButton->setEnabled(m_spotwayActive);
}