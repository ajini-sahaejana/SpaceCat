#include "widget.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/images/spaceCatMain.jpg"));
    splash->show();

    Widget w;

    QTimer::singleShot(3000,splash,SLOT(close()));
    QTimer::singleShot(3000,&w,SLOT(show()));

    //w.show();

    return a.exec();
}
