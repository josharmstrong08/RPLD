#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <QObject>

class FrameBuffer : public QObject
{
    Q_OBJECT
public:
    explicit FrameBuffer(int width, int height, QObject *parent = 0);
    
    void setWidth(int width);
    void setHeight(int height);
    int getWidth();
    int getHeight();
    void setPixel(int x, int y, unsigned char red, unsigned char green, unsigned char blue);

signals:
    
public slots:

private:
    int width;
    int height;
    
};

#endif // FRAMEBUFFER_H
