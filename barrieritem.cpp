#include "barrieritem.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QGraphicsScene>
#include "scene.h"
#include "catitem.h"

BarrierItem::BarrierItem() :
    topBarrier(new QGraphicsPixmapItem(QPixmap(":/images/burn2.png"))),
    //bottomBarrier(new QGraphicsPixmapItem(QPixmap(":/images/burn2.png"))),
    pastShip(false)
{
    topBarrier->setPos(QPointF(0,0) - QPointF(topBarrier -> boundingRect().width()/2,
                                              topBarrier->boundingRect().height() +120));

    //bottomBarrier->setPos(QPointF(0,0) + QPointF(bottomBarrier->boundingRect().width()/2, 60));

    addToGroup(topBarrier);
    //addToGroup(bottomBarrier);

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
    delete topBarrier;
    //delete bottomBarrier;
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
    QList<QGraphicsItem*> collidingItems = topBarrier->collidingItems();
    //collidingItems.append(bottomBarrier->collidingItems());

    foreach(QGraphicsItem * item, collidingItems){
       CatItem * catItem = dynamic_cast<CatItem*>(item);
       if(catItem){
           return true;
       }
    }
    return false;
}
