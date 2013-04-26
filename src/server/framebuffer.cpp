#include "framebuffer.h"

FrameBuffer::FrameBuffer(int width, int height, QObject *parent) :
    QObject(parent)
{
    this->width = width;
    this->height = height;
}

void FrameBuffer::setWidth(int width)
{
    this->width = width;
}

void FrameBuffer::setHeight(int height)
{
    this->height = height;
}

int FrameBuffer::getWidth()
{
    return this->width;
}

int FrameBuffer::getHeight()
{
    return this->height;
}

void FrameBuffer::setPixel(int x, int y, unsigned char red, unsigned char green, unsigned char blue)
{

}
