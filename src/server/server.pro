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

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-RPLDCommunications-Desktop_Qt_4_8_4_in_PATH_System-Debug/release/ -lRPLDCommunications
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-RPLDCommunications-Desktop_Qt_4_8_4_in_PATH_System-Debug/debug/ -lRPLDCommunications
#else:unix:!macx: LIBS += -L$$PWD/../build-RPLDCommunications-Desktop_Qt_4_8_4_in_PATH_System-Debug/ -lRPLDCommunications

#INCLUDEPATH += $$PWD/../build-RPLDCommunications-Desktop_Qt_4_8_4_in_PATH_System-Debug
#DEPENDPATH += $$PWD/../build-RPLDCommunications-Desktop_Qt_4_8_4_in_PATH_System-Debug
