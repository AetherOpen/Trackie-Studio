// src/components/centralpanel/centralpanel.h
// Definição do CentralPanel com a barra de ferramentas minimalista.

#ifndef CENTRALPANEL_H
#define CENTRALPANEL_H

#include <QFrame>
#include <QString>

class QHBoxLayout;
class QPushButton;

class CentralPanel : public QFrame
{
    Q_OBJECT

public:
    explicit CentralPanel(QWidget *parent = nullptr);
    ~CentralPanel();

public slots:
    void updateForModel(const QString &modelName);
    void updateForMode(const QString &modeName);

private:
    void setupUi();
    void updateButtonStates();

    // Função helper para criar os botões e evitar repetição de código.
    // ATUALIZAÇÃO: Adicionamos o parâmetro 'toolTip'.
    QPushButton* createToolButton(const QString &iconPath, const QString &toolTip);

    QString m_currentModel;
    QString m_currentMode;

    // Ponteiros para os widgets
    QFrame      *m_toolbarContainer;
    QHBoxLayout *m_toolbarLayout;

    QPushButton *m_searchInternetButton;
    QPushButton *m_cameraFeedButton;
    QPushButton *m_objectViewerButton;
    QPushButton *m_faceViewerButton;
    QPushButton *m_distancePreviewButton;
    QPushButton *m_segmentationFilterButton;
    QPushButton *m_navigationModeButton;
    QPushButton *m_silentModeButton;
    QPushButton *m_nightVisionButton;
    QPushButton *m_launchButton;
};

#endif // CENTRALPANEL_H