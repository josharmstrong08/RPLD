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
    ledmatrixdriver.cpp

HEADERS += \
    leddriver.h \
    ledmatrixdriver.h

QMAKE_CXXFLAGS += -std=c++0x
