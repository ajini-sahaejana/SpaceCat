#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "scene.h"
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_startButton_clicked();

    void on_bellabutton_clicked();

    void on_leoButton_clicked();

    void on_miloButton_clicked();

    void on_showStartButton();

private:
    Ui::Widget *ui;
    Scene * scene;
    QMediaPlayer * gameAudio;
};
#endif // WIDGET_H
