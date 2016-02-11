#ifndef LEVEL_H
#define LEVEL_H
#include "snake.h"
#include "field.h"
#include <QList>
#include "cell.h"
#include "position.h"
#include "time.h"


class Level
{
private:
    //коэффициенты для расчета очков
    const float score_coeff;
    const int max_score;

    // счетчик времени, начальное значение
    const int startTimeCounter;

public:
    Field field;
    Snake snake;
    QList<Beetle_cell> beetles;
    Port_cell port;
    int Beetle_num;

private:
    int timeCounter;

public:
    Level(const Field &field, const Snake &snake,
         const QList<Beetle_cell> &beetles, const Port_cell &port, const int Beetle_num);
    void incrementTimeCounter();
    int getTimeCounter() const;
    void setTimeCounter(int value);
    int getScore() const;
    Position generateBeetlePos() const;
    void createBeetle(const Position &beetlePos);
    void removeBeetle(const Position &beetlePos);
    void decBeetles();
};

#endif // GAME_H
