QT += core gui \
      multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = SpaceCat

SOURCES += \
    barrieritem.cpp \
    catitem.cpp \
    main.cpp \
    scene.cpp \
    widget.cpp

HEADERS += \
    barrieritem.h \
    catitem.h \
    scene.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES +=
