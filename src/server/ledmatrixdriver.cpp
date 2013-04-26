/**
 * Implementation of the LEDMatrixDriver class.
 */

#include "ledmatrixdriver.h"
#ifndef USE_STD_OUT
#include <wiringPi.h>
#endif
#include <QDebug>
#include <QObject>
#include <QThread>
#include <cstdint>

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

#define CALC_BUFFER_OFFSET(X,Y,WIDTH) ((((Y) * (WIDTH)) * 3) + ((X) * 3))

/**
 * @brief LEDMatrixDriver::LEDMatrixDriver
 */
LEDMatrixDriver::LEDMatrixDriver(QObject *parent) :
    LEDDriver(parent)
{
#ifndef USE_STD_OUT
    wiringPiSetup();

    piHiPri(0); 

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

    this->matrixCount = 1;
    this->buffer = new uint8_t[32 * 32 * 1 * 3]();
    this->nextbuffer = this->buffer;
    this->timer = new QTimer(this);
    connect(this->timer, SIGNAL(timeout()), this, SLOT(output()));
    this->currentRow = 0;
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
int LEDMatrixDriver::outputFrame(uint8_t *frame, unsigned long width, unsigned long height)
{
    if (height != 32 || width % 32 != 0) {
        qDebug() << "only horizontals";
        throw "Only horizontal configurations are supported.";
    }
    if (width != (unsigned long)this->matrixCount * 32) {
        qDebug() << "frame size does not match";
        throw "Frame size does not match matrix configuration.";
    }

    memcpy(this->nextbuffer, frame, sizeof(uint8_t) * width * height * 3);

    return 0;
}

void LEDMatrixDriver::start()
{
    // Start the timer
    this->timer->start(1);
}

void LEDMatrixDriver::stop()
{
    // Stop the timer
    this->timer->stop();
}

/**
 * @brief Writes one new row of information from the buffer to the led matrices.
 */
void LEDMatrixDriver::output()
{
#ifndef USE_STD_OUT
    digitalWrite(OE, HIGH);
    // select the row
    digitalWrite(A, this->currentRow & 0x01);
    digitalWrite(B, this->currentRow & 0x02);
    digitalWrite(C, this->currentRow & 0x04);
    digitalWrite(D, this->currentRow & 0x08);

    // unlatch
    digitalWrite(LAT, LOW);

    // Clock in some data
    int column;
    int width = this->matrixCount * 32;
    for (column = 0; column < width; column++) {
        uint8_t pixel1r = this->buffer[CALC_BUFFER_OFFSET(column, this->currentRow, width) + 0];
        uint8_t pixel1g = this->buffer[CALC_BUFFER_OFFSET(column, this->currentRow, width) + 1];
        uint8_t pixel1b = this->buffer[CALC_BUFFER_OFFSET(column, this->currentRow, width) + 2];
        uint8_t pixel2r = this->buffer[CALC_BUFFER_OFFSET(column, this->currentRow + 16, width) + 0];
        uint8_t pixel2g = this->buffer[CALC_BUFFER_OFFSET(column, this->currentRow + 16, width) + 1];
        uint8_t pixel2b = this->buffer[CALC_BUFFER_OFFSET(column, this->currentRow + 16, width) + 2];

        pixel1r = pixel1r < 128 ? 0 : 1;
        pixel1g = pixel1g < 128 ? 0 : 1;
        pixel1b = pixel1b < 128 ? 0 : 1;
        pixel2r = pixel2r < 128 ? 0 : 1;
        pixel2g = pixel2g < 128 ? 0 : 1;
        pixel2b = pixel2b < 128 ? 0 : 1;

        digitalWrite(R1, pixel1r);
        digitalWrite(G1, pixel1g);
        digitalWrite(B1, pixel1b);
        digitalWrite(R2, pixel2r);
        digitalWrite(G2, pixel2g);
        digitalWrite(B2, pixel2b);

        // Pulse the clock
        digitalWrite(SCLK, LOW);
        digitalWrite(SCLK, HIGH);
    }

    // Increment row
    this->currentRow++;
    if (this->currentRow == 16) {
        uint8_t *temp = this->buffer;
        this->buffer = this->nextbuffer;
        this->nextbuffer = temp;

        this->currentRow = 0;
    }

    // latch
    digitalWrite(LAT, HIGH);
    //digitalWrite(LAT, LOW);
    digitalWrite(OE, LOW);
#endif
}

void LEDMatrixDriver::SetMatrixCount(int count)
{
    qDebug() << "Setting new matrix count: " << count;
    this->buffer = new uint8_t[32 * 32 * count * 3]();
    this->matrixCount = count;
}

int LEDMatrixDriver::GetMatrixCount()
{
    return this->matrixCount;
}
