#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QVariant>
#include "scrollingtextdisplay.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    
signals:
    
private slots:
    void recievedSetting(QString settingName, QVariant value);

private:
    ScrollingTextDisplay *display;
    LEDDriver *driver;
};

#endif // SERVER_H
