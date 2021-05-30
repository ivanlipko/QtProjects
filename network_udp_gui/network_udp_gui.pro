#-------------------------------------------------
#
# Project created by QtCreator 2018-04-05T15:55:58
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = network_udp_gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    network.cpp

HEADERS  += mainwindow.h \
    network.h

FORMS    += mainwindow.ui
