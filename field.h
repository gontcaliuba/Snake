#ifndef FIELD_H
#define FIELD_H

#include <QDebug>
#include "cell.h"
#include "size.h"
#include "position.h"

class Field
{
    Size size;
    Cell ***matrix;

public:
    Field(const Size &size);
    Field(const Field &field);
    ~Field();

    bool inField(const Position &pos) const;
    void clearCell(const Position &pos);
    void setCell(Cell *cell);
    Cell * getCell(const Position &pos) const;
    void clearField();

    const Size &getSize() const;

private:
    void initMatrix(const Size &size);
    void destroyMatrix();
};

#endif // FIELD_H
