/**
 * Concrete implementation of the LEDDriver class for the 32x32 LED Matrices available
 * from Adafruit.
 */

#ifndef LEDMATRIXDRIVER_H
#define LEDMATRIXDRIVER_H

#include "leddriver.h"
#include <cstdint>
#include <QObject>

/**
 * @brief The LEDMatrixDriver class
 */
class LEDMatrixDriver : public LEDDriver, public QObject
{
    Q_OBJECT
public:
    explicit LEDMatrixDriver(QObject *parent = 0);
    int OutputFrame(uint8_t *frame, unsigned long width, unsigned long height);
    void SetMatrixConfig(int **config, unsigned int width, unsigned int height);

private:
    int matrixCount;
};

#endif // LEDMATRIXDRIVER_H
