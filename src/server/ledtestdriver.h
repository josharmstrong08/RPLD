#ifndef LEDTESTDRIVER_H
#define LEDTESTDRIVER_H

#include "leddriver.h"
#include <QObject>
#include <cstdint>
#include <QTimer>

class LEDTestDriver : public LEDDriver
{
    Q_OBJECT
public:
    explicit LEDTestDriver(QObject *parent=0);

public slots:
    int outputFrame(uint8_t *frame, unsigned long width, unsigned long height);
    void start();
    void stop();

private slots:
    void output();

private:
    uint8_t *buffer;
    unsigned long width;
    unsigned long height;
    QTimer *timer;
};

#endif // LEDTESTDRIVER_H
