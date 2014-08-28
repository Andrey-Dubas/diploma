#include "flightpanel.h"
#include <QTimer>
#include <iostream>

const float FlightPanel::controlHeight = 100;

FlightPanel::FlightPanel(QWidget *parent):
    QWidget(parent),
    wi(this),
    timer(this)
{
    up.reset(new QPushButton(QIcon(), QString("up"), this));
    down.reset(new QPushButton(QIcon(), QString("down"), this));
    left.reset(new QPushButton(QIcon(), QString("left"), this));
    right.reset(new QPushButton(QIcon(), QString("right"), this));

    up->resize(   controlHeight, controlHeight/2.5);
    down->resize( controlHeight, controlHeight/2.5);
    left->resize( controlHeight, controlHeight/2.5);
    right->resize(controlHeight, controlHeight/2.5);

    QRect rect = QRect(0, 0, this->width(), this->height() - 50);
    wi.setGeometry(rect);
    wi.setVisible(true);

    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));

    QObject::connect(up.get(), SIGNAL(clicked()),    &wi, SLOT(rotateUp()));
    QObject::connect(down.get(), SIGNAL(clicked()),  &wi, SLOT(rotateDown()));
    QObject::connect(left.get(), SIGNAL(clicked()),  &wi, SLOT(rotateLeft()));
    QObject::connect(right.get(), SIGNAL(clicked()), &wi, SLOT(rotateRight()));
    timer.setInterval(200);
    timer.start();
}

void FlightPanel::setFrameRect(const QRect& rect) {
    QWidget::setGeometry(rect);
}

void FlightPanel::resizeEvent(QResizeEvent* event)
{
    QSize s = event->size();
    float width = s.width();
    s.setHeight(s.height() - controlHeight);
    wi.resize(s);

    static float downTopBottom = this->height() - controlHeight* 0.10 - down->height();
    static float upperTopBottom = this->height() - controlHeight * 0.55 - up->height();

    static float sideTopBottom =  this->height() - controlHeight * 0.3 - left->height();

    float centralButtonLeft = width / 2 - controlHeight / 2;

    float leftButtonLeft = width / 2 - controlHeight * 1.5 - 10;
    float rightButtonLeft = width / 2 + controlHeight * 0.5 + 10;

    up->move(centralButtonLeft, upperTopBottom);
    down->move(centralButtonLeft, downTopBottom);

    left->move(leftButtonLeft, sideTopBottom);
    right->move(rightButtonLeft, sideTopBottom);
}

void FlightPanel::setTargetPosition(Point3D target)
{
    std::cout << target;
    this->wi.setTargetPosition(target);

}

void FlightPanel::setChaserPosition(Point3D chaser)
{
    this->wi.setChaserPosition(chaser);
}

void FlightPanel::tick()
{
/*
    static float x = 0;
    const float chaserAmplitudeX = 50;
    const float chaserAmplitudeY = 50;
    const float targetAmplitudeX = 50;
    const float targetAmplitudeY = 50;
    const float lenKoef = 10;

    this->wi.mathModelState(Point3D(0 * lenKoef, chaserAmplitudeX * std::sin(x - 1), chaserAmplitudeY * std::cos(x - 1)),
                            Point3D(0 * lenKoef, targetAmplitudeX * std::sin(x), targetAmplitudeY * std::cos(x)));
    x += 0.1;
*/
    this->wi.update();
}

FlightPanel::~FlightPanel()
{
}
