/*!
 * Implementation of the ScrollingTextDisplay class.
 */
#include "scrollingtextdisplay.h"
#include <iostream>

/*!
 * \brief
 * \param parent
 */
ScrollingTextDisplay::ScrollingTextDisplay(QObject *parent) :
    QObject(parent)
{

}

/*!
 * \brief Starts displaying the scrolling text.
 */
void ScrollingTextDisplay::start()
{
    for (int i = 0; i < 10; i++) {
        std::cout << "Calculating frame and outputting..." << std::endl;
    }
}
