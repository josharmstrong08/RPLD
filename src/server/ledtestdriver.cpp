#include "ledtestdriver.h"

#include <iostream>

/**
 * @brief LEDTestDriver::OutputFrame
 * @param width
 * @param height
 * @return
 */
int LEDTestDriver::OutputFrame(uint8_t *frame, unsigned long width, unsigned long height)
{
    for (int i = 0; i < 80; i++) {
        std::cout << std::endl;
    }

    for (unsigned long y = 0; y < 32; y++){
        for (unsigned long x = 0; x < 32; x++) {
            if (frame[y * (width * 3) + x * 3 + 0] == 0xff &&
                frame[y * (width * 3) + x * 3 + 1] == 0xff &&
                frame[y * (width * 3) + x * 3 + 2] == 0xff) {
            //if (frame[y * (width * 3) + x] == 0xff) {
                std::cout << "#";
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    return 0;
}
