/**
 * Implementation of the RPLDClient class. This class uses QTCPSocket and
 * QDataStream to communicate with the RPLDSettings class. This class can
 * send (and soon, request current) settings that are stored on the server.
 */

#include "rpldclient.h"
#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>

/**
 * @brief Initializes a new instance of the @see RPLDClient class. This does
 *   not connect to the server.
 * @param parent
 */
RPLDClient::RPLDClient(QObject *parent) :
    QObject(parent)
{
    this->tcpSocket = new QTcpSocket(this);
    connect(this->tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(socketStatusChanged(QAbstractSocket::SocketState)));
}

/**
 * @brief Tries to connect the server. This function will not block and will
 *   return immediately. Connect to the statusChanged signal to find out when
 *   the client is in the disconnected, connecting, and connected states.
 * @param address The address to connect to.
 */
void RPLDClient::connectToServer(QString address)
{
    emit this->statusChanged(RPLDClient::CONNECTING);
    this->tcpSocket->connectToHost(address, 8888);
}

/**
 * @brief Disconnects from the server. Not strictly necessary to use.
 */
void RPLDClient::disconnectFromServer()
{
    this->tcpSocket->disconnectFromHost();
}

/**
 * @brief If connected to the server, then this function will send a
 *   setting name and value. If an error occurs nothing happens.
 *   TODO Better error handling (what if disconnected...)
 * @param settingName The name of the setting to set.
 * @param value The new value of the setting.
 */
void RPLDClient::sendSetting(QString settingName, QVariant value)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << (quint16)0;
    out << settingName << value;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    this->tcpSocket->write(block);
}

/**
 * @brief Gets the latest error string, or an empty string if no error
 *   occured.
 * @return A string representation of the last error.
 */
const QString RPLDClient::errorString()
{
    if (this->tcpSocket->error() != QTcpSocket::UnknownSocketError) {
        return this->tcpSocket->errorString();
    } else {
        return QString("");
    }
}

/**

 * @brief This private socket recives socket state changes from the tcp socket.
 * @param state The new socket state.
 */
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
