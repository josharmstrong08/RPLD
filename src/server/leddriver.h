/**
 * Definition of the LEDDriver abstract base class. This class defines an interface
 * for displaying an image on any LED display.
 */

#ifndef LEDDRIVER_H
#define LEDDRIVER_H

#include <cstdint>

/**
 * @brief The LEDDriver class
 */
class LEDDriver
{
public:
    virtual int OutputFrame(uint8_t (**frame)[3], unsigned long width, unsigned long height) =0;
};

#endif // LEDDRIVER_H
