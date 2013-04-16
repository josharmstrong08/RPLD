#include "rpldclient.h"
#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>

/**
 * @brief Initializes a new instance of the @see RPLDClient class.
 * @param parent
 */
RPLDClient::RPLDClient(QObject *parent) :
    QObject(parent)
{
    this->tcpSocket = new QTcpSocket(this);
    //connect(this->tcpSocket, SIGNAL(connected()), this, SLOT(connected()));
    //connect(this->tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(this->tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(socketStatusChanged(QAbstractSocket::SocketState)));
}

void RPLDClient::connectToServer(QString address)
{
    this->tcpSocket->connectToHost(QHostAddress(address), 8888);
}

/*
RPLDClient::ConnectionStatus RPLDClient::getConnectionStatus()
{
    if (this->tcpSocket->state() == QTcpSocket::ConnectedState) {
        return RPLDClient::CONNECTED;
    } else {
        return RPLDClient::DISCONNECTED;
    }
}
*/

void RPLDClient::sendSetting(QString settingName, QVariant value)
{
    //this->tcpSocket->write(value.toString().toAscii());

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << (quint16)0;
    out << settingName << value;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    this->tcpSocket->write(block);
}

void RPLDClient::connected()
{
    //emit this->statusChanged(RPLDClient::CONNECTED);
}

void RPLDClient::disconnected()
{
    //emit this->statusChanged(RPLDClient::DISCONNECTED);
}

void RPLDClient::socketStatusChanged(QAbstractSocket::SocketState state)
{
    switch (state) {
    case QAbstractSocket::UnconnectedState:
    case QAbstractSocket::ClosingState:
        emit this->statusChanged(RPLDClient::DISCONNECTED);
        break;
    case QAbstractSocket::ListeningState:
    case QAbstractSocket::BoundState:
    case QAbstractSocket::ConnectedState:
        emit this->statusChanged(RPLDClient::CONNECTED);
        break;
    case QAbstractSocket::ConnectingState:
    case QAbstractSocket::HostLookupState:
        emit this->statusChanged(RPLDClient::CONNECTING);
    }
}
