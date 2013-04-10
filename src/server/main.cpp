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
#include "rpldcommunications.h"

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
    ScrollingTextDisplay *display = new ScrollingTextDisplay(driver, 64, 32);
    display->setText("Hello world! 1234567890 ~!@#$%^&*()_+[]{};:'\",<.>/?\\|");
    display->setScrollingSpeed(1);

    RPLDCommunications *test = new RPLDCommunications();
    test->sendSetting("setting", 1);
    test->connect();

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
    // Start the thread
    displayThread->start();

    displayThread->wait();

    return 0;
}
