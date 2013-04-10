#-------------------------------------------------
#
# Project created by QtCreator 2013-04-09T08:35:16
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = RPLDCommunications
TEMPLATE = lib

DEFINES += RPLDCOMMUNICATIONS_LIBRARY

SOURCES += rpldcommunications.cpp \
    message.cpp

HEADERS += rpldcommunications.h\
        rpldcommunications_global.h \
    message.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

DESTDIR = ../build-RPLDCommunications
