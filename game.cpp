#include "game.h"

Game::Game() :
    currentLevel(0)
{
    QDir dir("levels/");
    QList<QString> fileList = dir.entryList(QDir::Files);
    for (int i = 0; i < fileList.count(); i++)
    {
        Level *readLevel = FileWorker::readLevelFromFile("levels/" + fileList[i]);
        if (readLevel) levels.append(readLevel);
    }
}

Game::~Game()
{
    for (int i = 0; i < levels.count(); i++)
    {
        delete levels[i];
    }
    levels.clear();
}

Level *Game::getCurrentLevel() const
{
    if (currentLevel >= levels.count()) return 0;
    return levels[currentLevel];
}

void Game::nextLevel()
{
    if (currentLevel < levels.count())
    {
        currentLevel++;
        emit this->changedLevel();
    }
}

const GameState &Game::getState() const
{
    return state;
}

void Game::setState(GameState::GameStateEnum game_state)
{
    state.setGameState(game_state);
}

int Game::getAllScore() const
{
    int allScore = 0;
    for (int i = 0; i < levels.count(); i++)
    {
        if (levels[i] == 0) continue;
        allScore += levels[i]->getScore();
    }
    return allScore;
}

int Game::getLevelNum()
{
    return currentLevel;
}

