#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "/home/andy/diploma_code_2/FlightReviewPanel/GeometryStructures.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    , _target(Point3D(100, 100, 100), Point3D(10, 10, 0), Point3D(10, -10, 0))
    , ui(new Ui::MainWindow)
    , _chaser(
          CMissle(
              Point3D(0, 0, 0),
              Point3D(0, 0, 20),
              Point3D(100, 100, 100),
              new MathModel(),
              new GuidanceAlgo(),
              new CKalman(),
              new SignalApplier()
          )
     )
{
    ui->setupUi(this);
    _curDirection = FORWARD;
    _overviewPanel.reset(new FlightPanel(dynamic_cast<QWidget*>(ui->spaceViewer)));
    _timer.setInterval(_modellingStepIntervalMilisec);
    QObject::connect(&_timer, SIGNAL(timeout()), this, SLOT(dataProvide()));
    QObject::connect(ui->startModellingButton, SIGNAL(clicked()), this, SLOT(startModelling()));
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    QRect rect = ui->spaceViewer->geometry();
    _overviewPanel->setGeometry(QRect(QPoint(0, 0), QSize(rect.width(), rect.height())));
}


void MainWindow::keyPressEvent(QKeyEvent * event)
{
    QString txt = event->text();

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
    Point3D targetPos = _target.timeStep(_modellingStepIntervalMilisec * 0.001, _curDirection);//_curDirection); // FIX
    this->_overviewPanel->setTargetPosition(targetPos);

    std::pair<float, Vector3D> relativeDistance = dekartToPolar(_chaser.RelativePosition());
    std::pair<float, Vector3D> targetSpeed = dekartToPolar(_target.Speed());
    std::pair<float, Vector3D> chaserSpeed = dekartToPolar(_chaser.Velocity());

    CMissle::Vector realPosition = {
        relativeDistance.first, relativeDistance.second.Alpha(), relativeDistance.second.Beta(),
        targetSpeed.first, targetSpeed.second.Alpha(), targetSpeed.second.Beta(),
        chaserSpeed.first, chaserSpeed.second.Alpha(), chaserSpeed.second.Beta()
    };
    CMissle::Vector distortedModel = DistortionFunction(
        realPosition
    );

    _chaser.timeStep(
                distortedModel,
                _modellingStepIntervalMilisec * 0.001);

    Point3D chaserPosition = targetPos - _chaser.RelativePosition();

    this->_overviewPanel->setChaserPosition(chaserPosition);

    ui->positionView->setText(QString(_target.Position().toString().data()));
    ui->speedView->setText(QString(_target.Speed().toString().data()));
    ui->orientationView->setText(QString(_target.Orientation().toString().data()));
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

CMissle::Vector MainWindow::DistortionFunction(const CMissle::Vector& realState)
{
    return realState;
}

CMissle::Vector MainWindow::chaserEvolution(const CMissle::Vector& realState, const CControlledTarget& target, float dt)
{
    CMissle::Vector result;

    return result;
}

MainWindow::~MainWindow()
{
    delete ui;
}
