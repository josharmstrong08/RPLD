#include "ledtestdriver.h"

#include <iostream>

/**
 * @brief Writes a frame to stdout, after print 80 new lines to clear the screen.
 * @param frame The frame in row-major order with three bytes per pixel.
 * @param width The width of the frame
 * @param height the height of the frame
 * @return Always returns 0 for success.
 */
int LEDTestDriver::OutputFrame(uint8_t *frame, unsigned long width, unsigned long height)
{
    for (int i = 0; i < 80; i++) {
        std::cout << std::endl;
    }

    int i;
    for (i = 0 ; i < width * height * 3; i++) {
        if (frame[i] > 0x00) {
            break;
        }
    }

    std::cout << "Color: (" << (int)frame[i] << "," << (unsigned int)frame[i+1] << "," << (unsigned short)frame[i+2] << ")" << std::endl;
    std::cout << "+";
    for (unsigned long x = 0; x < width; x++) {
        std::cout << "-";
    }
    std::cout << "+" << std::endl;

    for (unsigned long y = 0; y < height; y++){
        std::cout << "|";
        for (unsigned long x = 0; x < width; x++) {
            if (frame[y * (width * 3) + x * 3 + 0] > 0x00 ||
                frame[y * (width * 3) + x * 3 + 1] > 0x00 ||
                frame[y * (width * 3) + x * 3 + 2] > 0x00) {
                std::cout << "#";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "|" << std::endl;
    }

    std::cout << "+";
    for (unsigned long x = 0; x < width; x++) {
        std::cout << "-";
    }
    std::cout << "+" << std::endl;

    return 0;
}
