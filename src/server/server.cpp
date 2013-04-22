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
    LEDTestDriver *testdriver = new LEDTestDriver();
    this->driver = testdriver;
#else
    // Set up the scrolling text display with the led matrix driver.
    LEDMatrixDriver *matrixdriver = new LEDMatrixDriver();
    int **matrixconfig = (int**)malloc(sizeof(int*));
    *matrixconfig = (int*)malloc(sizeof(int));
    **matrixconfig = 1;
    matrixdriver->SetMatrixConfig(matrixconfig, 1, 1);
    this->driver = matrixdriver;
#endif

    // Create the driver thread
    QThread *driverThread = new QThread(this);
    // When the thread starts, start the driver.
    QObject::connect(driverThread, SIGNAL(started()), this->driver, SLOT(start()));
    // Delete the driver when the thread stops (when driverThread->quit() is called)
    QObject::connect(driverThread, SIGNAL(finished()), this->driver, SLOT(deleteLater()));
    // Move the driver to the driver thread
    this->driver->moveToThread(driverThread);

    // Create the scrolling text display, which generates frames when needed.
    this->display = new ScrollingTextDisplay(32, 32);
    // connect the scrolling text display's update frame signal to the driver's output frame slot.
    connect(this->display, SIGNAL(updateFrame(uint8_t*,ulong,ulong)), this->driver, SLOT(outputFrame(uint8_t*,ulong,ulong)));

    // Set initial values
    // TODO Load values from persistent storage, QSettings?
    this->display->setText("Hello world!");
    this->display->setScrollingSpeed(1);
    this->display->setColor(0xff, 0xff, 0xff);

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

    // Start listening for incoming settings
    this->rpldServer = new RPLDServer(this);
    QObject::connect(this->rpldServer, SIGNAL(recievedSetting(QString,QVariant)), this, SLOT(recievedSetting(QString,QVariant)));
    QObject::connect(this->rpldServer, SIGNAL(settingRequested(QString)), this, SLOT(settingRequested(QString)));

    // Start the driver thread
    driverThread->start();
    // Start the display thread
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
    } else if (settingName == "shutdown") {
        // This program should be running as root
        system("halt");
    } else if (settingName == "matrixcount") {
        int count = value.toInt();
#ifndef USE_STD_OUT
        int **matrixconfig = (int**)malloc(sizeof(int*));
        *matrixconfig = (int*)malloc(sizeof(int) * count);
        for (int i = 0; i < count; i++) {
            matrixconfig[0][i] = i;
        }
        LEDMatrixDriver *matrixdriver = static_cast<LEDMatrixDriver*>(this->driver);
        matrixdriver->SetMatrixConfig(matrixconfig, count, 1);
#endif
        this->display->setWidth(count * 32);
        this->display->setHeight(32);
    }
}

/**
 * @brief A setting value was requested by the client. Return it through the
 *   communications library.
 * @param settingName The name of the setting requested.
 */
void Server::settingRequested(QString settingName)
{
    if (settingName == "text") {
        this->rpldServer->returnSettingValue("text", this->display->getText());
    } else if (settingName == "speed") {
        this->rpldServer->returnSettingValue("speed", this->display->getScrollingSpeed());
    } else if (settingName == "color") {
        //this->rpldServer->returnSettingValue("color", this->display->getc);
    } else if (settingName == "matrixcount") {
        //this->rpldServer->returnSettingValue(this->display->ge);
    }
}
