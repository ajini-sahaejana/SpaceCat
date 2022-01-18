#ifndef BARRIERITEM_H
#define BARRIERITEM_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class BarrierItem : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)

public:
    explicit BarrierItem();
    ~BarrierItem();
    qreal x() const;

    void freezeBarrier();

signals:
    void collideFail();

public slots:
    void setX(qreal x);

private:

    bool shipCollides();

    QGraphicsPixmapItem * obstacle;
    QPropertyAnimation * xAnimation;

    int yPos;
    qreal m_x;

    bool pastShip;
};

#endif // BARRIERITEM_H
