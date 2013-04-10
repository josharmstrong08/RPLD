#-------------------------------------------------
#
# Project created by QtCreator 2013-04-01T10:40:15
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ledmatrixdriver.cpp \
    scrollingtextdisplay.cpp \
    ledtestdriver.cpp \
    font.cpp

HEADERS += \
    leddriver.h \
    ledmatrixdriver.h \
    scrollingtextdisplay.h \
    ledtestdriver.h

QMAKE_CXXFLAGS += -std=c++0x

DEFINES += USE_STD_OUT

unix:!macx|win32: LIBS += -L$$PWD/../build-RPLDCommunications/ -lRPLDCommunications

INCLUDEPATH += $$PWD/../rpldcommunications
DEPENDPATH += $$PWD/../rpldcommunications
