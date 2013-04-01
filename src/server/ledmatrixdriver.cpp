/*!
 * Implementation of the LEDMatrixDriver class.
 */

#include "ledmatrixdriver.h"
#include <iostream>

/*!
 * \brief Implementation of the OutputFrame function for the 32x32 LED Matrices available
 *        from Adafruit. It works by constantly shifting out data to the matrix (or matrices)
 *        in a seperate thread. The seperate thread is required because this function must
 *        guarantee that the frame is constantly shown and only two rows can actually be
 *        shown at a time. So the rows must be iterated through fast enough for the eye to
 *        not be able to percieve it.
 * \param width The width the output frame.
 * \param height The height of the output frame.
 * \return If an error occured it returns a nonzero integer, otherwise it returns 0.
 */
int LEDMatrixDriver::OutputFrame(uint8_t (**frame)[3], unsigned long width, unsigned long height)
{
    std::cout << "Output Frame" << std::endl;

    return 0;
}
