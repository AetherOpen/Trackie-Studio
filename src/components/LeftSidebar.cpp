// src/components/LeftSidebar.cpp

#include "components/LeftSidebar.h"

// Inclusões completas necessárias para criar os widgets.
#include <QPushButton>
#include <QVBoxLayout>
#include <QFrame>
#include <QLabel>      // Usaremos QLabel como placeholders para os ícones
#include <QHBoxLayout> // Para organizar os ícones na barra inferior

LeftSidebar::LeftSidebar(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
}

void LeftSidebar::setupUi()
{
    // 1. Cria o layout principal para este widget.
    // O espaçamento de 10px será entre os botões Trackie e Spotway.
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 20, 10, 0); // Margens: esq, topo, dir, baixo
    mainLayout->setSpacing(10);

    // 2. Cria os botões principais.
    trackieButton = new QPushButton("Trackie", this);
    trackieButton->setFixedSize(160, 40);
    trackieButton->setCursor(Qt::PointingHandCursor); // Muda o cursor ao passar por cima

    spotwayButton = new QPushButton("Spotway", this);
    spotwayButton->setFixedSize(160, 40);
    spotwayButton->setCursor(Qt::PointingHandCursor);

    // TODO: Implementar o botão de colapso e sua lógica.
    // Por enquanto, vamos omiti-lo para focar na estrutura principal.

    // 3. Adiciona os botões ao layout, alinhados ao centro horizontalmente.
    mainLayout->addWidget(trackieButton, 0, Qt::AlignHCenter);
    mainLayout->addWidget(spotwayButton, 0, Qt::AlignHCenter);

    // 4. Adiciona um "espaçador elástico".
    // Isso empurra tudo o que vem depois para a parte inferior do layout.
    // É o truque para manter a barra de ferramentas no fundo.
    mainLayout->addStretch(1);

    // 5. Cria a barra de ferramentas inferior.
    bottomToolbar = new QFrame(this);
    bottomToolbar->setObjectName("bottomToolbar"); // Para estilizar com QSS (#bottomToolbar)
    bottomToolbar->setFixedHeight(40);
    // Remove a borda padrão que nosso QSS aplica a todos os QFrames.
    bottomToolbar->setStyleSheet("border: none; border-radius: 5px;");

    // Layout para os ícones dentro da barra de ferramentas.
    QHBoxLayout *toolbarLayout = new QHBoxLayout(bottomToolbar);
    toolbarLayout->setContentsMargins(10, 0, 10, 0);
    toolbarLayout->setSpacing(10);

    // Placeholders para os ícones. No futuro, usaremos QToolButton com QIcon.
    toolbarLayout->addWidget(new QLabel("G", bottomToolbar)); // Globo
    toolbarLayout->addWidget(new QLabel("T", bottomToolbar)); // Telefone
    toolbarLayout->addWidget(new QLabel("N", bottomToolbar)); // Nuvem
    toolbarLayout->addWidget(new QLabel("R", bottomToolbar)); // Raio
    toolbarLayout->addStretch(1); // Empurra os próximos ícones para a direita
    toolbarLayout->addWidget(new QLabel("G", bottomToolbar)); // Grade
    toolbarLayout->addWidget(new QLabel("-", bottomToolbar)); // Minimizar
    toolbarLayout->addWidget(new QLabel("+", bottomToolbar)); // Mais

    // 6. Adiciona a barra de ferramentas ao layout principal.
    mainLayout->addWidget(bottomToolbar);

    // Define o layout para este widget LeftSidebar.
    this->setLayout(mainLayout);
}