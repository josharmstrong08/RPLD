#-------------------------------------------------
#
# Project created by QtCreator 2013-03-23T10:32:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DesktopClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    displayconfigwidget.cpp

HEADERS  += mainwindow.h \
    displayconfigwidget.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc

unix:!macx|win32: LIBS += -L$$PWD/../build-RPLDCommunications/ -lRPLDCommunications

INCLUDEPATH += $$PWD/../rpldcommunications
DEPENDPATH += $$PWD/../rpldcommunications
