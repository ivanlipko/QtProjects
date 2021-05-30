#-------------------------------------------------
#
# Project created by QtCreator 2014-09-27T19:47:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChessCupViewer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    turwidget.cpp \
    mdiwindow.cpp

HEADERS  += mainwindow.h \
    turwidget.h \
    mdiwindow.h

FORMS    += mainwindow.ui \
    turwidget.ui

OTHER_FILES += \
    todo.txt
