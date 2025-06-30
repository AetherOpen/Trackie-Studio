// src/components/rightsidebar/ToggleSwitch.cpp

#include "ToggleSwitch.h"
#include <QPainter>

ToggleSwitch::ToggleSwitch(QWidget *parent)
    : QAbstractButton(parent),
      m_offset(0)
{
    setCheckable(true);
    // Por padrão, o toggle começa desligado.
    setChecked(false);

    // Configura a animação para a propriedade 'm_offset'.
    m_animation = new QPropertyAnimation(this, "m_offset", this);
    m_animation->setDuration(150); // Animação rápida de 150ms.
    m_animation->setEasingCurve(QEasingCurve::InOutCubic); // Curva suave.

    // Quando o estado muda (clicado), atualizamos a animação.
    connect(this, &ToggleSwitch::toggled, this, [this](bool checked) {
        int endValue = checked ? height() - 4 : 0;
        m_animation->setEndValue(endValue);
        m_animation->start();
    });
}

ToggleSwitch::~ToggleSwitch() {}

QSize ToggleSwitch::sizeHint() const
{
    // Tamanho padrão elegante.
    return QSize(48, 24);
}

void ToggleSwitch::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // Define as cores com base no estado (ligado/desligado).
    QColor bgColor = isChecked() ? QColor("#FFFFFF") : QColor("#555555");
    QColor circleColor = isChecked() ? QColor("#222222") : QColor("#FFFFFF");
    int radius = (height() - 4) / 2;

    // Desenha o fundo arredondado.
    p.setPen(Qt::NoPen);
    p.setBrush(bgColor);
    p.drawRoundedRect(rect(), radius + 2, radius + 2);

    // Desenha o círculo que se move.
    p.setBrush(circleColor);
    // A posição X do círculo é controlada pela nossa propriedade animada 'm_offset'.
    p.drawEllipse(m_offset + 2, 2, radius * 2, radius * 2);
}

void ToggleSwitch::mouseReleaseEvent(QMouseEvent *e)
{
    // Inverte o estado ao clicar.
    setChecked(!isChecked());
    QAbstractButton::mouseReleaseEvent(e);
}

void ToggleSwitch::setOffset(int offset)
{
    m_offset = offset;
    update(); // Redesenha o widget a cada passo da animação.
}

int ToggleSwitch::offset() const
{
    return m_offset;
}