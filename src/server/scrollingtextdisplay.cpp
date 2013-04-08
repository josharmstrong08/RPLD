/**
 * Implementation of the ScrollingTextDisplay class.
 */

#include "scrollingtextdisplay.h"
#include "leddriver.h"
#include <QThread>
#include <QDebug>
#include <stdint.h>
#include <iostream>


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
    this->buffer = new uint8_t [width * height * 3];

    // Testing accessing a single character
    // The offset into the bitmap array of the character
    uint16_t charOffset = this->fontInfo.charInfo['A' - this->fontInfo.startChar].offset;
    // The width of the character in bits (in other words, how many pixels wide it is).
    int bitmapWidth = this->fontInfo.charInfo['A' - this->fontInfo.startChar].widthBits;

    int xPageCount, yPageCount;
    if (bitmapWidth % 8 == 0) {
        xPageCount = bitmapWidth / 8;
    } else {
        xPageCount = (bitmapWidth / 8) + 1;
    }
    yPageCount = this->fontInfo.heightPages * 8;

    for (int y = 0; y < yPageCount; y++) {
        for (int x = 0; x < xPageCount; x++) {
            // Output a byte
            uint8_t byte = this->fontInfo.data[charOffset + y * xPageCount + x];
            //std::cout << byte;
            for (int z = 0; z < 8; z++) {
                if ((byte & 0x80) == 0x80) {
                    std::cout << "#";
                } else {
                    std::cout << " ";
                }
                byte <<= 1;
            }
        }
        std::cout << "\n";
    }
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
 * returned.
 */
void ScrollingTextDisplay::start()
{
    qDebug() << "Scrolling text display started (thread " << QThread::currentThreadId() << ")";
    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    //this->timer->start(33);
}

/**
 * @brief Outputs a frame and calculates the next frame.
 */
void ScrollingTextDisplay::update()
{
    qDebug() << "Frame output";
    //this->driver->OutputFrame(this->buffer, 32, 32);
}

/**
 * @brief Stop
 */
void ScrollingTextDisplay::stop()
{

}

/**
 * @brief ScrollingTextDisplay::setText
 * @param text The text to display.
 */
void ScrollingTextDisplay::setText(QString text)
{
    this->text = text;
}

/**
 * @brief ScrollingTextDisplay::setColor
 * @param color The new text color. The actual color displayed is dependent
 *              on the hardware and driver.
 */
//void ScrollingTextDisplay::setColor(QColor color)
//{
//    this->textColor = color;
//}

/**
 * @brief Sets the text scrolling speed.
 * @param speed The speed to scroll the text at, in pixels per millisecond.
 *              Values can be positive or negative.
 */
void ScrollingTextDisplay::setScrollingSpeed(int speed)
{
    this->scrollingSpeed = speed;
}
