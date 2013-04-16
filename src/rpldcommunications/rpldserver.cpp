#include "rpldserver.h"
#include <QDebug>
#include <QDataStream>

/**
 * @brief Initializes a new instance of the @see RPLDServer class. The server
 *   starts listening on the port 8888.
 * @param parent
 */
RPLDServer::RPLDServer(QObject *parent) :
    QObject(parent)
{
    this->server = new QTcpServer(this);
    connect(this->server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
    this->server->listen(QHostAddress::Any, 8888);
    qDebug() << "Server now listening";
}

/**
 * @brief Stops the TCP server.
 */
RPLDServer::~RPLDServer()
{
    this->server->close();
}

/**
 * @brief This slot will accept a new connection.
 */
void RPLDServer::acceptConnection()
{
    this->client = this->server->nextPendingConnection();
    this->messageSize = 0;
    this->recievingMessage = false;
    connect(this->client, SIGNAL(readyRead()), this, SLOT(dataReady()));
}

/**
 * @brief This slot will read data sent from a TCP client.
 */
void RPLDServer::dataReady()
{
    QDataStream in(this->client);
    in.setVersion(QDataStream::Qt_4_8);

    // Keep looping as long as there is data to recieve.
    while (in.atEnd() == false) {
        // If the message size is not yet defined, it should be the next value to be
        // sent.
        if (this->messageSize == 0) {
            // The message size itself could be coming across in several chunks, but
            // we know it's size: unsigned 16 bit integer.
            if (this->client->bytesAvailable() < (int)sizeof(quint16)) {
                return;
            } else {
                in >> this->messageSize;
            }
        }

        // Now wait until the full message comes across
        if (this->client->bytesAvailable() < this->messageSize) {
            return;
        }

        // At this point we have enough bytes to make a full message
        QString settingName;
        QVariant value;
        in >> settingName >> value;
        this->messageSize = 0;

        emit this->recievedSetting(settingName, value);
    }
}
