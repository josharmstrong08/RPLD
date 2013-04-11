/**
 * Implementation of the ScrollingTextDisplay class.
 */

#include "scrollingtextdisplay.h"
#include "leddriver.h"
#include <QThread>
#include <QDebug>
#include <stdint.h>
#include <iostream>
#include <cassert>

/**
 * @brief Initializes a new instance of the ScrollingTextDisplay class.
 *
 * @param driver An instance of a LEDDriver class to provide a OutputFrame function. This class will
 *        be deleted in the class destructor.
 * @param width The number of horizontal pixels available.
 * @param height The number of vertical pixel available.
 * @param parent The Qt parent.
 */
ScrollingTextDisplay::ScrollingTextDisplay(LEDDriver *driver, unsigned long width, unsigned long height, QObject *parent) :
    QObject(parent)
{
    this->driver = driver;
    this->width = width;
    this->height = height;
    this->buffer = new uint8_t [width * height * 3]();
    this->currentOffset = 0;
    this->maxOffset = this->width;
    this->text = "";
    this->scrollingSpeed = 0;
}

/**
 * @brief ScrollingTextDisplay::~ScrollingTextDisplay
 */
ScrollingTextDisplay::~ScrollingTextDisplay()
{
    //delete this->driver;
}

/**
 * @brief Starts displaying the scrolling text.
 *
 * This function cause frames to start updating. Control is immediately
 * returned. This function is meant to be entry point of a new thread.
 */
void ScrollingTextDisplay::start()
{
    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    this->timer->start(33);
}

/**
 * @brief Outputs a frame and calculates the next frame. This frame is expected to be called
 *   once every 33 milliseconds (30 times per second).
 */
void ScrollingTextDisplay::update()
{
    // Display the frame--------------------------------------------------
    this->driver->OutputFrame(this->buffer, this->width, this->height);

    // Scroll ------------------------------------------------------------
    // TODO Adjust with scrolling speed here
    this->currentOffset -= 33 / 1000.0 * (double)this->scrollingSpeed;
    if (this->currentOffset <= this->maxOffset) {
        this->currentOffset = 0;
    }

    // Create the next frame for next update -----------------------------
    for (unsigned long i = 0; i < this->width * this->height * 3; i++) {
        this->buffer[i] = 0x00;
    }

    int tempOffset = this->currentOffset;
    for (int i = 0; i < this->text.length(); i++) {
        int bitmapWidth = this->fontInfo.charInfo[this->text[i].toLatin1() - this->fontInfo.startChar].widthBits;
        this->writeCharacter(this->text[i], tempOffset);
        tempOffset += bitmapWidth + 5;
    }
}

/**
 * @brief Writes a character to the buffer at the specified offset.
 *
 * This function assumes that the buffer has been cleared already. It will only
 * write within the bounds of the buffer. It uses the currently set color to
 * draw the character. The offset is the number of pixels from the left side
 * of the frame to start drawing. It will always start drawing at the top of the
 * frame.
 *
 * @param character The character to write out.
 * @param offset The offset from the left hand side to write at.
 */
void ScrollingTextDisplay::writeCharacter(QChar character, int offset)
{
    // The offset into the bitmap array of the character
    uint16_t charOffset = this->fontInfo.charInfo[character.toLatin1() - this->fontInfo.startChar].offset;
    // The width of the character in bits (in other words, how many pixels wide it is).
    int bitmapWidth = this->fontInfo.charInfo[character.toLatin1() - this->fontInfo.startChar].widthBits;

    // Get the number of bytes that the character uses, based on the width in pixels of the
    // character.
    int xByteCount;
    if (bitmapWidth % 8 == 0) {
        xByteCount = bitmapWidth / 8;
    } else {
        xByteCount = (bitmapWidth / 8) + 1;
    }

    // Set the max y value to the the height of the character in pixels,
    // or the height of the display, whichever is smaller.
    int yMax = qMin((unsigned long)(this->fontInfo.heightPages * 8), this->height);

    // Write the character to the buffer
    for (int y = 0; y < yMax; y++) {
        for (int xByte = 0; xByte < xByteCount; xByte++) {
            // Get a byte
            uint8_t byte = this->fontInfo.data[charOffset + y * xByteCount + xByte];

            for (int z = 0; z < 8; z++) {
                int x = xByte * 8 + z;
                if (x + offset >= 0 && x + offset < (signed long long)this->width) {
                    int index = this->calculateBufferOffset(x + offset, y);
                    if ((byte & 0x80) == 0x80) {
                        this->buffer[index + 0] = this->colorRed;
                        this->buffer[index + 1] = this->colorGreen;
                        this->buffer[index + 2] = this->colorBlue;
                    }
                }

                byte <<= 1;
            }
        }
    }
}

/**
 * @brief Calculates the index into the buffer of the given pixel at (x,y). The
 *   buffer is row-major order with each pixel taking three items (a byte) in the
 *   array.
 * @param x The x position of the pixel
 * @param y The y position of the pixel
 * @return A valid index into this->buffer.
 */
int ScrollingTextDisplay::calculateBufferOffset(unsigned long x, unsigned long y)
{
    assert(x < this->width);
    assert(y < this->height);

    return y * this->width * 3 + x * 3;
}

/**
 * @brief Stop displaying.
 */
void ScrollingTextDisplay::stop()
{
    this->timer->stop();

    for (unsigned long i = 0; i < this->width * this->height * 3; i++) {
        this->buffer[i] = 0x00;
    }

    this->driver->OutputFrame(this->buffer, width, height);
}

/**
 * @brief Sets the text to display
 * @param text The text to display.
 */
void ScrollingTextDisplay::setText(QString text)
{
    this->text = text;
    this->maxOffset = 0;
    for (int i = 0; i < text.length(); i++) {
        this->maxOffset -= this->fontInfo.charInfo[text[i].toLatin1() - this->fontInfo.startChar].widthBits + 5;
    }
    this->currentOffset = 0;
}

/**
 * @brief Sets the color of the scrolling text.
 * @param color The new text color. The actual color displayed is dependent
 *              on the hardware and driver.
 */
void ScrollingTextDisplay::setColor(unsigned char red, unsigned char green, unsigned char blue)
{
    this->colorRed = red;
    this->colorGreen = green;
    this->colorBlue = blue;
}

/**
 * @brief Sets the text scrolling speed.
 * @param speed The speed to scroll the text at, in pixels per millisecond.
 *              Values can be positive or negative.
 */
void ScrollingTextDisplay::setScrollingSpeed(int speed)
{
    this->scrollingSpeed = speed;
}
