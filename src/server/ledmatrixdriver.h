/**
 * Concrete implementation of the LEDDriver class for the 32x32 LED Matrices available
 * from Adafruit.
 */

#ifndef LEDMATRIXDRIVER_H
#define LEDMATRIXDRIVER_H

#include "leddriver.h"
#include <cstdint>

/**
 * @brief The LEDMatrixDriver class
 */
class LEDMatrixDriver : public LEDDriver
{
public:
    int OutputFrame(uint8_t (**frame)[3], unsigned long width, unsigned long height);
    void SetMatrixConfig(int **config, unsigned int width, unsigned int height);
};

#endif // LEDMATRIXDRIVER_H
