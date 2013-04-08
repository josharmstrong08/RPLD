#ifndef LEDTESTDRIVER_H
#define LEDTESTDRIVER_H

#include "leddriver.h"

class LEDTestDriver : public LEDDriver
{
public:
    virtual int OutputFrame(uint8_t (**frame)[3], unsigned long width, unsigned long height);
};

#endif // LEDTESTDRIVER_H
