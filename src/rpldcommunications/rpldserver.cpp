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
    this->messageSize = 0;
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

        // At this point we have enough bytes to recreate the full message
        // Read the message type part of the message
        QString messageType;
        in >> messageType;

        if (messageType == "setsetting") {
            // Read the setting name and value
            QVariant value;
            QString settingName;
            in >> settingName >> value;
            emit this->recievedSetting(settingName, value);
            this->messageSize = 0;
        } else if (messageType == "requestsetting") {
            // Read the setting name and get it.
            QString settingName;
            in >> settingName;
            emit this->settingRequested(settingName);
            this->messageSize = 0;
        } else  {
            qDebug() << "Unknown messagetype " << messageType;
            //char *dummy;
            //in.readBytes(dummy, this->client->bytesAvailable);
            this->messageSize = 0;
        }
    }
}

/**
 * @brief This slot will send the given setting to a connected client. Usually it
 *   is called because the settingRequested signal was emitted.
 * @param settingName
 * @param value
 */
void RPLDServer::returnSettingValue(QString settingName, QVariant value)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    QString messageType = "returnsetting";
    out.setVersion(QDataStream::Qt_4_8);
    out << (quint16)0;
    out << messageType << settingName << value;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    this->client->write(block);
}
