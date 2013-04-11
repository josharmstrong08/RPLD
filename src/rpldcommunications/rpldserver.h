#ifndef RPLDSERVER_H
#define RPLDSERVER_H

#include "rpldcommunications_global.h"
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class RPLDCOMMUNICATIONSSHARED_EXPORT RPLDServer : public QObject
{
    Q_OBJECT
public:
    explicit RPLDServer(QObject *parent = 0);
    ~RPLDServer();

private slots:
    void acceptConnection();
    void startRead();

signals:
    void recievedSetting(QString settingName, QVariant value);

private:
  QTcpServer *server;
  QTcpSocket *client;
    
};

#endif // RPLDSERVER_H