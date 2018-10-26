#-------------------------------------------------
# (c) 2018 Jens Kallup
# all rights reserved.
#-------------------------------------------------

QT       += core gui widgets network sql webenginewidgets

TARGET = mathnews
TEMPLATE = app

CONFIG += c++14 debug

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cc \
    mainwindow.cc \
    mathesymbole.cc \
    symbolinputbox.cc \
    mathwebpage.cpp \
    mathgetposts.cpp \
    strom.cpp

HEADERS += \
    mainwindow.h \
    mathesymbole.h \
    symbolinputbox.h \
    mathgetposts.h \
    mathwebpage.h \
    strom.h \
    simulatorvisitor.h \
    downvisitor.h \
    visitorcommando.h \
    visitorenergie.h \
    slamp.h \
    visitorwire.h \
    visitorlamp.h \
    connection.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    resources.qrc

LIBS += -L. -lcrypto -lssl -lcalcparser -ly
