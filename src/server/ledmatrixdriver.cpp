/**
 * Implementation of the LEDMatrixDriver class.
 */

#include "ledmatrixdriver.h"
#include <iostream>

/**
 * @brief Implementation of the OutputFrame function for the 32x32 LED Matrices available
 *        from Adafruit. It works by constantly shifting out data to the matrix (or matrices)
 *        in a seperate thread. The seperate thread is required because this function must
 *        guarantee that the frame is constantly shown and only two rows can actually be
 *        shown at a time. So the rows must be iterated through fast enough for the eye to
 *        not be able to percieve it.
 * @param width The width the output frame.
 * @param height The height of the output frame.
 * @return If an error occured it returns a nonzero integer, otherwise it returns 0.
 */
int LEDMatrixDriver::OutputFrame(uint8_t (**frame)[3], unsigned long width, unsigned long height)
{
    std::cout << "Output Frame" << std::endl;

    return 0;
}

/**
 * @brief LEDMatrixDriver::SetMatrixConfig
 * @param config This is a two dimensional array of LED matrix indices. Each integer corresponds
 *        to the index of LED matrix in the chain of LED matrices, starting with zero. The
 *        innermost array is the columns and the outermost array is the rows. If a LED matrix is
 *        not present in a spot in the two dimensional array, then a -1 is used. For example, a
 *        horizontal line of four LED matrices could be displayed as:
 *          @code{.cpp} int config[4][1] = {{0}, {1}, {2}, {3}}; @endcode
 *        A vertical line of four LED matrices could be displayed as:
 *          @code{.cpp} int config[1][4] = {{0, 1, 2, 3}} @endcode
 *        And a diagonal line as:
 *          @code{.cpp} int config[4][4] = {{0,-1,-1,1},{-1,1,-1,-1},{-1,-1,2,-1},{-1,-1,-1,3}} @endcode
 *        This function will free the memory in config by calling the free() function.
 * @param width
 * @param height
 */
void LEDMatrixDriver::SetMatrixConfig(int **config, unsigned int width, unsigned int height)
{

}
