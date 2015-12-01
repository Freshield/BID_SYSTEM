#-------------------------------------------------
#
# Project created by QtCreator 2015-12-01T16:40:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SERVER_GUI
TEMPLATE = app


SOURCES += main.cpp\
        server.cpp

HEADERS  += server.h

FORMS    += server.ui

LIBS += -lws2_32

