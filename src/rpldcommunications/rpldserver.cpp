#include "rpldserver.h"
#include <QDebug>

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
    connect(this->client, SIGNAL(readyRead()), this, SLOT(startRead()));
}

/**
 * @brief This slot will read data sent from a TCP client.
 */
void RPLDServer::startRead()
{
    char buffer[1024] = {0};
    client->read(buffer, 1024);
    qDebug() << buffer;
    emit this->recievedSetting("text", QVariant(buffer));
}
