#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include "game.h"
#include "direction.h"
#include <QTimer>
#include "snake.h"
#include "field.h"
#include "sounds.h"

class Engine
{
    Game &game;
    Sounds &sounds;

public:
    Engine(Game &game);
    void eventLeft();
    void eventRight();
    void eventUp();
    void eventDown();
    void time_timer_event();
    void turn_timer_event();
    void eventPause();
    void startGame();

private:
    bool headInWall(const Snake &snake, const Field &field) const;
    bool positionInWall(const Position &pos, const Field &field) const;
    bool headInBody(const Snake &snake) const;
    bool headInBeetle(const Position &snake_head_pos, const QList<Beetle_cell> &beetles) const;
    void move();
    void eat();

};

#endif // ENGINE_H
