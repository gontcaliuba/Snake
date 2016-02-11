#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    game(), engine(game), fd(0)
{
    ui->setupUi(this);
    connect(&time_timer, SIGNAL(timeout()), this, SLOT(time_timer_event()));
    connect(&turn_timer, SIGNAL(timeout()), this, SLOT(turn_timer_event()));
    time_timer.start(1000);
    turn_timer.start(200);

    fd = new FieldDrawer();
    fd->setGame(game);

    this->setCentralWidget(fd);
    reccountFormSize();

    connect(&game, SIGNAL(changedLevel()), this, SLOT(reccountFormSize()));

    engine.startGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
}

void MainWindow::keyPressEvent(QKeyEvent *ke)
{
    if (ke == 0) return;
    switch (ke->key())
    {
    case Qt::Key_Left:
        engine.eventLeft();
        break;
    case Qt::Key_Right:
        engine.eventRight();
        break;
    case Qt::Key_Up:
        engine.eventUp();
        break;
    case Qt::Key_Down:
        engine.eventDown();
        break;
    case Qt::Key_Space:
        engine.eventPause();
        break;
    }
}

void MainWindow::time_timer_event()
{
    engine.time_timer_event();
    if (fd) fd->update();
}

void MainWindow::turn_timer_event()
{
    engine.turn_timer_event();
    if (fd) fd->update();
}

void MainWindow::reccountFormSize()
{
    if (fd)
    {
        int w = fd->getFieldWidth();
        int h = fd->getFieldHeight();

        if (w == 0) return;
        if (h == 0) return;

        this->resize(w, h);

        this->setMinimumWidth(w);
        this->setMaximumWidth(w);

        this->setMinimumHeight(h);
        this->setMaximumHeight(h);
    }
}

