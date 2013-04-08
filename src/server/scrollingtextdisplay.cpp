/**
 * Implementation of the ScrollingTextDisplay class.
 */

#include "scrollingtextdisplay.h"
#include "leddriver.h"
#include <QThread>
#include <QDebug>
#include <stdint.h>


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

    //this->buffer = (uint8_t(**)[3])malloc(sizeof(uint8_t) * 32 * 32 * 3);
    this->buffer = new uint8_t** [32];
    for (int i = 0; i < 32; i++) {
        this->buffer[i] = new uint8_t*[32];
        for (int j = 0; j < 3; j++) {
            this->buffer[i][j] = new uint8_t[3];
            this->buffer[i][j][0] = 0;
            this->buffer[i][j][1] = 1;
            this->buffer[i][j][2] = 2;
        }
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
    this->timer->start(33);
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
