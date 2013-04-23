/**
 * Defines the ScrollingTextDisplay class. This class uses a LEDDriver class
 * to display scrolling text.
 */

#ifndef SCROLLINGTEXTDISPLAY_H
#define SCROLLINGTEXTDISPLAY_H

#include <QObject>
#include <QTimer>
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
    //explicit ScrollingTextDisplay(LEDDriver *driver, unsigned long width, unsigned long height, QObject *parent = 0);
    explicit ScrollingTextDisplay(unsigned long width, unsigned long height, QObject *parent = 0);
    ~ScrollingTextDisplay();

private:
    void writeCharacter(QChar character, int offset);
    int calculateBufferOffset(unsigned long x, unsigned long y);

signals:
    void finished();
    
public slots:
    void start();
    void stop();
    void setText(QString text);
    void setColor(unsigned char red, unsigned char green, unsigned char blue);
    void setScrollingSpeed(int speed);
    void setWidth(unsigned long width);
    void setHeight(unsigned long height);
    QString getText();
    void getColor(unsigned char &red, unsigned char &green, unsigned char &blue);
    int getScrollingSpeed();
    unsigned long getWidth();
    unsigned long getHeight();


signals:
    void updateFrame(uint8_t *frame, unsigned long width, unsigned long height);

private slots:
    void update();

private:
    //LEDDriver *driver;
    unsigned long width;
    unsigned long height;
    QTimer *timer;
    uint8_t *buffer;
    QString text;
    unsigned char colorRed;
    unsigned char colorGreen;
    unsigned char colorBlue;
    int scrollingSpeed;
    double currentOffset;
    int maxOffset;

    // This structure describes a single character's display information
    typedef struct
    {
        const uint8_t widthBits;                // width, in bits (or pixels), of the character
        const uint16_t offset;					// offset of the character's bitmap, in bytes, into the the FONT_INFO's data array

    } FONT_CHAR_INFO;

    // Describes a single font
    typedef struct
    {
        const uint8_t 			heightPages;	// height, in pages (8 pixels), of the font's characters
        const uint8_t 			startChar;		// the first character in the font (e.g. in charInfo and data)
        const uint8_t 			endChar;		// the last character in the font
        const FONT_CHAR_INFO*	charInfo;		// pointer to array of char information
        const uint8_t*			data;			// pointer to generated array of character visual representation
    } FONT_INFO;

    static const uint8_t fontBitmaps[];
    static const FONT_INFO fontInfo;
    static const FONT_CHAR_INFO fontCharInfo[];
};

#endif // SCROLLINGTEXTDISPLAY_H
