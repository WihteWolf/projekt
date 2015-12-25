#-------------------------------------------------
#
# Project created by QtCreator 2015-12-25T01:23:01
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ClientQt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    config.cpp \
    dateuser.cpp \
    registr.cpp

HEADERS  += mainwindow.h \
    config.h \
    dateuser.h \
    registr.h

FORMS    += mainwindow.ui \
    config.ui \
    dateuser.ui \
    registr.ui

RESOURCES +=
