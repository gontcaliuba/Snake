#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QList"
#include "level.h"
#include "field.h"
#include "snake.h"
#include "cell.h"
#include "position.h"
#include "fileworker.h"
#include "game.h"
#include "QKeyEvent"
#include "engine.h"
#include "fielddrawer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Game game;
    Engine engine;
    QTimer time_timer, turn_timer;
    FieldDrawer *fd;


protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void keyPressEvent(QKeyEvent *ke);


public slots:
    void time_timer_event();
    void turn_timer_event();
    void reccountFormSize();
};

#endif // MAINWINDOW_H
