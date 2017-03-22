#-------------------------------------------------
#
# Project created by QtCreator 2017-03-22T10:16:33
#
#-------------------------------------------------

QT       += core gui script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DoJS
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

DISTFILES += \
    TransCal.js

RESOURCES += \
    dojs.qrc
