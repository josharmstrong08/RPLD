#include "server.h"

#ifdef USE_STD_OUT
#include "ledtestdriver.h"
#else
#include "ledmatrixdriver.h"
#endif
#include "scrollingtextdisplay.h"
#include "rpldserver.h"
#include <QThread>
#include <QObject>
#include <QDebug>
#include <QVariant>
#include <QCoreApplication>

/**
 * @brief Server::Server
 * @param parent
 */
Server::Server(QObject *parent) :
    QObject(parent)
{
#ifdef USE_STD_OUT
    // Setup the scrolling text display with the test stdout driver.
    LEDTestDriver *driver = new LEDTestDriver();
#else
    // Set up the scrolling text display with the led matrix driver.
    LEDMatrixDriver *driSOME_DEFINE=valuever = new LEDMatrixDriver();
    int **matrixconfig = (int**)malloc(sizeof(int*));
    *matrixconfig = (int*)malloc(sizeof(int));
    **matrixconfig = 1;
    driver->SetMatrixConfig(matrixconfig, 1, 1);
#endif
    this->display = new ScrollingTextDisplay(driver, 64, 32);

    this->display->setText("Hello world!");
    this->display->setScrollingSpeed(1);
    this->display->setColor(0xff, 0xff, 0xff);

    // Start listening for incoming settings
    RPLDServer *rpldServer = new RPLDServer(this);
    QObject::connect(rpldServer, SIGNAL(recievedSetting(QString,QVariant)), this, SLOT(recievedSetting(QString,QVariant)));

    // Create the display thread
    QThread *displayThread = new QThread(this);

    // Start the display when the thread starts.
    QObject::connect(displayThread, SIGNAL(started()), display, SLOT(start()));
    // When the display finishes executing, quit the thread.
    QObject::connect(display, SIGNAL(finished()), displayThread, SLOT(quit()));
    // When the thread is finished, delete the display.
    QObject::connect(displayThread, SIGNAL(finished()), display, SLOT(deleteLater()));
    // When the thead is finished exit the program.
    QObject::connect(displayThread, SIGNAL(finished()), qApp, SLOT(quit()));
    // Push the display onto the display thread
    display->moveToThread(displayThread);
    // Start the thread
    displayThread->start();
}

/**
 * @brief Server::recievedSetting
 * @param settingName
 * @param value
 */
void Server::recievedSetting(QString settingName, QVariant value)
{
    if (settingName == "text") {
        this->display->setText(value.toString());
    } else if (settingName == "speed") {
        this->display->setScrollingSpeed(value.toInt());
    } else if (settingName == "color") {
        QString string = value.toString();
        unsigned char red = string.section(',', 0, 0).toUInt();
        unsigned char green = string.section(',', 1, 1).toUInt();
        unsigned char blue = string.section(',', 2, 2).toUInt();
        this->display->setColor(red, green, blue);
    }
}
