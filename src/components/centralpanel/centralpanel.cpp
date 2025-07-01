// src/components/centralpanel/centralpanel.cpp
// Implementação do CentralPanel com a barra de ferramentas de hitbox circular.

#include "centralpanel.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QIcon>
#include <QGraphicsDropShadowEffect>

CentralPanel::CentralPanel(QWidget *parent)
    : QFrame(parent),
      m_currentModel("TrackieLLM"),
      m_currentMode("Audio & camera")
{
    setObjectName("CentralPanel");
    setStyleSheet("background: transparent;");
    setupUi();
    updateButtonStates();
}

CentralPanel::~CentralPanel() {}

// Função helper para criar os botões de ícone.
QPushButton* CentralPanel::createToolButton(const QString &iconPath, const QString &toolTip)
{
    QPushButton *button = new QPushButton(this);
    button->setIcon(QIcon(iconPath));
    button->setIconSize(QSize(22, 22));
    button->setFixedSize(40, 40); // Define a área de clique quadrada. O QSS a tornará circular.
    button->setObjectName("CentralToolButton");
    button->setToolTip(toolTip);
    button->setCheckable(true); // Permite que o botão seja "ligado/desligado".

    // MUDANÇA-CHAVE: Remove toda a borda e fundo padrão do botão.
    // Isso o transforma em uma "hitbox" invisível que só aparece com o QSS.
    button->setFlat(true);
    button->setAttribute(Qt::WA_Hover, true);
    button->setMouseTracking(true);

    return button;
}

void CentralPanel::setupUi()
{
    auto *outerLayout = new QVBoxLayout(this);
    outerLayout->addStretch();

    m_toolbarContainer = new QFrame(this);
    m_toolbarContainer->setObjectName("ToolbarContainer");
    m_toolbarContainer->setFixedHeight(56);

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(25);
    shadow->setColor(QColor(0, 0, 0, 80));
    shadow->setOffset(0, 5);
    m_toolbarContainer->setGraphicsEffect(shadow);

    outerLayout->addWidget(m_toolbarContainer, 0, Qt::AlignHCenter);
    outerLayout->addStretch();

    m_toolbarLayout = new QHBoxLayout(m_toolbarContainer);
    m_toolbarLayout->setContentsMargins(15, 0, 15, 0);
    m_toolbarLayout->setSpacing(8);
    m_toolbarContainer->setAttribute(Qt::WA_Hover, true);
    m_toolbarContainer->setMouseTracking(true);

    m_searchInternetButton = createToolButton(":/icons/box/box-ico1.png", "Pesquisar na Internet");
    m_cameraFeedButton = createToolButton(":/icons/box/box-ico2.png", "Camera Feed");
    m_objectViewerButton = createToolButton(":/icons/box/box-ico3.png", "Object Viewer");
    m_faceViewerButton = createToolButton(":/icons/box/box-ico4.png", "Face Viewer");
    m_distancePreviewButton = createToolButton(":/icons/box/box-ico5.png", "Distance Preview");
    m_segmentationFilterButton = createToolButton(":/icons/box/box-ico6.png", "Segmentation Filter");
    m_navigationModeButton = createToolButton(":/icons/box/box-ico7.png", "Navigation Mode");
    m_silentModeButton = createToolButton(":/icons/box/box-ico8.png", "Silent Mode");
    m_nightVisionButton = createToolButton(":/icons/box/box-ico9.png", "Night Vision");

    m_launchButton = createToolButton(":/icons/box/box-ico.png", "Lançar");
    m_launchButton->setObjectName("LaunchButton");
    m_launchButton->setCheckable(false);

    m_toolbarLayout->addWidget(m_searchInternetButton);
    m_toolbarLayout->addWidget(m_cameraFeedButton);
    m_toolbarLayout->addWidget(m_objectViewerButton);
    m_toolbarLayout->addWidget(m_faceViewerButton);
    m_toolbarLayout->addWidget(m_distancePreviewButton);
    m_toolbarLayout->addWidget(m_segmentationFilterButton);
    m_toolbarLayout->addWidget(m_navigationModeButton);
    m_toolbarLayout->addWidget(m_silentModeButton);
    m_toolbarLayout->addWidget(m_nightVisionButton);
    m_toolbarLayout->addStretch();
    m_toolbarLayout->addWidget(m_launchButton);
}

void CentralPanel::updateForModel(const QString &modelName)
{
    m_currentModel = modelName;
    updateButtonStates();
}

void CentralPanel::updateForMode(const QString &modeName)
{
    m_currentMode = modeName;
    updateButtonStates();
}

void CentralPanel::updateButtonStates()
{
    bool isIntelligenceModel = (m_currentModel == "TrackieIntelligence");
    bool isCameraMode = (m_currentMode == "Audio & camera" || m_currentMode == "Camera");

    m_searchInternetButton->setEnabled(isIntelligenceModel);
    m_cameraFeedButton->setEnabled(isCameraMode);
    m_objectViewerButton->setEnabled(isCameraMode);
    m_faceViewerButton->setEnabled(isCameraMode);
    m_distancePreviewButton->setEnabled(isCameraMode);
    m_segmentationFilterButton->setEnabled(isCameraMode);
    m_navigationModeButton->setEnabled(isCameraMode);
    m_silentModeButton->setEnabled(true);
    m_nightVisionButton->setEnabled(false);
}