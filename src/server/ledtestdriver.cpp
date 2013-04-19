#include "ledtestdriver.h"
#include <iostream>
#include <cstdint>


LEDTestDriver::LEDTestDriver(QObject *parent)
    : LEDDriver(parent)
{
    // Setup initial default values
    this->width = 32;
    this->height = 32;
    this->buffer = new uint8_t(this->width * this->height * 3);
    this->timer = new QTimer(this);
}

/**
 * @brief Writes a frame to stdout, after print 80 new lines to clear the screen.
 * @param frame The frame in row-major order with three bytes per pixel.
 * @param width The width of the frame
 * @param height the height of the frame
 * @return Always returns 0 for success.
 */
int LEDTestDriver::outputFrame(uint8_t *frame, unsigned long width, unsigned long height)
{
    this->width = width;
    this->height = height;
    this->buffer = frame;
    return 0;
}

void LEDTestDriver::start()
{
    // Start the timer with a 10 millisecond timeout rate.
    connect(this->timer, SIGNAL(timeout()), this, SLOT(output()));
    this->timer->start(10);
}

void LEDTestDriver::stop()
{
    // Do nothing
    this->timer->stop();
}

/**
 * @brief This slot should be connected a timer's timeout signal. It will
 *   write the current buffer to the screen.
 */
void LEDTestDriver::output()
{
    unsigned long i;
    for (i = 0 ; i < this->width * this->height * 3; i++) {
        if (this->buffer[i] > 0x00) {
            break;
        }
    }

    std::cout << "Color: (" << (int)this->buffer[i] << "," << (unsigned int)this->buffer[i+1] << "," << (unsigned short)this->buffer[i+2] << ")" << std::endl;
    std::cout << "+";
    for (unsigned long x = 0; x < this->width; x++) {
        std::cout << "-";
    }
    std::cout << "+" << std::endl;

    for (unsigned long y = 0; y < this->height; y++){
        std::cout << "|";
        for (unsigned long x = 0; x < this->width; x++) {
            if (this->buffer[y * (this->width * 3) + x * 3 + 0] > 0x00 ||
                this->buffer[y * (this->width * 3) + x * 3 + 1] > 0x00 ||
                this->buffer[y * (this->width * 3) + x * 3 + 2] > 0x00) {
                std::cout << "#";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "|" << std::endl;
    }

    std::cout << "+";
    for (unsigned long x = 0; x < this->width; x++) {
        std::cout << "-";
    }
    std::cout << "+" << std::endl;
}
