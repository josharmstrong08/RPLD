#ifndef LEDMATRIXDRIVER_H
#define LEDMATRIXDRIVER_H

#include "leddriver.h"
#include <cstdint>

class LEDMatrixDriver : public LEDDriver
{
public:
    int OutputFrame(uint8_t (**frame)[3], unsigned long width, unsigned long height);
};

#endif // LEDMATRIXDRIVER_H
