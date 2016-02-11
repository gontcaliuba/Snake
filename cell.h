#ifndef CELL_H
#define CELL_H

#include <QObject>
#include "position.h"
#include "fieldimages.h"

class Cell : public QObject
{
Q_OBJECT

public:
    Position pos;

protected:
    FieldImages &field_images;

public:
    Cell(const Position &pos);
    Cell(const Cell &cell);
    virtual ~ Cell();
    virtual Cell * clone();
    const Cell &operator = (const Cell &cell);
    virtual const QImage &getCellImage() const;
};

class Snake_cell: public Cell
{
Q_OBJECT

public:
    Snake_cell(const Position &pos);
    Snake_cell(const Cell &cell);
    const Snake_cell &operator = (const Snake_cell &cell);
    virtual Cell * clone();
    virtual const QImage &getCellImage() const;
};

class Snake_head_ud: public Snake_cell
{
    Q_OBJECT

public:
    Snake_head_ud(const Position &pos);
    Snake_head_ud(const Cell &cell);
    const Snake_head_ud &operator = (const Snake_head_ud &cell);
    virtual Cell * clone();
    virtual const QImage &getCellImage() const;
};

class Snake_head_lr: public Snake_cell
{
    Q_OBJECT

public:
    Snake_head_lr(const Position &pos);
    Snake_head_lr(const Cell &cell);
    const Snake_head_lr &operator = (const Snake_head_lr &cell);
    virtual Cell * clone();
    virtual const QImage &getCellImage() const;
};

class Field_cell: public Cell
{
    Q_OBJECT

public:
    Field_cell(const Position &pos);
    Field_cell(const Cell &cell);
    const Field_cell &operator = (const Field_cell &cell);
    virtual Cell * clone();
    virtual const QImage &getCellImage() const;
};

class Beetle_cell: public Cell
{
    Q_OBJECT

public:
    Beetle_cell(const Position &pos);
    Beetle_cell(const Cell &cell);
    const Beetle_cell &operator = (const Beetle_cell &cell);
    virtual Cell * clone();
    virtual const QImage &getCellImage() const;
};

class Port_cell: public Cell
{
    Q_OBJECT

    bool state;
public:
    Port_cell(const Position &pos, bool state = false);
    Port_cell(const Cell &cell, bool state = false);
    const Port_cell &operator = (const Port_cell &cell);
    virtual Cell * clone();
    virtual const QImage &getCellImage() const;
    void setState(bool State);
    bool getState() const;
};

class Wall_cell: public Cell
{
    Q_OBJECT

public:
    Wall_cell(const Position &pos);
    Wall_cell(const Cell &cell);
    const Wall_cell &operator = (const Wall_cell &cell);
    virtual const QImage &getCellImage() const;
    virtual Cell * clone();
};

#endif // CELL_H
