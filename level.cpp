#include "level.h"


Level::Level(const Field &field, const Snake &snake,
           const QList<Beetle_cell> &beetles, const Port_cell &port, const int Beetle_num) :
    score_coeff(-1.667),
    max_score(100),
    startTimeCounter(-3),

    field(field),
    snake(snake),
    beetles(beetles),
    port(port),
    Beetle_num(Beetle_num),
    timeCounter(startTimeCounter)

{
}


void Level::incrementTimeCounter()
{
    timeCounter++;
}

int Level::getTimeCounter() const
{
    return timeCounter;
}

void Level::setTimeCounter(int value)
{
    timeCounter = value;
}

int Level::getScore() const
{
    if (timeCounter < 0) return max_score;

    int score;
    score = score_coeff * timeCounter + max_score;
    if (score < 0) score = 0;
    if (score > max_score) score = max_score;
    return score;
}

Position Level::generateBeetlePos() const
{
    const Size &fieldSize = field.getSize();

    while (true)
    {
        int x = rand() % fieldSize.getW();
        int y = rand() % fieldSize.getH();
        Position newBeetlePos(x, y);

        Cell *cell = field.getCell(newBeetlePos);
        if (cell == 0) continue;

        QString className = cell->metaObject()->className();
        if (className != "Field_cell") continue;

        bool success = true;
        for (int i = 0; i < beetles.count(); i++)
        {
            if (beetles[i].pos == newBeetlePos)
            {
                success = false;
                break;
            }
        }
        if (success == false) continue;

        for (int i = 0; i < snake.getSnakeLength(); i++)
        {
            if (snake.getSnakeCell(i).pos != newBeetlePos)
            {
                return newBeetlePos;
            }
        }
    }
}

void Level::createBeetle(const Position &beetlePos)
{
    beetles.append(Beetle_cell(beetlePos));
}

void Level::removeBeetle(const Position &beetlePos)
{
    QList<Beetle_cell>::iterator it = beetles.begin();
    while (it != beetles.end())
    {
        if ((*it).pos == beetlePos)
        {
            it = beetles.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Level::decBeetles()
{
    Beetle_num--;
}
