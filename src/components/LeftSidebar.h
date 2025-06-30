// src/components/LeftSidebar.h

#ifndef LEFTSIDEBAR_H
#define LEFTSIDEBAR_H

#include <QWidget>

// Forward declarations para os tipos de widgets que usaremos.
// Isso evita a necessidade de incluir os cabeçalhos completos aqui,
// acelerando a compilação.
class QPushButton;
class QVBoxLayout;
class QFrame;

class LeftSidebar : public QWidget
{
    Q_OBJECT

public:
    explicit LeftSidebar(QWidget *parent = nullptr);

private:
    // Função de configuração interna para criar e organizar os widgets.
    void setupUi();

    // Ponteiros para os componentes da UI que este sidebar gerencia.
    QPushButton *trackieButton;
    QPushButton *spotwayButton;
    QPushButton *collapseButton; // Placeholder para o botão de colapso
    QFrame      *bottomToolbar;  // O painel branco na parte inferior

    // Layout principal que organiza os widgets verticalmente.
    QVBoxLayout *mainLayout;

    // --- COMENTÁRIO PARA INTEGRAÇÃO FUTURA ---
    // Adicionaremos SINAIS aqui para comunicar com outras partes da aplicação.
    // Por exemplo, quando o botão "Trackie" for clicado, poderíamos emitir um sinal:
    // signals:
    //     void trackieModuleRequested();
    //     void spotwayModuleRequested();
};

#endif // LEFTSIDEBAR_H