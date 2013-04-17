/**
 * Definition of the LEDDriver abstract base class. This class defines an interface
 * for displaying an image on any LED display.
 */

#ifndef LEDDRIVER_H
#define LEDDRIVER_H

#include <cstdint>
#include <QObject>

/**
 * @brief The LEDDriver class
 */
class LEDDriver : public QObject
{
    Q_OBJECT
public:
    explicit LEDDriver(QObject *parent=0);
    virtual int OutputFrame(uint8_t *frame, unsigned long width, unsigned long height) =0;
};

#endif // LEDDRIVER_H
