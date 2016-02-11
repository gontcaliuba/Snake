#ifndef GAMESTATE
#define GAMESTATE

class GameState
{
public:
    enum GameStateEnum
    {
        None = 0,
        CountDown,
        Appear,
        InGame,
        InPort,
        Disappear,
        NextLevel,
        Lose,
        Pause,
        Win

    };

private:
    GameStateEnum gameState[2];

public:
    GameState()
    {
        gameState[0] = None;
        gameState[1] = None;
    }

    void setGameState(GameStateEnum newState)
    {
        gameState[0] = gameState[1];
        gameState[1] = newState;
    }

    GameStateEnum getCurGameState() const
    {
        return gameState[1];
    }

    GameStateEnum getPrevGameState() const
    {
        return gameState[0];
    }
};

#endif // GAMESTATE

