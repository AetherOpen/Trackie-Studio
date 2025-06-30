// src/components/RightSidebar.h

#ifndef RIGHTSIDEBAR_H
#define RIGHTSIDEBAR_H

#include <QWidget>
#include <QString>

// Forward declarations
class QVBoxLayout;
class QComboBox;
class QSlider;
class QLabel;
class QCheckBox; // Usaremos QCheckBox para os toggles de ferramentas

class RightSidebar : public QWidget
{
    Q_OBJECT

public:
    explicit RightSidebar(QWidget *parent = nullptr);




    // --- SINAIS ---
    // Estes são os sinais que este componente emitirá para notificar
    // o resto da aplicação sobre as mudanças de estado.
    signals:
        void modelChanged(const QString& modelName);
    void modeChanged(const QString& modeName);
    // Adicionaremos mais sinais aqui para as ferramentas, se necessário.

private:
    void setupUi();

    // --- SLOTS PRIVADOS ---
    // Estes slots respondem a eventos internos dos widgets deste painel.
    // Quando um QComboBox muda, ele chama um destes slots.
private slots:
    void onModelSelectionChanged(int index);
    void onModeSelectionChanged(int index);

private:
    // Layout
    QVBoxLayout *mainLayout;

    // Widgets
    QComboBox *modelSelector;
    QComboBox *modeSelector;

    QSlider *gainSlider;
    QSlider *contrastSlider;

    QLabel *toolsLabel;
    QCheckBox *distanceToolToggle;
    QCheckBox *detectionToolToggle;
    QCheckBox *faceToolToggle;
};

#endif // RIGHTSIDEBAR_H