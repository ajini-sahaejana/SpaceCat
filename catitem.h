#ifndef CATITEM_H
#define CATITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class CatItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal y READ y WRITE setY)

public:
    explicit CatItem(QPixmap pixmap);

    qreal rotation() const;

    qreal y() const;

    void flyUp();

    void startFlying();

    void freezeShip();


signals:

public slots:
    void setRotation(qreal rotation);

    void setY(qreal y);

    void rotateTo(const qreal &end, const int& duration, const QEasingCurve& curve);

    void fallToGround();

private:
    enum ShipPosition{
        Up,
        Middle,
        Down
    };
    void updatePixmap();

    ShipPosition shipPosition;
    bool shipDirection;

    qreal m_rotation;
    qreal m_y;

    QPropertyAnimation * yAnimation;
    QPropertyAnimation * rotationAnimation;

    qreal groundPosition;
};

#endif // CATITEM_H
