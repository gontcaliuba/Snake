#include "fielddrawer.h"

FieldDrawer::FieldDrawer(QWidget *parent, Qt::WindowFlags f):
    QFrame(parent, f),
    game_ptr(0),
    field_images(FieldImages::getInstance()),
    count_down_font("Courier new", 20, QFont::Bold),
    time_font("Courier new", 15, QFont::Bold),
    count_font_metrics(count_down_font),
    myWhitePen(QColor::fromRgb(255, 255, 255)),
    myBlackPen(QColor::fromRgb(0, 0, 0))
{

}

void FieldDrawer::setGame(Game &game)
{
    game_ptr = &game;
    setWidgetSize(game);
    this->update();
}

int FieldDrawer::getFieldWidth() const
{
    if (game_ptr == 0) return 0;
    Level * currentLevel = game_ptr->getCurrentLevel();
    if (currentLevel == 0) return 0;
    int imSize = field_images.getImageSize();

    return currentLevel->field.getSize().getW() * imSize;
}

int FieldDrawer::getFieldHeight() const
{
    if (game_ptr == 0) return 0;
    Level * currentLevel = game_ptr->getCurrentLevel();
    if (currentLevel == 0) return 0;
    int imSize = field_images.getImageSize();

    return currentLevel->field.getSize().getH() * imSize;
}

int FieldDrawer::deltaXFunc(const Cell &A, const Cell &B) const
{   int xA = A.pos.getX();
    int xB = B.pos.getX();
    int deltaX = xA - xB;
    if (qAbs(deltaX) <= 1) return deltaX;
    else if (xA > xB) return -1;
    else if (xB > xA) return 1;
    return 0;
}

int FieldDrawer::deltaYFunc(const Cell &A, const Cell &B) const
{
    int yA = A.pos.getY();
    int yB = B.pos.getY();
    int deltaY = yA - yB;
    if (qAbs(deltaY) <= 1) return deltaY;
    else if (yA > yB) return -1;
    else if (yB > yA) return 1;
    return 0;
}

void FieldDrawer::setImage(QPainter &painter, const Cell &cell, const ImageType &image) const
{
    int imSize = field_images.getImageSize();
    painter.drawImage(cell.pos.getX() * imSize,
                      cell.pos.getY() * imSize,
                      field_images.getImage(image));
}

void FieldDrawer::drawHead(QPainter &painter, const Snake &snake) const
{
    const Cell &head = snake.getSnakeCell(0);
    const Cell &afterHead = snake.getSnakeCell(1);
    int deltaX = deltaXFunc(head, afterHead);
    int deltaY = deltaYFunc(head, afterHead);
    if (deltaX == -1)
    {
        setImage(painter, head, image_snake_head_left);
    }
    else if (deltaX == 1)
    {
        setImage(painter, head, image_snake_head_right);
    }
    else if (deltaY == 1)
    {
        setImage(painter, head, image_snake_head_bottom);
    }
    else if (deltaY == -1)
    {
        setImage(painter, head, image_snake_head_top);
    }
}

void FieldDrawer::drawBody(QPainter &painter, const Snake &snake) const
{
    for (int i = 1; i < snake.getSnakeLength() - 1; i++)
    {
        const Cell &prevCell = snake.getSnakeCell(i - 1);
        const Cell &currentCell = snake.getSnakeCell(i);
        const Cell &nextCell = snake.getSnakeCell(i + 1);
        int deltaX1 = deltaXFunc(prevCell, currentCell);
        int deltaX2 = deltaXFunc(currentCell, nextCell);
        int deltaY1 = deltaYFunc(prevCell, currentCell);
        int deltaY2 = deltaYFunc(currentCell, nextCell);
        int deltaX = deltaX1 + deltaX2;
        int deltaY = deltaY1 + deltaY2;

        if (qAbs(deltaX) == 2)
            setImage(painter, currentCell, image_snake_hor);
        else if (qAbs(deltaY) == 2)
            setImage(painter, currentCell, image_snake_ver);
        else if ((deltaX1 == -1 && deltaX2 == 0 && deltaY1 == 0 && deltaY2 == 1) ||
                 (deltaX1 == 0 && deltaX2 == 1 && deltaY1 == -1 && deltaY2 == 0))
            setImage(painter, currentCell, image_snake_top_left);
        else if ((deltaX1 == 0 && deltaX2 == -1 && deltaY1 == -1 && deltaY2 == 0) ||
                 (deltaX1 == 1 && deltaX2 == 0 && deltaY1 == 0 && deltaY2 == 1))
            setImage(painter, currentCell, image_snake_top_right);
        else if ((deltaX1 == -1 && deltaX2 == 0 && deltaY1 == 0 && deltaY2 == -1) ||
                 (deltaX1 == 0 && deltaX2 == 1 && deltaY1 == 1 && deltaY2 == 0))
            setImage(painter, currentCell, image_snake_bottom_left);
        else if ((deltaX1 == 0 && deltaX2 == -1 && deltaY1 == 1 && deltaY2 == 0) ||
                 (deltaX1 == 1 && deltaX2 == 0 && deltaY1 == 0 && deltaY2 == -1))
            setImage(painter, currentCell, image_snake_bottom_right);
    }

}

void FieldDrawer::drawTail(QPainter &painter, const Snake &snake) const
{
    int tailNum = snake.getSnakeLength() - 1;
    const Cell &tailCell = snake.getSnakeCell(tailNum);
    const Cell &beforeTailCell = snake.getSnakeCell(tailNum - 1);
    int deltaX = deltaXFunc(tailCell, beforeTailCell);
    int deltaY = deltaYFunc(tailCell, beforeTailCell);
    if (deltaX == -1)
    {
        setImage(painter, tailCell, image_snake_tail_left);
    }
    else if (deltaX == 1)
    {
        setImage(painter, tailCell,image_snake_tail_right);
    }
    else if (deltaY == 1)
    {
        setImage(painter, tailCell,image_snake_tail_bottom);
    }
    else if (deltaY == -1)
    {
        setImage(painter, tailCell,image_snake_tail_top);
    }
}

void FieldDrawer::setWidgetSize(const Game &game)
{
    Level * currentLevel = game.getCurrentLevel();
    if (currentLevel == 0) return;

    int imSize = field_images.getImageSize();
    int fieldW = currentLevel->field.getSize().getW() * imSize;
    int fieldH = currentLevel->field.getSize().getH() * imSize;

    if((fieldW != width()) || (fieldH != height())) resize(fieldW, fieldH);
}

void FieldDrawer::paintEvent(QPaintEvent *)
{
    const GameState &gameState = game_ptr->getState();
    QPainter painter(this);

    if (game_ptr == 0) return;
    Level * currentLevel = game_ptr->getCurrentLevel();
    Snake &snake = currentLevel->snake;
    int imSize = field_images.getImageSize();
    if(currentLevel != 0)
    {
        const Size &field_size = currentLevel->field.getSize();

        for(int i = 0; i < field_size.getW(); i++)
            for(int j = 0; j < field_size.getH(); j++)
            {
               Cell *cell = currentLevel->field.getCell(Position(i , j));
               if (cell == 0) continue;

               painter.drawImage(i * imSize, j * imSize, cell->getCellImage());
            }

        for (int i = 0; i < currentLevel->beetles.count(); i++)
        {
            painter.drawImage(currentLevel->beetles[i].pos.getX() * imSize,
                              currentLevel->beetles[i].pos.getY() * imSize,
                              currentLevel->beetles[i].getCellImage());
        }

        // SNAKE!

        if (currentLevel->snake.getSnakeLength() == 1)
        {
            const Cell &head = currentLevel->snake.getSnakeCell(0);

            if (currentLevel->snake.getDir() == Up)
                            setImage(painter, head, image_snake_head_top);
            if (currentLevel->snake.getDir() == Down)
                            setImage(painter, head, image_snake_head_bottom);
            if (currentLevel->snake.getDir() == Left)
                            setImage(painter, head, image_snake_head_left);
            if (currentLevel->snake.getDir() == Right)
                            setImage(painter, head, image_snake_head_right);
        }

        else if (currentLevel->snake.getSnakeLength() > 1)
        {
            if (gameState.getCurGameState() == GameState::Appear)
            {
                drawHead(painter, snake);
                drawBody(painter, snake);
                drawTail(painter, snake);

            }
            else if (gameState.getCurGameState() == GameState::Disappear)
            {
                drawBody(painter, snake);
                drawTail(painter, snake);
            }

            else
            {
                drawHead(painter, snake);
                drawBody(painter, snake);
                drawTail(painter, snake);
            }
        }
    }
    else if ((gameState.getCurGameState() == GameState::Win))
    {
       painter.setPen(myBlackPen);
       painter.setFont(count_down_font);
       QString win = "YOU WIN!";
       painter.drawText(width() / 2 - count_font_metrics.width(win)/2,
                        height() / 2 - count_font_metrics.height()/2, win);
       QString scoreText = "Your score: ";
       int score = game_ptr->getAllScore();
       if (score < 0) score = 0;
       scoreText += QString::number(score);
       painter.drawText(width() / 2 - count_font_metrics.width(scoreText)/2,
                        height() / 2 + count_font_metrics.height() - count_font_metrics.height()/2, scoreText);
       return;
    }
   else return;

    if ((gameState.getCurGameState() == GameState::CountDown)||
        (gameState.getCurGameState() == GameState::Appear)||
        (gameState.getCurGameState() == GameState::InPort)||
        (gameState.getCurGameState() == GameState::Disappear))
    {
        int x = currentLevel->port.pos.getX();
        int y = currentLevel->port.pos.getY();
        painter.drawImage(x * imSize, y * imSize, currentLevel->port.getCellImage());
    }



    if ((gameState.getCurGameState() == GameState::Lose))
    {
        painter.setPen(myBlackPen);
        painter.setFont(count_down_font);
        QString lose = "GAME OVER!";
        painter.drawText(width() / 2 - count_font_metrics.width(lose)/2 , height() / 2 - 20, lose);
    }

    painter.setFont(time_font);
    painter.setPen(myBlackPen);
    painter.drawText(width() - 100, 15, "Time:");

    const int timeCount = currentLevel->getTimeCounter();
    if (timeCount < 0)
    {
        painter.setPen(myBlackPen);
        painter.setFont(count_down_font);
        painter.drawText(width() / 2 - count_font_metrics.width(timeCount), height() / 2 - 10, QString::number(-timeCount));

        painter.setFont(time_font);
        painter.setPen(myBlackPen);
        painter.drawText(width() - 30, 15, "0");
    }
    else if (timeCount == 0)
    {
        painter.setFont(time_font);
        painter.setPen(myBlackPen);
        painter.drawText(width() - 30, 15, "0");

        painter.setPen(myBlackPen);
        painter.setFont(count_down_font);
        QString go = "Go!";
        painter.drawText(width() / 2 - count_font_metrics.width(go)/2, height() / 2 - 12, go);
    }
    else
    {   painter.setPen(myBlackPen);
        painter.setFont(time_font);
        painter.drawText(width() - 30, 15, QString::number(timeCount));
    }

}

