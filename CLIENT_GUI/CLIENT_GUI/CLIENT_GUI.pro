#-------------------------------------------------
#
# Project created by QtCreator 2015-12-01T18:43:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CLIENT_GUI
TEMPLATE = app


SOURCES += main.cpp\
        client.cpp

HEADERS  += client.h

FORMS    += client.ui

LIBS += -lws2_32
