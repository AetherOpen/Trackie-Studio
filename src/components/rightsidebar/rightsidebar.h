// src/components/rightsidebar/rightsidebar.h
// Definição da classe RightSidebar, o painel de configurações e ferramentas.

#ifndef RIGHTSIDEBAR_H
#define RIGHTSIDEBAR_H

#include <QFrame>

// Forward declarations para os widgets que usaremos.
class QVBoxLayout;
class QComboBox;
class QSlider;
class QLabel;
class QCheckBox; // Usaremos QCheckBox por enquanto, que pode ser estilizado como um toggle.

class RightSidebar : public QFrame
{
    Q_OBJECT

public:
    explicit RightSidebar(QWidget *parent = nullptr);
    ~RightSidebar();

    signals:
        // --- Sinais de Mudança de Estado ---
        // Estes são os sinais mais importantes deste componente. Eles notificarão
        // a MainWindow (e, por consequência, o CentralPanel) sobre as seleções do usuário.
        void modelChanged(const QString &modelName);
    void modeChanged(const QString &modeName);

private slots:
    // Slots para capturar as mudanças nos widgets e emitir os sinais correspondentes.
    void onModelSelectionChanged(const QString &text);
    void onModeSelectionChanged(const QString &text);

private:
    // Função auxiliar para criar e configurar a UI.
    void setupUi();

    // --- Ponteiros para os Widgets da UI ---
    QVBoxLayout *m_mainLayout;

    // Seletor de Modelo
    QLabel      *m_modelLabel;
    QComboBox   *m_modelSelector;

    // Seletor de Modo
    QLabel      *m_modeLabel;
    QComboBox   *m_modeSelector;

    // Sliders (Alavancas)
    QLabel      *m_gainLabel;
    QSlider     *m_gainSlider;
    QLabel      *m_contrastLabel;
    QSlider     *m_contrastSlider;

    // Seção de Ferramentas (Tools)
    QLabel      *m_toolsLabel;
    QCheckBox   *m_distanceToolToggle;
    QCheckBox   *m_objectDetectionToolToggle;
    QCheckBox   *m_faceRecognitionToolToggle;
};

#endif // RIGHTSIDEBAR_H