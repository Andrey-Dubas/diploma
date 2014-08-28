#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _target(Point3D(100, 100, 100), Point3D(10, 10, 0)),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _curDirection = FORWARD;
    _overviewPanel.reset(new FlightPanel(dynamic_cast<QWidget*>(ui->spaceViewer)));
    _timer.setInterval(_modellingStepIntervalMilisec);
    QObject::connect(&_timer, SIGNAL(timeout()), this, SLOT(dataProvide()));
    QObject::connect(ui->startModellingButton, SIGNAL(clicked()), this, SLOT(startModelling()));
}

void MainWindow::resizeEvent(QResizeEvent * event)
{
    QRect rect = ui->spaceViewer->geometry();
    _overviewPanel->setGeometry(QRect(QPoint(0, 0), QSize(rect.width(), rect.height())));
}


void MainWindow::keyPressEvent(QKeyEvent * event)
{
    QString txt = event->text();

    std::cout << txt.toUtf8().constData() << std::endl;

    switch(event->key())
    {
    case Qt::Key_A:
        _curDirection = LEFT;
        break;

    case Qt::Key_D:
        _curDirection = RIGHT;
        break;

    case Qt::Key_W:
        _curDirection = UP;
        break;

    case Qt::Key_S:
        _curDirection = DOWN;
        break;
    default: ;
    }
    QMainWindow::keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    _curDirection = FORWARD;
    QMainWindow::keyReleaseEvent(event);
}

void MainWindow::dataProvide()
{
    std::cout << "direction: " << _curDirection << std::endl;
    Point3D pos = _target.timeStep(_modellingStepIntervalMilisec * 0.001, _curDirection);
    this->_overviewPanel->setTargetPosition(pos);


    ui->positionView->setText(QString(_target.Position().toString().data()));
    ui->speedView->setText(QString(_target.Speed().toString().data()));
    //ui->accelerationView->setText(QString(_target.Acceleration().toString().data()));
}


void MainWindow::startModelling()
{
    if(_active == OFF)
    {
        _active = ON;
        _timer.start(_modellingStepIntervalMilisec);
        ui->startModellingButton->setText("Stop");
    }
    else
    {
        _active = OFF;
        _timer.stop();
        ui->startModellingButton->setText("Start");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
