#include "snake.h"

Snake::Snake()
    : initialSnakeLength(0)
{
}

Snake::Snake(const QList<Snake_cell> &snakeList, const Direction &dir) :
    snakeList(snakeList), dir(dir), initialSnakeLength(0)
{
}

Snake::Snake(const Snake &snake) :
    snakeList(snake.snakeList), dir(snake.dir), initialSnakeLength(snake.initialSnakeLength)
{
}

void Snake::setDirection(const Direction &direction, const Size &fieldSize)
{
    if (getSnakeLength() < 2)
    {
        dir = direction;
        return;
    }

    Position nextPos = changePosition(snakeList[0].pos, direction, fieldSize);
    if (snakeList[1].pos != nextPos) dir = direction;
}

bool Snake::move(const Size &fieldSize)
{
    if (snakeList.isEmpty()) return false;
    Snake_cell &head = snakeList[0];
    Snake_cell new_head(Snake::changePosition(head.pos, dir, fieldSize));
    snakeList.push_front(new_head);
    snakeList.removeLast();
    return true;
}

bool Snake::eat(const Size &fieldSize)
{
    if (snakeList.isEmpty()) return false;
    Snake_cell &head = snakeList[0];
    Snake_cell new_cell(Snake::changePosition(head.pos, dir, fieldSize));
    snakeList.push_front(new_cell);
    return true;
}

Position Snake::getNextHeadPosition(const Size &fieldSize)
{
    if (snakeList.isEmpty()) return Position();
    Snake_cell &head = snakeList[0];
    return changePosition(head.pos, dir, fieldSize);
}

int Snake::getSnakeLength() const
{
    return snakeList.count();
}

void Snake::setInitialSnakeLength(int initialSnakeLength)
{
    this->initialSnakeLength = initialSnakeLength;
}

int Snake::getInitialSnakeLength() const
{
    return initialSnakeLength;
}

const Snake_cell &Snake::getSnakeCell(int cellNum) const
{
    return snakeList[cellNum];
}

void Snake::createHead(const Position &pos)
{
    if (getSnakeLength() == 0) snakeList.append(Snake_cell(pos));
}

void Snake::cutTail()
{
    if (getSnakeLength() > 0) snakeList.removeLast();
}

Direction Snake::getDir() const
{
    return dir;
}

Position Snake::changePosition(const Position &pos, const Direction &dir, const Size &fieldSize)
{
    switch (dir)
    {
    case Up:
        if (pos.getY() <= 0) return Position(pos.getX(), fieldSize.getH() - 1);
        return Position(pos.getX(), pos.getY() - 1);
    case Down:
        if (pos.getY() >= fieldSize.getH() - 1) return Position(pos.getX(), 0);
        return Position(pos.getX(), pos.getY() + 1);
    case Left:
        if (pos.getX() <= 0) return Position(fieldSize.getW() - 1, pos.getY());
        return Position(pos.getX() - 1, pos.getY());
    case Right:
        if (pos.getX() >= fieldSize.getW() - 1) return Position(0, pos.getY());
        return Position(pos.getX() + 1, pos.getY());
    }
    return pos;
}

