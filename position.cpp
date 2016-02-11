#include "position.h"

Position::Position() :
    x(0),y(0)
{
}

Position::Position(int x, int y) :
    x(x), y(y)
{
}

Position::Position(const Position &p) :
    x(p.x), y(p.y)
{
}

void Position::setXY(int X, int Y)
{
    x = X;
    y = Y;
}

void Position::setXY(const Position &p)
{
    x = p.x;
    y = p.y;
}

void Position::setX(int X)
{
    x = X;
}

void Position::setY(int Y)
{
    y = Y;
}


int Position::getX() const
{
    return x;
}

int Position::getY() const
{
    return y;
}

bool Position::operator ==(const Position &pos) const
{
    if (pos.x != x) return false;
    if (pos.y != y) return false;
    return true;
}

bool Position::operator !=(const Position &pos) const
{
    return !(pos == *this);
}

