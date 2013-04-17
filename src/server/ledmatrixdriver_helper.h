/**
 * A helper class for the led matrix driver that runs in a seperate thread 
 * and does the actual work in displaying images on the led matrices.
 */

#ifndef LEDMATRIXDRIVER_HELPER_H
#define LEDMATRIXDRIVER_HELPER_H

#include <QObject>

class LEDMatrixDriverHelper : public QObject
{
    Q_OBJECT
public:
    explicit LEDMatrixDriverHelper(QObject *parent = 0);

public slots:
    void start();
    void newFrame(uint8_t *frame, unsigned long width, unsigned long height);
};

#endif
