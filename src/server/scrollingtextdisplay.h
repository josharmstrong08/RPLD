/**
 * Defines the ScrollingTextDisplay class. This class uses a LEDDriver class
 * to display scrolling text.
 */

#ifndef SCROLLINGTEXTDISPLAY_H
#define SCROLLINGTEXTDISPLAY_H

#include <QObject>
#include <QTimer>
//#include <QColor>
#include <stdint.h>
#include "leddriver.h"

/**
 * @brief The ScrollingTextDisplay class
 *
 */
class ScrollingTextDisplay : public QObject
{
    Q_OBJECT
public:
    explicit ScrollingTextDisplay(LEDDriver *driver, unsigned long width, unsigned long height, QObject *parent = 0);
    ~ScrollingTextDisplay();

private:
    LEDDriver *driver;
    unsigned long width;
    unsigned long height;
    QTimer *timer;
    uint8_t ***buffer;

signals:
    void finished();
    
private slots:
    void update();

public slots:
    void start();
    void stop();
    void setText(QString text);
    //void setColor(QColor color);
    void setScrollingSpeed(int speed);

private:
    QString text;
    //QColor textColor;
    int scrollingSpeed;
};

#endif // SCROLLINGTEXTDISPLAY_H
