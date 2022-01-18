#include "catitem.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>

CatItem::CatItem(QPixmap pixmap) :
    shipPosition(ShipPosition::Up),
    shipDirection(0)
{
    setPixmap(pixmap);
    setX(-320);
    setY(-180);

    QTimer * catShipTimer = new QTimer(this);
    connect(catShipTimer, &QTimer::timeout,[=]() {
        updatePixmap();
    });

    catShipTimer->start(200);

    groundPosition = scenePos().y() + 350;

    yAnimation = new QPropertyAnimation(this, "y", this);
    yAnimation->setStartValue(scenePos().y());
    yAnimation->setEndValue(groundPosition);
    yAnimation->setEasingCurve(QEasingCurve::InQuad);
    yAnimation->setDuration(1000);

    rotationAnimation = new QPropertyAnimation(this, "rotation", this);

//    rotateTo(90, 1200, QEasingCurve::InQuad);
//    yAnimation->start();
//    yAnimation->setStartValue(groundPosition);
//    yAnimation->setStartValue(y());
//    yAnimation->setEasingCurve(QEasingCurve::InQuad);
//    yAnimation->setEndValue(groundPosition);
//    yAnimation->setDuration(1200);
}

qreal CatItem::rotation() const
{
    return m_rotation;
}

qreal CatItem::y() const
{
    return m_y;
}

void CatItem::flyUp()
{
    if(y()>-400){
        yAnimation->stop();
        rotationAnimation->stop();

        qreal curPosY = y();

        yAnimation->setStartValue(curPosY);
        yAnimation->setEndValue(curPosY - scene()->sceneRect().height()/6);
        yAnimation->setEasingCurve(QEasingCurve::OutQuad);
        yAnimation->setDuration(285);

        connect(yAnimation, &QPropertyAnimation::finished,[=](){
            fallToGround();
        });

        yAnimation->start();

        rotateTo(-20, 200, QEasingCurve::OutCubic);
    }

}

void CatItem::startFlying()
{
    yAnimation->start();
    rotateTo(90, 1200, QEasingCurve::InQuad);
}

void CatItem::freezeShip()
{
    yAnimation->stop();
    rotationAnimation->stop();
}

void CatItem::setRotation(qreal rotation)
{
    m_rotation = rotation;

    QPointF c = boundingRect().center();

    QTransform t;
    t.translate(c.x(), c.y());
    t.rotate(rotation);
    t.translate(-c.x(), -c.y());
    setTransform(t);
}

void CatItem::setY(qreal y)
{
    moveBy(0,y-m_y);
    m_y = y;
}

void CatItem::rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve)
{
    rotationAnimation->setStartValue(rotation());
    rotationAnimation->setEndValue(end);
    rotationAnimation->setEasingCurve(curve);
    rotationAnimation->setDuration(duration);

    rotationAnimation->start();
}

void CatItem::fallToGround()
{
    if(y() < groundPosition) {
        rotationAnimation->stop();
        //yAnimation->stop();

        yAnimation->setStartValue(y());
        yAnimation->setEasingCurve(QEasingCurve::InQuad);
        yAnimation->setEndValue(groundPosition);
        yAnimation->setDuration(1200);
        yAnimation->start();

        rotateTo(90, 1100, QEasingCurve::InCubic);
    }
    qDebug() << y();
}

void CatItem::updatePixmap()
{
    if(shipPosition == ShipPosition::Middle) {
        if(shipDirection) {
            //Up
            setPixmap(QPixmap(":/images/spacecatup1.png"));
            shipPosition = ShipPosition::Up;
            shipDirection = 0;
        } else {
            //down
            setPixmap(QPixmap(":/images/spacecatdown1.png"));
            shipPosition = ShipPosition::Down;
            shipDirection = 1;
        }
    } else {
        setPixmap(QPixmap(":/images/spacecat1.png"));
        shipPosition = ShipPosition::Middle;
    }
}
