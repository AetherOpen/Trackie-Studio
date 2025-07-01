// src/components/centralpanel/IconButton.h
// Um botão de ícone customizado, animado e "checkable".

#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QPushButton>
#include <QPropertyAnimation>
#include <QColor>

class IconButton : public QPushButton
{
    Q_OBJECT
    // Propriedade customizada para animar a cor de fundo suavemente.
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)

public:
    explicit IconButton(const QString &iconPath, QWidget *parent = nullptr);
    ~IconButton();

    QSize sizeHint() const override;

protected:
    // Eventos para controlar as animações de hover.
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

    // Onde desenhamos o nosso botão customizado.
    void paintEvent(QPaintEvent *event) override;

private slots:
    // Slot para reagir a mudanças no estado "checked".
    void onToggled(bool checked);

private:
    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    QPropertyAnimation *m_colorAnimation;
    QColor m_backgroundColor;
    QColor m_defaultColor;
    QColor m_hoverColor;
    QColor m_checkedColor;
};

#endif // ICONBUTTON_H