#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QList>
#include "level.h"
#include <QDir>
#include "fileworker.h"
#include "gamestate.h"

class Game : public QObject
{
Q_OBJECT

    int currentLevel;
    QList<Level *> levels;
    GameState state;

public:
    Game();
    ~Game();
    Level * getCurrentLevel() const;
    void nextLevel();
    const GameState & getState() const;
    void setState(GameState::GameStateEnum game_state);
    int getAllScore() const;
    int getLevelNum();

signals:
    void changedLevel();
};

#endif // GAME_H
