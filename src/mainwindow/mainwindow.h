// src/mainwindow/mainwindow.h
// Definição da classe MainWindow, a janela principal que organiza a aplicação.

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// --- Forward Declarations ---
// Usamos "forward declarations" para informar ao compilador que essas classes
// existem, sem precisar incluir seus cabeçalhos completos aqui. Isso acelera
// a compilação e evita dependências circulares.
class QWidget;
class QHBoxLayout;
class LeftSidebar;
class CentralPanel;
class RightSidebar;

class MainWindow : public QMainWindow
{
    // A macro Q_OBJECT é obrigatória para qualquer classe que defina
    // seus próprios sinais ou slots ou use o sistema de meta-objetos do Qt.
    Q_OBJECT

public:
    // Construtor padrão. 'explicit' previne conversões implícitas indesejadas.
    explicit MainWindow(QWidget *parent = nullptr);

    // Destrutor.
    ~MainWindow();

private:
    // Função auxiliar para criar e configurar todos os elementos da UI.
    // Chamar esta função no construtor mantém o código organizado.
    void setupUI();

    // Função auxiliar para conectar os sinais e slots entre os componentes.
    // Mantém a lógica de comunicação separada da criação da UI.
    void connectSignalsAndSlots();

    // --- Ponteiros para os Componentes da UI ---
    // Estes ponteiros mantêm as instâncias dos nossos três painéis principais.
    // Usamos o prefixo 'm_' como convenção para variáveis membro.

    // O widget central que serve de contêiner para nosso layout principal.
    QWidget *m_centralWidget;

    // O layout principal que organiza os painéis em três colunas.
    QHBoxLayout *m_mainLayout;

    // Ponteiros para os nossos três painéis modulares já implementados.
    LeftSidebar  *m_leftSidebar;
    CentralPanel *m_centralPanel;
    RightSidebar *m_rightSidebar;
};

#endif // MAINWINDOW_H