#-------------------------------------------------
#
# Project created by QtCreator 2016-01-07T21:50:48
#
#-------------------------------------------------

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += webenginewidgets

CONFIG += c++11

TARGET = abrowser
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    webcontainer.cpp \
    webpage.cpp

HEADERS += \
    common.h \
    mainwindow.h \
    tabhost.h \
    webcontainer.h \
    webpage.h
