#ifndef FIELDDRAWER_H
#define FIELDDRAWER_H

#include <QObject>
#include <QFont>
#include <QFrame>
#include <QPainter>
#include <level.h>
#include "fieldimages.h"
#include "gamestate.h"
#include "game.h"
#include <QPen>

class FieldDrawer : public QFrame
{

Q_OBJECT

    Game *game_ptr;
    FieldImages &field_images;

    QFont count_down_font;
    QFont time_font;

    QFontMetrics count_font_metrics;

    QPen myWhitePen, myBlackPen;

public:
    FieldDrawer(QWidget* parent = 0, Qt::WindowFlags f = 0);
    void setGame(Game &game);
    int getFieldWidth() const;
    int getFieldHeight() const;
    int deltaXFunc(const Cell &A, const Cell &B) const;
    int deltaYFunc(const Cell &A, const Cell &B) const;
    void setImage(QPainter &painter, const Cell &cell, const ImageType &image) const;
    void drawHead(QPainter &painter, const Snake &snake) const;
    void drawBody(QPainter &painter, const Snake &snake) const;
    void drawTail(QPainter &painter, const Snake &snake) const;


private:
    void setWidgetSize(const Game &game);

protected:
    virtual void paintEvent(QPaintEvent *);
};

#endif // FIELDDRAWER_H
