#include "size.h"

Size::Size() :
    width(0), height(0)
{    
}

Size::Size(int w, int h) :
    width(w), height(h)
{
}

Size::Size(const Size &s):
    width(s.width), height(s.height)
{
}

void Size::setWH(int W, int H)
{
    width = W;
    height = H;
}

void Size::setWH(const Size &s)
{
    width = s.width;
    height = s.height;
}

void Size::setW(int W)
{
    width = W;
}

void Size::setH(int H)
{
    height = H;
}

int Size::getW() const
{
    return width;
}

int Size::getH() const
{
    return height;
}

