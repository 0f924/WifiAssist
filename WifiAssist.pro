#-------------------------------------------------
#
# Project created by QtCreator 2016-03-11T22:37:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ../INSTALL/WifiAssist
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/wifi.cpp \
    src/wsettings.cpp \
    src/wdevices.cpp \
    src/about.cpp \
    src/wthread.cpp

HEADERS  += src/mainwindow.h \
    src/wifi.h \
    src/wsettings.h \
    src/wdevices.h \
    src/about.h \
    src/wthread.h
    ui_mainwindow.h

FORMS    += src/mainwindow.ui \
    src/about.ui

DISTFILES +=

RESOURCES += \
    resources/icon.qrc

include(src/singleapplication/singleapplication.pri)
