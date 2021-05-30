#-------------------------------------------------
#
# Project created by QtCreator 2016-08-10T19:00:48
#
#-------------------------------------------------

QT       += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ClickerGame
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    achivementtimer.cpp \
    ultimate.cpp

HEADERS  += mainwindow.h \
    achivementtimer.h \
    ultimate.h

FORMS    += mainwindow.ui

RESOURCES +=
