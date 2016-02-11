//******************БИБЛИОТЕКИ******************//

#include "mainwindow.h"
#include <QApplication>

#include <QList>
#include "cell.h"
#include "position.h"
#include "snake.h"
#include "field.h"
#include "time.h"
#include "fieldimages.h"
#include "fileworker.h"
#include "game.h"
#include "time.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(time(0));
    MainWindow w;
    w.show();

    return a.exec();
}
