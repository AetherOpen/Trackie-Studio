// src/components/CentralPanel.h

#ifndef CENTRALPANEL_H
#define CENTRALPANEL_H

#include <QFrame> // Usaremos QFrame como base para ter o estilo de painel.
#include <QString>

// Forward declarations
class QVBoxLayout;
class QComboBox;
class QPushButton;
class QFrame;

class CentralPanel : public QFrame
{
    Q_OBJECT

public:
    explicit CentralPanel(QWidget *parent = nullptr);

    // --- SLOTS PÚBLICOS ---
    // Estes são os pontos de entrada para atualizar a UI deste painel.
    // A MainWindow conectará os sinais do RightSidebar a estes slots.
public slots:
    void onModelChanged(const QString& modelName);
    void onModeChanged(const QString& modeName);
    void onSpotwayStatusChanged(bool isActive);

private:
    void setupUi();
    void updateButtonStates(); // Função central para aplicar a lógica de enable/disable.

    // Layouts
    QVBoxLayout *mainLayout;
    QVBoxLayout *panelLayout;

    // O painel interno que terá o fundo escuro e os botões
    QFrame *contentPanel;

    // Widgets
    QComboBox   *coreModelDropdown;
    QPushButton *searchButton;
    QPushButton *objectViewerButton;
    QPushButton *distancePreviewButton;
    QPushButton *cameraFeedButton;
    QPushButton *segmentationFilterButton;
    QPushButton *navigationModeButton;
    QPushButton *silentModeButton;
    QPushButton *nightVisionButton;

    // --- Estado Interno ---
    // O painel armazena o estado atual para tomar decisões.
    QString m_currentModel;
    QString m_currentMode;
    bool    m_spotwayActive;
};

#endif // CENTRALPANEL_H