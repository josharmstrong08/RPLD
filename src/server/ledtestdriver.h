#ifndef LEDTESTDRIVER_H
#define LEDTESTDRIVER_H

#include "leddriver.h"
#include <QObject>

class LEDTestDriver : public LEDDriver
{
public:
    explicit LEDTestDriver(QObject *parent=0);
    virtual int OutputFrame(uint8_t *frame, unsigned long width, unsigned long height);
};

#endif // LEDTESTDRIVER_H
