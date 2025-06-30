// src/components/leftsidebar/leftsidebar.h
// Definição da classe LeftSidebar, o painel de navegação esquerdo.

#ifndef LEFTSIDEBAR_H
#define LEFTSIDEBAR_H

#include <QFrame>

// Forward declarations para os widgets que usaremos como ponteiros membro.
class QPushButton;
class QVBoxLayout;
class QWidget;

class LeftSidebar : public QFrame
{
    // Macro Q_OBJECT é essencial para usar sinais e slots.
    Q_OBJECT

public:
    // Construtor. 'explicit' é uma boa prática em C++.
    explicit LeftSidebar(QWidget *parent = nullptr);
    ~LeftSidebar();

    signals:
        // Sinais são a forma como este componente se comunicará com o resto da aplicação
        // (especificamente com a MainWindow). Eles notificam que algo aconteceu.
        void trackieModuleClicked();
    void spotwayModuleClicked();

private slots:
    // Slots são funções que podem ser conectadas a sinais (ex: clique de um botão).
    // Este slot irá gerenciar a lógica de colapsar e expandir a barra lateral.
    void handleCollapseToggle();

private:
    // Função auxiliar para criar e organizar os elementos visuais.
    void setupUi();

    // Função para atualizar a aparência da barra com base no estado (colapsado/expandido).
    void updateUiForState();

    // --- Constantes de Largura ---
    // Definir as larguras como constantes torna o código mais legível e fácil de manter.
    static const int EXPANDED_WIDTH = 200;
    static const int COLLAPSED_WIDTH = 50; // 50px é mais prático para ícones do que 20px.

    // --- Membros de Estado ---
    bool m_isCollapsed;

    // --- Ponteiros para os Widgets da UI ---
    // Mantemos ponteiros para os widgets que precisamos manipular ou referenciar.
    QVBoxLayout *m_mainLayout;
    QPushButton *m_trackieButton;
    QPushButton *m_spotwayButton;
    QPushButton *m_collapseButton;
    QWidget     *m_bottomToolbar; // Placeholder para a barra de ferramentas inferior.
};

#endif // LEFTSIDEBAR_H