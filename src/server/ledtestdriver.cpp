#include "ledtestdriver.h"

#include <iostream>

/**
 * @brief LEDTestDriver::OutputFrame
 * @param width
 * @param height
 * @return
 */
int LEDTestDriver::OutputFrame(uint8_t (**frame)[3], unsigned long width, unsigned long height)
{
    for (unsigned long x = 0; x < width; x++) {
        for (unsigned long y = 0; y < height; y++) {
            std::cout << "(" << frame[x][y][0] << "," << frame[x][y][1] << "," << frame[x][y][2] << ") ";
        }

        std::cout << std::endl;
    }

    return 0;
}
