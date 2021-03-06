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
    void dataReady();

public slots:
    void returnSettingValue(QString settingName, QVariant value);

signals:
    void recievedSetting(QString settingName, QVariant value);
    void settingRequested(QString settingName);

private:
  QTcpServer *server;
  QTcpSocket *client;
  quint16 messageSize;
  bool recievingMessage;
};

#endif // RPLDSERVER_H
