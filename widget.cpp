#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsPixmapItem>
//#include "barrieritem.h"
//#include "catitem.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    gameAudio = new QMediaPlayer();
    gameAudio->setMedia(QUrl("qrc:/audio/bgAudio.mp3"));

    setWindowIcon(QIcon(":/images/logo.png"));
    ui->setupUi(this);

    //Scene Instantiation
    scene = new Scene(this);
    scene->setSceneRect(-250,-300,500,600);

    QGraphicsPixmapItem * pixItem = new QGraphicsPixmapItem(QPixmap(":/images/sky2.jpg"));
    scene-> addItem(pixItem);
    pixItem->setPos(QPointF(0,0) - QPointF(pixItem->boundingRect().width()/2,
                                           pixItem->boundingRect().height()/2));

//    Testing codes
//    scene->addLine(-400,0,400,0,QPen(Qt::blue));
//    scene->addLine(0,-400,0,400,QPen(Qt::blue));

//    CatItem * cat = new CatItem(QPixmap(":/images/spacecatup1.png"));
//    scene->addItem(cat);

//    BarrierItem * barrier = new BarrierItem();
//    scene->addItem(barrier);

    ui->graphicsView->setScene(scene);
    scene->addCat();

    //play audio continously
    gameAudio->play();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_startButton_clicked()
{
    //Start Game
    scene->startGame();

    //play audio once the user clicks the Start Button
//    if (gameAudio->state() == QMediaPlayer::PlayingState) {
//        gameAudio->setPosition(0);
//    } else if (gameAudio->state() == QMediaPlayer::StoppedState) {
//        gameAudio->play();
//    }
//    QMediaPlayer * music = new QMediaPlayer();
//    music->setMedia(QUrl("qrc:/audio/bgAudio.mp3"));
//    music->play();
}


void Widget::on_bellabutton_clicked()
{

}


void Widget::on_leoButton_clicked()
{

}


void Widget::on_miloButton_clicked()
{

}

