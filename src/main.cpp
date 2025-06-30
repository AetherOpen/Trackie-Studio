// src/main.cpp
// Ponto de entrada principal da aplicação TrackieStudio.

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QEventLoop>
#include <QDebug> // Incluído para a mensagem de aviso (qWarning)

// Inclui os cabeçalhos dos nossos dois componentes principais de alto nível.
#include "mainwindow/mainwindow.h"
#include "components/loadingscreen/loadingscreen.h"

int main(int argc, char *argv[])
{
    // 1. Cria a instância principal da aplicação Qt.
    // QApplication gerencia o loop de eventos e os recursos principais da GUI.
    QApplication app(argc, argv);

    // --- Carregamento do Tema Escuro (Stylesheet) ---
    // Nosso design profissional depende de uma folha de estilos, similar a um CSS.
    // O prefixo ':' indica que o arquivo está compilado dentro do executável
    // através do sistema de recursos do Qt (resources.qrc).
    QFile styleFile(":/styles/dark_theme.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&styleFile);
        QString styleSheet = stream.readAll();
        app.setStyleSheet(styleSheet);
        styleFile.close();
    } else {
        // Se o arquivo de estilo não for encontrado, um aviso será impresso no console.
        qWarning("AVISO: Não foi possível encontrar o arquivo de estilo ':/styles/dark_theme.qss'. A aplicação pode não ter a aparência correta.");
    }
    // --- Fim do Carregamento do Tema ---


    // --- Lógica de Inicialização com a Tela de Carregamento ---

    // 2. Instancia a nossa tela de carregamento customizada.
    LoadingScreen splash;
    splash.show(); // Mostra a tela de carregamento imediatamente.

    // 3. Simula o carregamento de recursos.
    // Usamos um QTimer para manter a aplicação "pausada" na tela de carregamento
    // por um período fixo, sem congelar a interface gráfica.
    QEventLoop loop;
    QTimer::singleShot(3500, &loop, &QEventLoop::quit); // 3.5 segundos de exibição
    loop.exec(); // Bloqueia a execução aqui até o timer disparar o quit().

    // 4. Transição para a Janela Principal.
    splash.close(); // Fecha a tela de carregamento.

    // 5. Cria e exibe a janela principal da aplicação.
    MainWindow w;
    w.show(); // A janela principal só aparece após a tela de carregamento fechar.

    // 6. Inicia o loop de eventos principal da aplicação.
    // A aplicação ficará em execução, respondendo a cliques, teclado, etc.,
    // até que a janela principal seja fechada e a função exec() retorne.
    return app.exec();
}