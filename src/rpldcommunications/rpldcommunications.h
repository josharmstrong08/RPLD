#ifndef RPLDCOMMUNICATIONS_H
#define RPLDCOMMUNICATIONS_H

#include "rpldcommunications_global.h"
#include <QObject>
#include <QVariant>

class RPLDCOMMUNICATIONSSHARED_EXPORT RPLDCommunications : public QObject
{
    Q_OBJECT
public:
    enum ConnectionStatus {
        CONNECTED,
        DISCONNECTED
    };

    enum MessageStatus {
        SENT,
        NOTSENT
    };

public:
    ConnectionStatus connect();
    ConnectionStatus disconnect();
    MessageStatus sendSetting(QString settingName, QVariant value);

signals:
    void recievedSetting(QString settingName, QVariant value);
    void disconnected();

};

#endif // RPLDCOMMUNICATIONS_H
