#ifndef RPLDCLIENT_H
#define RPLDCLIENT_H

#include "rpldcommunications_global.h"
#include <QObject>
#include <QTcpSocket>

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
    //ConnectionStatus getConnectionStatus();
    void sendSetting(QString settingName, QVariant value);

signals:
    void statusChanged(RPLDClient::ConnectionStatus status);

private slots:
    void connected();
    void disconnected();
    void socketStatusChanged(QAbstractSocket::SocketState state);

private:
    QTcpSocket *tcpSocket;
    
};

#endif // RPLDCLIENT_H
