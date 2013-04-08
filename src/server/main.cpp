/**
 * The Raspberry Pi server application.
 *
 * This application listens for messages from the desktop client application
 * as well as driving the LED matrices.
 */

#include <QCoreApplication>
#include <QThread>
#include <QObject>
#include <QDebug>
#ifdef USE_STD_OUT
#include "ledtestdriver.h"
#else
#include "ledmatrixdriver.h"
#endif
#include "scrollingtextdisplay.h"

/**
 * @brief The entry point for the application.
 * @param argc The number of command line arguments
 * @param argv The array of command line argument strings.
 * @return The exit status of the application.
 */
int main(int argc, char *argv[])
{
    QCoreApplication *a = new QCoreApplication(argc, argv);
    
#ifdef USE_STD_OUT
    LEDTestDriver *driver = new LEDTestDriver();
#else
    // Set up the scrolling text display with the led matrix driver.
    LEDMatrixDriver *driSOME_DEFINE=valuever = new LEDMatrixDriver();
    int **matrixconfig = (int**)malloc(sizeof(int*));
    *matrixconfig = (int*)malloc(sizeof(int));
    **matrixconfig = 1;
    driver->SetMatrixConfig(matrixconfig, 1, 1);
#endif
    ScrollingTextDisplay *display = new ScrollingTextDisplay(driver, 32, 32);

    // Create the display thread
    QThread *displayThread = new QThread();

    // Start the display when the thread starts.
    QObject::connect(displayThread, SIGNAL(started()), display, SLOT(start()));
    // When the display finishes executing, quit the thread.
    QObject::connect(display, SIGNAL(finished()), displayThread, SLOT(quit()));
    // When the thread is finished, delete the display.
    QObject::connect(displayThread, SIGNAL(finished()), display, SLOT(deleteLater()));
    // When the thead is finished exit the program.
    QObject::connect(displayThread, SIGNAL(finished()), a, SLOT(quit()));
    // Push the display onto the display thread
    display->moveToThread(displayThread);
    qDebug() << "Starting a new thread from the main thread (thread " << QThread::currentThreadId() << ")";
    // Start the thread
    displayThread->start();
    qDebug() << "Started the thread";
    displayThread->wait();
    qDebug() << "Joined the thread";

    return 0;
}
