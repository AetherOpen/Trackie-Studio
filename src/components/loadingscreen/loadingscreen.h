// src/components/loadingscreen/loadingscreen.h
// Definição da classe LoadingScreen, a tela de carregamento inicial da aplicação.

#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H

#include <QWidget>

class LoadingScreen : public QWidget
{
    Q_OBJECT

public:
    // O construtor define as flags da janela para ser sem bordas e translúcida.
    explicit LoadingScreen(QWidget *parent = nullptr);
    ~LoadingScreen();

protected:
    // Sobrescrevemos o paintEvent para fazer todo o nosso desenho customizado.
    // Este é o método mais importante para a aparência da nossa tela.
    void paintEvent(QPaintEvent *event) override;

private:
    // Função auxiliar para desenhar as formas de "pétalas" do fundo.
    void drawBackgroundShapes(QPainter &painter);
};

#endif // LOADINGSCREEN_H