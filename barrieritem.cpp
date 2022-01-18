#include "barrieritem.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QGraphicsScene>
#include "scene.h"
#include "catitem.h"

BarrierItem::BarrierItem() :
    obstacle(new QGraphicsPixmapItem(QPixmap(":/images/burn2.png"))),
    pastShip(false)
{
    obstacle->setPos(QPointF(0,0) - QPointF(obstacle -> boundingRect().width()/2,
                                              obstacle->boundingRect().height() +120));

    addToGroup(obstacle);

    yPos = QRandomGenerator::global()->bounded(550);
    int xRandomizer = QRandomGenerator::global()->bounded(600);

    setPos(QPoint(0,0) + QPointF(640 + xRandomizer, yPos));

    xAnimation = new QPropertyAnimation(this, "x", this);
    xAnimation->setStartValue(640 + xRandomizer);
    xAnimation->setEndValue(-640);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(3000);

    connect(xAnimation,&QPropertyAnimation::finished,[=](){
        qDebug() << "Animation Finished";
        scene()->removeItem(this);
        delete this;
    });

    xAnimation->start();
}

BarrierItem::~BarrierItem()
{
    qDebug() << "Deleting Barrier";
    delete obstacle;
}

qreal BarrierItem::x() const
{
    return m_x;
}

void BarrierItem::freezeBarrier()
{
    xAnimation->stop();
}

void BarrierItem::setX(qreal x)
{
    //qDebug() << "Barrier position: " << x;
    m_x = x;

    if(x < 0 && !pastShip) {
        pastShip = true;
        QGraphicsScene * mScene = scene();
        Scene * myScene = dynamic_cast < Scene * >(mScene);
        if(myScene){
            myScene->incrementScore();
        }
    }
    if(shipCollides()) {
        emit collideFail();
    }
    setPos(QPoint(0,0) + QPointF(x,yPos));
}

bool BarrierItem::shipCollides()
{
    QList<QGraphicsItem*> collidingItems = obstacle->collidingItems();

    foreach(QGraphicsItem * item, collidingItems){
       CatItem * catItem = dynamic_cast<CatItem*>(item);
       if(catItem){
           return true;
       }
    }
    return false;
}
