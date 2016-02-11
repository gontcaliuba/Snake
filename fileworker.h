#ifndef FILEWORKER_H
#define FILEWORKER_H

#include <QTextStream>
#include <QFile>
#include <QString>
#include <QStringList>
#include "level.h"
#include "size.h"
#include <QDir>
#include "cell.h"
#include "field.h"


class FileWorker
{
public:
    static Level * readLevelFromFile(const QString &fileName);
    static Direction convStringDir(const QString &dirString);
};

#endif // FILEWORKER_H
