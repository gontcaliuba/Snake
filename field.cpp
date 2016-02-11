#include "field.h"


Field::Field(const Size &size) :
    size(size),
    matrix(0)
{
    if (Field::size.getW() <= 0) Field::size.setW(1);
    if (Field::size.getH() <= 0) Field::size.setH(1);
    initMatrix(Field::size);
}

Field::Field(const Field &field) :
    size(field.size),
    matrix(0)
{
    if (Field::size.getW() <= 0) Field::size.setW(1);
    if (Field::size.getH() <= 0) Field::size.setH(1);
    initMatrix(Field::size);

    for (int i = 0; i < size.getW(); i++)
        for (int j = 0; j < size.getH(); j++)
        {
            if (field.matrix[i][j])
                matrix[i][j] = field.matrix[i][j]->clone();
        }
}

Field::~Field()
{
    destroyMatrix();
}

void Field::initMatrix(const Size &size)
{
    int w = size.getW();
    int h = size.getH();
    matrix = new Cell **[w];

    for (int i = 0; i < w; i++)
    {
        matrix[i] = new Cell *[h];
    }

    for (int i = 0; i < w; i++)
        for(int j = 0; j < h; j++)
        {
            matrix[i][j] = 0;
        }
}

void Field::destroyMatrix()
{
    int w = size.getW();
    int h = size.getH();
    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
        {
            Cell *ptr = matrix[i][j];
            if (ptr)
            {
                delete ptr;
            }
        }
    for (int i = 0; i < w; i++)
    {
        delete [] matrix[i];
    }
    delete [] matrix;
}

bool Field::inField(const Position &pos) const
{
    int w = size.getW();
    int h = size.getH();

    if (pos.getX() >= w) return false;
    if (pos.getX() <  0) return false;
    if (pos.getY() >= h) return false;
    if (pos.getY() <  0) return false;

    return true;
}

void Field::clearCell(const Position &pos)
{
    Cell *c = matrix[pos.getX()][pos.getY()];
    if (c) delete c;
}

void Field::setCell(Cell *cell)
{
    if(cell == 0) return;
    if(inField(cell->pos) == true)
    {
        clearCell(cell->pos);
        matrix[cell->pos.getX()][cell->pos.getY()] = cell;
    }
}

Cell *Field::getCell(const Position &pos) const
{
    if (!inField(pos)) return 0;
    return matrix[pos.getX()][pos.getY()];
}

void Field::clearField()
{
    int w = size.getW();
    int h = size.getH();

    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
            clearCell(Position (i, j));
}

const Size &Field::getSize() const
{
    return size;
}
