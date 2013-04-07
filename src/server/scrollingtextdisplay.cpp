/**
 * Implementation of the ScrollingTextDisplay class.
 */
#include "scrollingtextdisplay.h"
#include "leddriver.h"

/**
 * @brief Initializes a new instance of the @see ScrollingTextDisplay class.
 * @param parent
 */
ScrollingTextDisplay::ScrollingTextDisplay(LEDDriver *driver, QObject *parent) :
    QObject(parent)
{
    this->driver = driver;
}

/**
 * @brief Starts displaying the scrolling text.
 */
void ScrollingTextDisplay::start()
{
    for (int i = 0; i < 10; i++) {
        std::cout << "Calculating frame and outputting..." << std::endl;
    }
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
void ScrollingTextDisplay::setColor(QColor color)
{
    this->textColor = color;
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
