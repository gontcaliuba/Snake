#include "engine.h"


Engine::Engine(Game &game) :
    game(game), sounds(Sounds::getInstance())
{

}

void Engine::eventLeft()
{
    Level * currentLevel_ptr = game.getCurrentLevel();
    if (currentLevel_ptr) currentLevel_ptr->snake.setDirection(Left, currentLevel_ptr->field.getSize());
}

void Engine::eventRight()
{
    Level * currentLevel_ptr = game.getCurrentLevel();
    if (currentLevel_ptr) currentLevel_ptr->snake.setDirection(Right, currentLevel_ptr->field.getSize());
}

void Engine::eventUp()
{
    Level * currentLevel_ptr = game.getCurrentLevel();
    if (currentLevel_ptr) currentLevel_ptr->snake.setDirection(Up, currentLevel_ptr->field.getSize());
}

void Engine::eventDown()
{
    Level * currentLevel_ptr = game.getCurrentLevel();
    if (currentLevel_ptr) currentLevel_ptr->snake.setDirection(Down, currentLevel_ptr->field.getSize());
}

void Engine::time_timer_event()
{
    if (game.getState().getCurGameState() == GameState::None) return;
    if (game.getState().getCurGameState() == GameState::Lose) return;
    if (game.getState().getCurGameState() == GameState::Pause) return;
    if (game.getState().getCurGameState() == GameState::Win) return;

    Level * currentLevel = game.getCurrentLevel();
    if (currentLevel)
    {
        currentLevel->incrementTimeCounter();

        if ((game.getState().getCurGameState() == GameState::CountDown) &&
                (currentLevel->getTimeCounter() == 0))
                    game.setState(GameState::Appear);
    }
}

void Engine::turn_timer_event()
{
    Level * currentLevel = game.getCurrentLevel();
    if (currentLevel == 0) return;

    Snake &snake = currentLevel->snake;
    const Field &field = currentLevel->field;
    const Size &fieldSize = field.getSize();
    const int snakeLen = snake.getSnakeLength();
    const Position nextHeadPos = snake.getNextHeadPosition(fieldSize);
    const GameState::GameStateEnum gameState = game.getState().getCurGameState();
    const Port_cell &port = currentLevel->port;


    switch (gameState)
    {
    case GameState::None:
    case GameState::Pause:
    case GameState::CountDown:
        break;

    case GameState::Win:
        break;

    case GameState::Lose:
        sounds.playLose();
        break;

    case GameState::Appear:
        sounds.playTheme(game.getLevelNum());
        if (headInBody(snake) ||
                (headInWall(snake, field) && port.pos != snake.getSnakeCell(0).pos))
                {
                    game.setState(GameState::Lose);
                    sounds.playCrash();
                }
        else
        {
            if (snake.getInitialSnakeLength() > snake.getSnakeLength())
            {
                if (snakeLen <= 0) snake.createHead(currentLevel->port.pos);
                else eat();
            }
            else
            {
                move();
                game.setState(GameState::InGame);
                if (currentLevel->Beetle_num > 0)
                {
                    currentLevel->createBeetle(currentLevel->generateBeetlePos());
                    currentLevel->decBeetles();
                }
            }
        }
        break;

    case GameState::InGame:
        if (headInBody(snake) || headInWall(snake, field))
        {
            game.setState(GameState::Lose);
            sounds.playCrash();
        }
        else
        {
            if (headInBeetle(nextHeadPos, currentLevel->beetles))
            {
                currentLevel->removeBeetle(nextHeadPos);
                eat();
                sounds.playCatch();

                if (currentLevel->Beetle_num > 0)
                {
                    currentLevel->createBeetle(currentLevel->generateBeetlePos());
                    currentLevel->decBeetles();
                }
            }
            else
            {
                move();
            }

            if ((currentLevel->Beetle_num <= 0)
                && (currentLevel->beetles.isEmpty()))
                    game.setState(GameState::InPort);
        }
        break;

    case GameState::InPort:
        if (headInBody(snake) ||
                (headInWall(snake, field) && port.pos != snake.getSnakeCell(0).pos))
        {
            game.setState(GameState::Lose);
            sounds.playCrash();
        }
        else
        {
            if (snake.getNextHeadPosition(fieldSize) == port.pos) snake.move(fieldSize);
            else move();

            if (snake.getSnakeCell(0).pos == port.pos) game.setState(GameState::Disappear);
        }
        break;

    case GameState::Disappear:
        snake.cutTail();
        if (snake.getSnakeLength() <= 0) game.setState(GameState::NextLevel);
        break;

    case GameState::NextLevel:
        game.nextLevel();
        if (game.getCurrentLevel() == 0)
        {
            sounds.playWin();
            game.setState(GameState::Win);
        }
        else
        {
            game.setState(GameState::Appear);
            game.getCurrentLevel()->setTimeCounter(0);
        }
        break;

    default:
        break;
    }
}

void Engine::eventPause()
{
    if (game.getState().getCurGameState() == GameState::None) return;
    if (game.getState().getCurGameState() == GameState::Lose) return;
    if (game.getState().getCurGameState() == GameState::Win) return;

    if (game.getState().getCurGameState() == GameState::Pause)
        game.setState(game.getState().getPrevGameState());
    else game.setState(GameState::Pause);
}

void Engine::startGame()
{
    game.setState(GameState::CountDown);
    //game.setState(GameState::Win);
}

bool Engine::headInWall(const Snake &snake, const Field &field) const
{
    if (snake.getSnakeLength() <= 0) return false;

    const Position &snake_head_pos = snake.getSnakeCell(0).pos;
    return positionInWall(snake_head_pos, field);
}

bool Engine::positionInWall(const Position &pos, const Field &field) const
{
    Cell *cell = field.getCell(pos);
    if (cell == 0) return false;

    QString className(cell->metaObject()->className());
    if (className == "Wall_cell") return true;
    return false;
}

bool Engine::headInBody(const Snake &snake) const
{
    int snakeLength = snake.getSnakeLength();
    if (snakeLength > 0)
    {
        Position headPos = snake.getSnakeCell(0).pos;
        for (int i = 1; i < snakeLength; i++)
        {
            if(headPos == snake.getSnakeCell(i).pos) return true;
        }
    }
    return false;
}

bool Engine::headInBeetle(const Position &snake_head_pos, const QList<Beetle_cell> &beetles) const
{
    for (int i = 0; i < beetles.count(); i++)
    {
        if (snake_head_pos == beetles[i].pos) return true;
    }
    return false;
}

void Engine::move()
{
    Level * currentLevel = game.getCurrentLevel();
    if (currentLevel == 0) return;

    Snake &snake = currentLevel->snake;
    Field &field = currentLevel->field;
    const Position &nextHeadPos = snake.getNextHeadPosition(field.getSize());

    if (positionInWall(nextHeadPos, field) == true)
    {
        sounds.playCrash();
        game.setState(GameState::Lose);
        return;
    }
    else snake.move(field.getSize());
}

void Engine::eat()
{
    Level * currentLevel = game.getCurrentLevel();
    if (currentLevel == 0) return;

    Snake &snake = currentLevel->snake;
    Field &field = currentLevel->field;
    const Position &nextHeadPos = snake.getNextHeadPosition(field.getSize());

    if (positionInWall(nextHeadPos, field) == true)
    {
        sounds.playCrash();
        game.setState(GameState::Lose);
        return;
    }
    else snake.eat(field.getSize());
}


