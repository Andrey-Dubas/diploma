#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _target(Point3D(100, 100, 100), Point3D(10, 10, 0)),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    overviewPanel.reset(new FlightPanel(dynamic_cast<QWidget*>(ui->spaceViewer)));
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(dataProvide()));
}

void MainWindow::resizeEvent(QResizeEvent * event)
{
    QRect rect = ui->spaceViewer->geometry();
    overviewPanel->setGeometry(QRect(QPoint(0, 0), QSize(rect.width(), rect.height())));
}

void MainWindow::dataProvide()
{
    _target.timeStep(0.05, FORWARD);
}

MainWindow::~MainWindow()
{
    delete ui;
}
