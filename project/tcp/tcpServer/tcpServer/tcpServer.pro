#-------------------------------------------------
#
# Project created by QtCreator 2015-12-03T21:30:48
#
#-------------------------------------------------

QT       += core gui

TARGET = tcpServer
TEMPLATE = app


SOURCES += main.cpp\
        server.cpp \
    clientjobs.cpp \
    items.cpp

HEADERS  += server.h \
    clientjobs.h \
    items.h

FORMS    += server.ui

QT += network

RC_FILE += myico.rc
