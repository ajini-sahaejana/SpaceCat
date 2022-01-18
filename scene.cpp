#include "scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>

Scene::Scene(QObject *parent) : QGraphicsScene(parent),
    gameOn(false), score(0), highscore(0)
{
    setUpBarrierTimer();

    //    CatItem * cat = new CatItem(QPixmap(":/images/spacecatup1.png"));
    //    addItem(cat);
}

void Scene::addCat()
{
    cat = new CatItem(QPixmap(":/images/spacecatup1.png"));
    addItem(cat);
}

void Scene::startGame()
{
    cat->startFlying();

    if(!barrierTimer->isActive()){
        cleanBarriers();
        setGameOn(true);
        setScore(0);
        hideGameOverGraphics();
        barrierTimer->start(1000);
    }
}

void Scene::setUpBarrierTimer()
{
    barrierTimer = new QTimer(this);
    connect(barrierTimer, &QTimer::timeout,[=](){
        BarrierItem * barrierItem = new BarrierItem();
        connect(barrierItem, &BarrierItem::collideFail,[=](){
            barrierTimer->stop();
            freezeShipandBarriers();
            setGameOn(false);
            showGameOverGraphics();
        });
        addItem(barrierItem);

    });

    //     barrierTimer->start(1000);
}

void Scene:: freezeShipandBarriers()
{
    //Freeze Ship
    cat->freezeShip();

    //Freeze Barriers
    QList<QGraphicsItem *> sceneItems = items();
    foreach (QGraphicsItem *item, sceneItems){
        BarrierItem * barrier = dynamic_cast < BarrierItem * > (item);
        if(barrier){
            barrier->freezeBarrier();
        }
    }
}

int Scene::getScore() const
{
    return score;
}

void Scene::on_gameOver()
{
    qDebug() << "game over!!";
}

bool Scene::getGameOn() const
{
    return gameOn;
}
void Scene::setGameOn(bool value)
{
    gameOn = value;
}

void Scene::incrementScore()
{
    score++;
    if(score > highscore)
        highscore = score;
        //qDebug() << "Score: " << score << "Highest Score: " << highscore;
}

void Scene::setScore(int value)
{
    score = value;
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Space) {
        if(gameOn){
            cat->flyUp();
        }
    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton) {
        if(gameOn){
            cat->flyUp();
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

void Scene::showGameOverGraphics()
{
    emit showPlayButton();

    gameOverPix = new QGraphicsPixmapItem(QPixmap(":/images/gameover1.png"));
    addItem(gameOverPix);
    gameOverPix->setPos(QPointF(0,0) - QPointF(gameOverPix->boundingRect().width()/2,
                                               gameOverPix->boundingRect().height()/1.5));
    scoreTextItem = new QGraphicsTextItem();

    QString htmlString = "<h6>Score: " + QString::number(score) + "</h6>"
            + "<h6> Highest Score: " + QString::number(highscore) + "</h6>";

    QFont mFont("Calibri", 20, QFont:: Bold);

    scoreTextItem->setHtml(htmlString);
    scoreTextItem->setFont(mFont);
    scoreTextItem->setDefaultTextColor(Qt::white);
    addItem(scoreTextItem);

    scoreTextItem->setPos(QPointF(0,0) - QPointF(scoreTextItem->boundingRect().width()/2,
                                                 -gameOverPix->boundingRect().height()/2));
}

void Scene::hideGameOverGraphics()
{
    if(gameOverPix == nullptr || scoreTextItem == nullptr) {
        return;
    }
    if(gameOverPix){
        removeItem(gameOverPix);
        delete gameOverPix;
        gameOverPix = nullptr;
    }
    if(scoreTextItem){
        removeItem(scoreTextItem);
        delete scoreTextItem;
        scoreTextItem = nullptr;
    }
}

void Scene::cleanBarriers()
{
    QList<QGraphicsItem *> sceneItems = items();
    foreach (QGraphicsItem *item, sceneItems){
        BarrierItem * barrier = dynamic_cast < BarrierItem * > (item);
        if(barrier) {
            removeItem(barrier);
            delete(barrier);
        }
    }
}
