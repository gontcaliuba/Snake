#include "cell.h"


Cell::Cell(const Position &pos) :
    QObject(0),
    pos(pos), field_images(FieldImages::getInstance())
{
}

Cell::Cell(const Cell &cell) :
    QObject(0),
    pos(cell.pos), field_images(FieldImages::getInstance())
{
}

Cell::~Cell()
{
}

Cell *Cell::clone()
{
    return new Cell(*this);
}

const Cell &Cell::operator = (const Cell &cell)
{
    this->pos = cell.pos;
    return *this;
}

const QImage &Cell::getCellImage() const
{
    return field_images.getImage(image_null);
}

////////////////////////////////////////////////////////


Snake_cell::Snake_cell(const Position &pos):
    Cell(pos)
{
}

Snake_cell::Snake_cell(const Cell &cell) :
    Cell(cell)
{
}

const Snake_cell &Snake_cell::operator =(const Snake_cell &cell)
{
    this->pos = cell.pos;
    return *this;
}

Cell *Snake_cell::clone()
{
    return new Snake_cell(*this);
}

const QImage &Snake_cell::getCellImage() const
{
    return field_images.getImage(image_null);
}

////////////////////////////////////////////////////////


Field_cell::Field_cell(const Position &pos):
    Cell(pos)
{
}

Field_cell::Field_cell(const Cell &cell):
    Cell(cell)
{
}

const Field_cell &Field_cell::operator =(const Field_cell &cell)
{
    this->pos = cell.pos;
    return *this;
}

Cell *Field_cell::clone()
{
    return new Field_cell(*this);
}

const QImage &Field_cell::getCellImage() const
{
    return field_images.getImage(image_field);
}

////////////////////////////////////////////////////////


Beetle_cell::Beetle_cell(const Position &pos):
    Cell(pos)
{
}

Beetle_cell::Beetle_cell(const Cell &cell):
    Cell(cell)
{
}

const Beetle_cell &Beetle_cell::operator =(const Beetle_cell &cell)
{
    this->pos = cell.pos;
    return *this;
}

Cell *Beetle_cell::clone()
{
    return new Beetle_cell(*this);
}

const QImage &Beetle_cell::getCellImage() const
{
    return field_images.getImage(image_beetle);
}

////////////////////////////////////////////////////////

Port_cell::Port_cell(const Position &pos, bool state):
    Cell(pos), state(state)
{
}

Port_cell::Port_cell(const Cell &cell, bool state):
    Cell(cell), state(state)
{
}

const Port_cell &Port_cell::operator =(const Port_cell &cell)
{
    this->pos = cell.pos;
    this->state = cell.state;
    return *this;
}

Cell *Port_cell::clone()
{
    return new Port_cell(*this);
}

const QImage &Port_cell::getCellImage() const
{
    return field_images.getImage(image_port);
}

void Port_cell::setState(bool State)
{
    state = State;
}

bool Port_cell::getState() const
{
    return state;
}

////////////////////////////////////////////////////////

Wall_cell::Wall_cell(const Position &pos):
    Cell(pos)
{
}

Wall_cell::Wall_cell(const Cell &cell):
    Cell(cell)
{
}

const Wall_cell &Wall_cell::operator =(const Wall_cell &cell)
{
    this->pos = cell.pos;
    return *this;
}

const QImage &Wall_cell::getCellImage() const
{
    return field_images.getImage(image_wall);
}

Cell *Wall_cell::clone()
{
    return new Wall_cell(*this);
}


////////////////////////////////////////////////////////

Snake_head_ud::Snake_head_ud(const Position &pos) :
    Snake_cell(pos)
{
}

Snake_head_ud::Snake_head_ud(const Cell &cell) :
    Snake_cell(cell)
{
}

const Snake_head_ud &Snake_head_ud::operator =(const Snake_head_ud &cell)
{
    this->pos = cell.pos;
    return *this;
}

Cell *Snake_head_ud::clone()
{
    return new Snake_head_ud(*this);
}

const QImage &Snake_head_ud::getCellImage() const
{
       return field_images.getImage(image_null);
}

////////////////////////////////////////////////////////

Snake_head_lr::Snake_head_lr(const Position &pos) :
    Snake_cell(pos)
{
}

Snake_head_lr::Snake_head_lr(const Cell &cell) :
    Snake_cell(cell)
{
}

const Snake_head_lr &Snake_head_lr::operator =(const Snake_head_lr &cell)
{
    this->pos = cell.pos;
    return *this;
}

Cell *Snake_head_lr::clone()
{
    return new Snake_head_lr(*this);
}

const QImage &Snake_head_lr::getCellImage() const
{
    return field_images.getImage(image_null);
}
