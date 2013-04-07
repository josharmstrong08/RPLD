/**
 * The Raspberry Pi server application.
 *
 * This application listens for messages from the desktop client application
 * as well as driving the LED matrices.
 */

#include <QCoreApplication>
#include <QThread>
#include <QObject>
#include "ledmatrixdriver.h"
#include "scrollingtextdisplay.h"

/**
 * @brief The entry point for the application.
 * @param argc The number of command line arguments
 * @param argv The array of command line argument strings.
 * @return The exit status of the application.
 */
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    LEDMatrixDriver *driver = new LEDMatrixDriver();
    ScrollingTextDisplay *display = new ScrollingTextDisplay(driver);
    QThread *displayThread = new QThread();

    QObject::connect(displayThread, SIGNAL(started()), display, SLOT(start()));
    QObject::connect(displayThread, SIGNAL(finished()), display, SLOT(deleteLater()));
    display->moveToThread(displayThread);

    displayThread->start();


    return a.exec();
}
