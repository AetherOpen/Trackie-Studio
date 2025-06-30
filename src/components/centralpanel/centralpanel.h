// src/components/centralpanel/centralpanel.h
// Definição da classe CentralPanel, a área de interação principal.

#ifndef CENTRALPANEL_H
#define CENTRALPANEL_H

#include <QFrame>
#include <QString>

// Forward declarations
class QVBoxLayout;
class QPushButton;
class QComboBox;

class CentralPanel : public QFrame
{
    Q_OBJECT

public:
    explicit CentralPanel(QWidget *parent = nullptr);
    ~CentralPanel();

public slots:
    // --- Slots Públicos para Atualização de Estado ---
    // Estes são os slots que a MainWindow conectará aos sinais do RightSidebar.
    // Quando o modelo ou modo mudar, estas funções serão chamadas.
    void updateForModel(const QString &modelName);
    void updateForMode(const QString &modeName);

private:
    // Função auxiliar para criar a UI.
    void setupUi();

    // Função central de lógica: atualiza a visibilidade e o estado dos botões.
    void updateButtonStates();

    // --- Variáveis de Estado Interno ---
    // O painel mantém sua própria cópia do estado atual da aplicação.
    QString m_currentModel;
    QString m_currentMode;
    bool m_isSpotwayActive; // Futuramente, este estado virá do LeftSidebar.

    // --- Ponteiros para os Widgets da UI ---
    QVBoxLayout *m_mainLayout;
    QFrame      *m_innerPanel; // O painel cinza escuro que contém os botões.

    // Ponteiros para todos os botões e controles possíveis.
    QComboBox   *m_coreModelDropdown;
    QPushButton *m_searchInternetButton;
    QPushButton *m_objectViewerButton;
    QPushButton *m_distancePreviewButton;
    QPushButton *m_cameraFeedButton;
    QPushButton *m_segmentationFilterButton;
    QPushButton *m_navigationModeButton;
    QPushButton *m_silentModeButton;
    QPushButton *m_nightVisionButton;
};

#endif // CENTRALPANEL_H