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

    Server *server = new Server(a);

    return a->exec();
}
