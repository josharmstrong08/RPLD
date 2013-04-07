/**
 * Defines the ScrollingTextDisplay class. This class uses a LEDDriver class
 * to display scrolling text.
 */
#ifndef SCROLLINGTEXTDISPLAY_H
#define SCROLLINGTEXTDISPLAY_H

#include <QObject>
#include "leddriver.h"

/**
 * @brief The ScrollingTextDisplay class.
 */
class ScrollingTextDisplay : public QObject
{
    Q_OBJECT
public:
    explicit ScrollingTextDisplay(LEDDriver *driver, QObject *parent = 0);
    
signals:
    
public slots:
    void start();
    void stop();
    void setText(QString text);
    void setColor(QColor color);
    void setScrollingSpeed(int speed);

private:
    QString text;
    QColor textColor;
    int scrollingSpeed;
    LEDDriver *driver;
};

#endif // SCROLLINGTEXTDISPLAY_H
