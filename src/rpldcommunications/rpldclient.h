#ifndef RPLDCLIENT_H
#define RPLDCLIENT_H

#include "rpldcommunications_global.h"
#include <QObject>
#include <QTcpSocket>
#include <QHostInfo>

class RPLDCOMMUNICATIONSSHARED_EXPORT RPLDClient : public QObject
{
    Q_OBJECT
public:
    enum ConnectionStatus {
        CONNECTING,
        CONNECTED,
        DISCONNECTED
    };

public:
    explicit RPLDClient(QObject *parent = 0);
    void connectToServer(QString address);
    void disconnectFromServer();
    void sendSetting(QString settingName, QVariant value);
    void requestSetting(QString settingName);
    const QString errorString();

signals:
    /**
     * @brief This signal is emitted whenever the state of the client changes.
     *   Connect to this signal to know when the connecToServer function succeeds
     *   or fails.
     * @param status The new connection status.
     */
    void statusChanged(RPLDClient::ConnectionStatus status);
    void recievedSetting(QString settingName, QVariant settingValue);

private slots:
    void socketStatusChanged(QAbstractSocket::SocketState state);
    void dataReady();

private:
    /**
     * @brief The tcp socket that is being used.
     */
    QTcpSocket *tcpSocket;
    quint16 messageSize;
    
};

#endif // RPLDCLIENT_H
