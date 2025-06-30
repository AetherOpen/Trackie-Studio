// src/components/rightsidebar/rightsidebar.h
// Definição da classe RightSidebar, o painel de configurações e ferramentas.

#ifndef RIGHTSIDEBAR_H
#define RIGHTSIDEBAR_H

#include <QFrame>
#include "ToggleSwitch.h"

// Forward declarations
class QVBoxLayout;
class QComboBox;
class QLabel;

class RightSidebar : public QFrame
{
    Q_OBJECT

public:
    explicit RightSidebar(QWidget *parent = nullptr);
    ~RightSidebar();

    signals:
        void modelChanged(const QString &modelName);
    void outputFormatChanged(const QString &format);
    void voiceChanged(const QString &voiceName);

private:
    void setupUi();
    QWidget* createToggleRow(const QString &text);

    // --- Ponteiros para os Widgets da UI ---
    QVBoxLayout *m_mainLayout;

    // Seletor de Modelo
    QComboBox   *m_modelSelector;

    // Seletor de Formato de Saída (agora um QComboBox)
    QComboBox   *m_outputFormatSelector; // <-- MUDANÇA AQUI

    // Seletor de Voz
    QComboBox   *m_voiceSelector;

    // Seção de Comportamento
    ToggleSwitch *m_turnCoverageToggle;
    ToggleSwitch *m_affectiveDialogToggle;
    ToggleSwitch *m_proactiveAudioToggle;

    // Seção de Ferramentas
    ToggleSwitch *m_distanceToolToggle;
    ToggleSwitch *m_objectDetectionToolToggle;
    ToggleSwitch *m_faceRecognitionToolToggle;
};

#endif // RIGHTSIDEBAR_H