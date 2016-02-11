#ifndef SNAKE_H
#define SNAKE_H
#include "cell.h"
#include "direction.h"
#include <QList>
#include "position.h"
#include "size.h"


class Snake
{
    QList<Snake_cell> snakeList;
    Direction dir;
    int initialSnakeLength;

public:
    Snake();
    Snake(const QList<Snake_cell> &snakeList, const Direction &dir);
    Snake(const Snake &snake);

    void setDirection(const Direction &direction, const Size &fieldSize);

    bool move(const Size &fieldSize);
    bool eat(const Size &fieldSize);
    Position getNextHeadPosition(const Size &fieldSize);
    int getSnakeLength() const;
    void setInitialSnakeLength(int initialSnakeLength);
    int getInitialSnakeLength() const;
    const Snake_cell & getSnakeCell(int cellNum) const;
    void createHead(const Position &pos);
    void cutTail();
    Direction getDir() const;

private:
    static Position changePosition(const Position &pos, const Direction &dir, const Size &fieldSize);
};

#endif // SNAKE_H
