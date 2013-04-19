/**
 * Implementation of the LEDMatrixDriver class.
 */

#include "ledmatrixdriver.h"
#ifndef USE_STD_OUT
#include <wiringPi.h>
#endif
#include <QDebug>

#define OE      1
#define SCLK    16
#define LAT     4
#define A       2
#define B       6
#define C       15
#define D       5
#define R1      14
#define G1      11
#define B1      13
#define R2      12
#define G2      10
#define B2      3

/**
 * @brief LEDMatrixDriver::LEDMatrixDriver
 */
LEDMatrixDriver::LEDMatrixDriver(QObject *parent) :
    QObject(parent)
{
#ifndef USE_STD_OUT
    wiringPiSetup();

    pinMode(OE, OUTPUT);
    pinMode(SCLK, OUTPUT);
    pinMode(LAT, OUTPUT);
    pinMode(A, OUTPUT);
    pinMode(B, OUTPUT);
    pinMode(C, OUTPUT);
    pinMode(D, OUTPUT);

    pinMode(R1, OUTPUT);
    pinMode(G1, OUTPUT);
    pinMode(B1, OUTPUT);
    pinMode(R2, OUTPUT);
    pinMode(G2, OUTPUT);
    pinMode(B2, OUTPUT);

    digitalWrite(SCLK, LOW);
    digitalWrite(LAT, LOW);
    digitalWrite(OE, HIGH);
    digitalWrite(A, LOW);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
    digitalWrite(R1, LOW);
    digitalWrite(R2, LOW);
    digitalWrite(G1, LOW);
    digitalWrite(G2, LOW);
    digitalWrite(B1, LOW);
    digitalWrite(B2, LOW);
    digitalWrite(OE, LOW);
#endif
}

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
int LEDMatrixDriver::OutputFrame(uint8_t *frame, unsigned long width, unsigned long height)
{
    
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
 * 
 *        Currently this function only handles straight horizontal configurations.
 * @param width   The maximum width, in number of matrices.
 * @param height  The maximum height, in number of matrices. 
 */
void LEDMatrixDriver::SetMatrixConfig(int **config, unsigned int width, unsigned int height)
{
    if (height != 1) {
        throw "Matrices must all be in a horizontal row.";
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            qDebug() << "Config (" << x << "," << y << "): " << config[y][x];
        }
    }
  
    // Record the number of matrices
    this->matrixCount = width;    

    // Free the memory used by config
    for (int y = 0; y < height; y++) {
        free(config[y]);
    }
}

