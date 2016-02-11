#include "fileworker.h"

Level * FileWorker::readLevelFromFile(const QString &fileName)
{
    QFile level(fileName);
    if (level.open(QFile::ReadOnly | QFile::Text) == false)
    {
        level.close();
        return 0;
    }
    QTextStream stream_reader(&level);

    QString all_file = stream_reader.readAll();
    level.close();

    QList<QString> string_list = all_file.split(QRegExp("[\r\n, ]+"));
    if (string_list.isEmpty()) return 0;
    if (string_list.last().isEmpty()) string_list.removeLast();
    if (string_list.count() < 2) return 0;

    int w = string_list[0].toInt();
    int h = string_list[1].toInt();

    if (string_list.size()<(w * h + 7)) return 0;


    int xPort = string_list[w * h + 4].toInt();
    int yPort = string_list[w * h + 5].toInt();

    int c = 1;
    int i = 2;
    Field levelField(Size(w, h));
    while (c <= h)
    {
         while (i < c * w + 2)
         {
             if(string_list[i].toInt() == 0)
                 levelField.setCell(new Field_cell(Position((i-2)-(c-1)*w,c-1)));
             else if(string_list[i].toInt() == 1)
                 levelField.setCell(new Port_cell(Position((i-2)-(c-1)*w,c-1)));
             else if(string_list[i].toInt() == 2)
                 levelField.setCell(new Wall_cell(Position((i-2)-(c-1)*w,c-1)));
             i++;
         }
       c++;
    }
    Snake snake;
    snake.setDirection(convStringDir(string_list[w * h + 6]), levelField.getSize());
    snake.setInitialSnakeLength(string_list[w * h + 2 ].toInt());
    int Beetle_num = string_list[w * h + 3].toInt();
    return new Level(levelField, snake, QList<Beetle_cell>(), Port_cell(Position(xPort, yPort)), Beetle_num);
    return 0;
}

Direction FileWorker::convStringDir(const QString &dirString)
{
    if (dirString == "u") return Up;
    if (dirString == "d") return Down;
    if (dirString == "l") return Left;
    if (dirString == "r") return Right;
    return Left;
}
