// src/components/loadingscreen/loadingscreen.cpp
// Implementação da classe LoadingScreen.

#include "loadingscreen.h"

#include <QPainter>
#include <QPainterPath>
#include <QLinearGradient>
#include <QScreen>
#include <QGuiApplication>
#include <QFontDatabase>

LoadingScreen::LoadingScreen(QWidget *parent)
    : QWidget(parent)
{
    // --- Configuração da Janela ---
    // 1. Define as flags para criar uma janela sem borda e que fica sobre as outras.
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    // 2. Habilita a translucidez, essencial para podermos ter cantos arredondados.
    setAttribute(Qt::WA_TranslucentBackground);

    // 3. Define um tamanho fixo para a nossa tela de carregamento.
    setFixedSize(640, 360); // Proporção 16:9

    // 4. Centraliza a janela na tela principal.
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {
        QRect screenGeometry = screen->geometry();
        int x = (screenGeometry.width() - width()) / 2;
        int y = (screenGeometry.height() - height()) / 2;
        move(x, y);
    }
}

LoadingScreen::~LoadingScreen() {}

void LoadingScreen::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    // Habilita o antialiasing para ter curvas e textos suaves e de alta qualidade.
    painter.setRenderHint(QPainter::Antialiasing);

    // --- Desenho do Corpo Principal (com cantos arredondados) ---
    QPainterPath path;
    // Um raio de 20px para os cantos, um valor moderno e suave.
    path.addRoundedRect(rect(), 20, 20);
    painter.setClipPath(path); // Define que todo o desenho ocorrerá dentro deste path.

    // --- Desenho do Fundo com Gradiente ---
    // Inspirado na imagem do PyCharm (verde para amarelo).
    QLinearGradient gradient(0, height(), width(), 0);
    gradient.setColorAt(0.0, QColor(20, 100, 40));  // Verde escuro e rico
    gradient.setColorAt(1.0, QColor(210, 230, 90)); // Amarelo-esverdeado vibrante
    painter.fillPath(path, gradient);

    // --- Desenho das Formas Abstratas de Fundo ---
    drawBackgroundShapes(painter);

    // --- Desenho dos Textos ---
    painter.setPen(Qt::white); // Define a cor do texto para branco.

    // 1. "AetherWay AI"
    QFont logoFont("Sans-Serif", 14);
    painter.setFont(logoFont);
    painter.drawText(QRect(40, 35, 200, 40), Qt::AlignLeft | Qt::AlignTop, "AetherWay AI");

    // 2. "Trackie Studio"
    QFont titleFont("Sans-Serif", 60, QFont::Bold);
    painter.setFont(titleFont);
    painter.drawText(rect(), Qt::AlignCenter, "Trackie Studio");

    // 3. "Version 1.0"
    QFont versionFont("Sans-Serif", 16);
    painter.setFont(versionFont);
    // Posiciona o texto da versão um pouco abaixo do centro vertical.
    painter.drawText(QRect(0, height() / 2 + 50, width(), 40), Qt::AlignHCenter, "Version 1.0");
}

void LoadingScreen::drawBackgroundShapes(QPainter &painter)
{
    // Esta função cria o efeito de "pétalas" ou "leque" de forma procedural.
    painter.save(); // Salva o estado atual do painter (transformações, opacidade, etc.)

    // Pivô de rotação no canto inferior esquerdo.
    painter.translate(0, height());

    // Desenha 12 "pétalas" em um loop.
    for (int i = 0; i < 12; ++i) {
        // Define uma cor branca com baixíssima opacidade para criar um brilho sutil.
        painter.setBrush(QColor(255, 255, 255, 8));
        painter.setPen(Qt::NoPen); // Não queremos bordas nas formas.

        painter.save();
        // Cada pétala é rotacionada um pouco mais que a anterior.
        painter.rotate(-i * 8.0);

        // Cria a forma da pétala usando uma curva de Bézier.
        QPainterPath petalPath;
        petalPath.moveTo(0, 0);
        petalPath.cubicTo(width() * 0.8, -height() * 0.5, width() * 0.7, -height() * 1.2, 0, -height() * 1.2);
        petalPath.closeSubpath();
        painter.drawPath(petalPath);

        painter.restore();
    }

    painter.restore(); // Restaura o painter ao estado original.
}