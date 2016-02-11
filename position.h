#ifndef POSITION_H
#define POSITION_H


class Position
{
    int x, y;

public:

    Position();
    Position(int x, int y);
    Position(const Position &p);

    void setXY(int X, int Y);
    void setXY(const Position &p);
    void setX(int X);
    void setY(int Y);

    int getX() const;
    int getY() const;

    bool operator == (const Position &pos) const;
    bool operator != (const Position &pos) const;
};

#endif // POSITION_H
