#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>
#include "barrieritem.h"
#include "catitem.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

    void addCat();
    void startGame();

    bool getGameOn() const;
    void setGameOn(bool value);

    void incrementScore();
    void setScore(int value);

    int getScore() const;

signals:
    void showPlayButton();

public slots:
    void on_gameOver();

    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    void showGameOverGraphics();
    void hideGameOverGraphics();
    void cleanBarriers();
    void setUpBarrierTimer();
    void freezeShipandBarriers();

    QTimer * barrierTimer;
    CatItem * cat;

    bool gameOn;
    int score;
    int highscore;

    QGraphicsPixmapItem * gameOverPix = nullptr;
    QGraphicsTextItem * scoreTextItem = nullptr;
};

#endif // SCENE_H
