#-------------------------------------------------
# (c) 2018 Jens Kallup
# all rights reserved.
#-------------------------------------------------

QT       += core gui widgets network sql

TARGET = mathnews
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cc \
        mainwindow.cc \
    mytcpserver.cc \
    mytcpclient.cc \
    mytask.cc \
    dbmanager.cc \
    mathesymbole.cc \
    symbolinputbox.cc

HEADERS += \
        mainwindow.h \
    mytcpserver.h \
    mytcpclient.h \
    mytask.h \
    dbmanager.h \
    mathesymbole.h \
    symbolinputbox.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    resources.qrc

LIBS += -L../build-calcparser-Desktop_Qt_5_10_0_GCC_64bit-Debug -lcalcparser -ly
