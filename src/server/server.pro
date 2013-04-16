#-------------------------------------------------
#
# Project created by QtCreator 2013-04-01T10:40:15
#
#-------------------------------------------------

QT       += core
QT       += network

QT       -= gui

TARGET = server
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += debug

TEMPLATE = app


SOURCES += main.cpp \
    ledmatrixdriver.cpp \
    scrollingtextdisplay.cpp \
    ledtestdriver.cpp \
    font.cpp \
    server.cpp

HEADERS += \
    leddriver.h \
    ledmatrixdriver.h \
    scrollingtextdisplay.h \
    ledtestdriver.h \
    server.h

QMAKE_CXXFLAGS += -std=c++0x

#DEFINES += USE_STD_OUT

unix:!macx|win32: LIBS += -L$$PWD/../build-RPLDCommunications/ -lRPLDCommunications
LIBS += -lwiringPi

INCLUDEPATH += $$PWD/../rpldcommunications
DEPENDPATH += $$PWD/../rpldcommunications
