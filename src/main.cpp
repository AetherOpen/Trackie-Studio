// src/main.cpp

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>

// Inclui o cabeçalho da nossa futura janela principal.
// Este arquivo ainda não existe, então a compilação falhará até que o criemos.
// Este é o próximo passo em nosso processo modular.
#include "windows/MainWindow.h"

// Função para carregar e aplicar a folha de estilos globalmente.
void loadStyleSheet(QApplication& app) {
    // O caminho ":/styles/dark_theme.qss" refere-se ao alias que definimos
    // no arquivo resources.qrc. O Qt sabe que deve procurar este arquivo
    // dentro dos recursos compilados, não no sistema de arquivos.
    QFile file(":/styles/dark_theme.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString styleSheet = stream.readAll();
        app.setStyleSheet(styleSheet);
        file.close();
        qDebug() << "Tema escuro carregado com sucesso.";
    } else {
        qDebug() << "Erro: Nao foi possivel carregar o arquivo de estilo 'dark_theme.qss'.";
        qDebug() << "Verifique se o arquivo 'resources.qrc' esta correto e incluido no build.";
    }
}

int main(int argc, char *argv[]) {
    // 1. Cria o objeto da aplicação. É necessário para qualquer app com GUI do Qt.
    QApplication app(argc, argv);

    // 2. Carrega nosso tema escuro.
    loadStyleSheet(app);

    // 3. Instancia nossa janela principal.
    // A classe MainWindow será definida em "windows/MainWindow.h" e "windows/MainWindow.cpp".
    MainWindow mainWindow;

    // 4. Exibe a janela principal.
    mainWindow.show();

    // 5. Inicia o loop de eventos da aplicação.
    // O programa ficará aqui, processando eventos (cliques, teclado, etc.)
    // até que a janela principal seja fechada.
    return app.exec();
}