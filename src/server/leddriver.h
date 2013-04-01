#ifndef LEDDRIVER_H
#define LEDDRIVER_H

#include <cstdint>

class LEDDriver
{
public:
    virtual int OutputFrame(uint8_t (**frame)[3], unsigned long width, unsigned long height) =0;
};

#endif // LEDDRIVER_H
