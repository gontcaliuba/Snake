#-------------------------------------------------
#
# Project created by QtCreator 2015-07-20T14:25:20
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Snake1_0
TEMPLATE = app

#win32:RC_ICONS += icons/images/icon.png

SOURCES += main.cpp\
        mainwindow.cpp \
    position.cpp \
    size.cpp \
    cell.cpp \
    snake.cpp \
    field.cpp \
    fielddrawer.cpp \
    fileworker.cpp \
    level.cpp \
    game.cpp \
    engine.cpp

HEADERS  += mainwindow.h \
    position.h \
    size.h \
    direction.h \
    cell.h \
    snake.h \
    field.h \
    fielddrawer.h \
    fieldimages.h \
    fileworker.h \
    level.h \
    game.h \
    engine.h \
    gamestate.h \
    sounds.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
