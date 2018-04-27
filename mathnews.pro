#-------------------------------------------------
#
# Project created by QtCreator 2018-04-26T23:16:29
#
#-------------------------------------------------

QT       += core gui widgets network

TARGET = mathnews
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cc \
        mainwindow.cc \
    mytcpserver.cc \
    mytcpclient.cc \
    mytask.cc

HEADERS += \
        mainwindow.h \
    mytcpserver.h \
    mytcpclient.h \
    mytask.h

FORMS += \
        mainwindow.ui
