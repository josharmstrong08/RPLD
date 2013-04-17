/**
 * The Raspberry Pi server application.
 *
 * This application listens for messages from the desktop client application
 * as well as driving the LED matrices.
 */

#include "server.h"
#include <QCoreApplication>

/**
 * @brief The entry point for the application.
 * @param argc The number of command line arguments
 * @param argv The array of command line argument strings.
 * @return The exit status of the application.
 */
int main(int argc, char *argv[])
{
    QCoreApplication *a = new QCoreApplication(argc, argv);

    // Create the server instance. The consuctor of it will set up
    // the driver, scrolling text display, and start listening for
    // incoming settings.
    //Server *server = new Server(a);
    Server server(a);

    return a->exec();
}
