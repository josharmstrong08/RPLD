/*!
 * Defines the ScrollingTextDisplay class. This class uses a LEDDriver class
 * to display scrolling text.
 */
#ifndef SCROLLINGTEXTDISPLAY_H
#define SCROLLINGTEXTDISPLAY_H

#include <QObject>

/*!
 * \brief The ScrollingTextDisplay class.
 */
class ScrollingTextDisplay : public QObject
{
    Q_OBJECT
public:
    explicit ScrollingTextDisplay(QObject *parent = 0);
    
signals:
    
public slots:
    void start();
};

#endif // SCROLLINGTEXTDISPLAY_H
