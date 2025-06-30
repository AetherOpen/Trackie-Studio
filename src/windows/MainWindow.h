// src/windows/MainWindow.h

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// --- Forward Declarations ---
// Em vez de incluir os cabeçalhos completos de nossos widgets aqui,
// usamos "forward declarations". Isso informa ao compilador que essas
// classes existem, sem precisar de todos os seus detalhes.
// Vantagens:
// 1. Reduz o tempo de compilação.
// 2. Evita problemas de "dependência circular" (#include A em B, e #include B em A).
// Os includes completos serão feitos no arquivo .cpp, onde realmente usamos os objetos.
class LeftSidebar;
class CentralPanel;
class RightSidebar;
class QHBoxLayout; // Layout horizontal para organizar nossas 3 colunas.

// MainWindow herda de QMainWindow, a classe base do Qt para janelas principais.
class MainWindow : public QMainWindow
{
    // Q_OBJECT é um macro obrigatório para qualquer classe que use o sistema de
    // Sinais e Slots do Qt, um mecanismo fundamental para a comunicação entre objetos.
    Q_OBJECT

public:
    // Construtor padrão do Qt. 'explicit' previne conversões implícitas.
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow(); // Destrutor

private:
    // --- Funções de Configuração Interna ---
    // Manter a configuração da UI em uma função separada deixa o construtor mais limpo.
    void setupUi();
    // Esta função será usada para conectar os sinais e slots entre os painéis.
    void setupConnections();

    // --- Ponteiros para os Componentes da UI ---
    // Precisamos de ponteiros para nossos widgets customizados para podermos
    // criá-los e gerenciá-los na memória.

    // O widget central que conterá o layout principal.
    // Em um QMainWindow, só podemos ter UM widget central.
    // Nosso truque é colocar um layout dentro deste widget.
    QWidget *mainCentralWidget;

    // O layout que organizará os 3 painéis lado a lado.
    QHBoxLayout *mainLayout;

    // Nossos três painéis modulares.
    LeftSidebar  *leftSidebar;
    CentralPanel *centralPanel;
    RightSidebar *rightSidebar;

    // --- COMENTÁRIO PARA INTEGRAÇÃO FUTURA ---
    // A classe AppState será o nosso "cérebro" central, guardando o estado
    // da aplicação (modelo selecionado, modo, etc.). A MainWindow terá um
    // ponteiro para ele e o passará para os painéis que precisarem.
    // AppState *appState; // Descomentar quando a classe AppState for criada.
};

#endif // MAINWINDOW_H