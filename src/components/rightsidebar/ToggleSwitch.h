// src/components/rightsidebar/ToggleSwitch.h
// Um widget de toggle customizado com animação suave.

#ifndef TOGGLESWITCH_H
#define TOGGLESWITCH_H

#include <QAbstractButton>
#include <QPropertyAnimation>

class ToggleSwitch : public QAbstractButton
{
    Q_OBJECT
    // Propriedade para animar a posição do círculo.
    Q_PROPERTY(int m_offset READ offset WRITE setOffset)

public:
    explicit ToggleSwitch(QWidget *parent = nullptr);
    ~ToggleSwitch();

    // Define o tamanho preferido para o widget.
    QSize sizeHint() const override;

protected:
    // Onde toda a mágica do desenho acontece.
    void paintEvent(QPaintEvent *e) override;
    // Captura o clique do mouse.
    void mouseReleaseEvent(QMouseEvent *e) override;

private:
    void setOffset(int offset);
    int offset() const;

    int m_offset;
    QPropertyAnimation *m_animation;
};

#endif // TOGGLESWITCH_H