// src/components/centralpanel/IconButton.cpp

#include "IconButton.h"
#include <QPainter>

IconButton::IconButton(const QString &iconPath, QWidget *parent)
    : QPushButton(parent),
      m_defaultColor(Qt::transparent),
      m_hoverColor(QColor(255, 255, 255, 20)), // Cinza muito sutil
      m_checkedColor(QColor("#555555"))       // Cinza sólido quando ativo
{
    setIcon(QIcon(iconPath));
    setIconSize(QSize(24, 24));
    setCheckable(true); // Permite que o botão seja "ativado".
    setFixedSize(48, 48);

    m_backgroundColor = m_defaultColor;

    // Configura a animação para a nossa propriedade customizada.
    m_colorAnimation = new QPropertyAnimation(this, "backgroundColor", this);
    m_colorAnimation->setDuration(200); // Animação de 200ms
    m_colorAnimation->setEasingCurve(QEasingCurve::InOutCubic);

    connect(this, &IconButton::toggled, this, &IconButton::onToggled);
}

IconButton::~IconButton() {}

QSize IconButton::sizeHint() const { return QSize(48, 48); }

void IconButton::enterEvent(QEnterEvent *event)
{
    if (!isChecked()) {
        m_colorAnimation->setEndValue(m_hoverColor);
        m_colorAnimation->start();
    }
    QPushButton::enterEvent(event);
}

void IconButton::leaveEvent(QEvent *event)
{
    if (!isChecked()) {
        m_colorAnimation->setEndValue(m_defaultColor);
        m_colorAnimation->start();
    }
    QPushButton::leaveEvent(event);
}

void IconButton::onToggled(bool checked)
{
    m_colorAnimation->setEndValue(checked ? m_checkedColor : m_defaultColor);
    m_colorAnimation->start();
}

void IconButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Desenha o fundo arredondado com a cor animada.
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_backgroundColor);
    painter.drawRoundedRect(rect(), 8, 8);

    // Desenha o ícone no centro.
    QIcon::Mode mode = isEnabled() ? QIcon::Normal : QIcon::Disabled;
    if (isChecked()) mode = QIcon::Active;

    QPixmap pixmap = icon().pixmap(iconSize(), mode);
    QRect iconRect = QRect(QPoint(0,0), iconSize());
    iconRect.moveCenter(rect().center());
    painter.drawPixmap(iconRect, pixmap);
}

void IconButton::setBackgroundColor(const QColor &color)
{
    m_backgroundColor = color;
    update(); // Redesenha o widget a cada passo da animação.
}

QColor IconButton::backgroundColor() const
{
    return m_backgroundColor;
}