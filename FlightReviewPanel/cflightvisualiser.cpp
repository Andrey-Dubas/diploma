#include <cmath>
#include <QBitmap>
#include <QPaintDevice>
#include <QPaintEvent>
#include <QPainter>

#include </home/andy/diploma_code_2/diploma/vector.h>
#include </home/andy/diploma_code_2/diploma/matrix.h>
#include </home/andy/diploma_code_2/diploma/DataOperations.h>
#include "cflightvisualiser.h"


Point3D operator*(const Point3D& p, float dt)
{
    return Point3D(p.X() * dt, p.Y() * dt, p.Z() * dt );
}

Point3D operator+(const Point3D& p1, const Point3D& p2)
{
    return Point3D(p1.X() * p2.X(), p1.Y() * p2.Y(), p1.Z() * p2.Z() );
}

Point3D operator*(Vector3D v, float scalar)
{
    return Point3D( scalar * cos(v.Beta()) * cos(v.Alpha()),
                  scalar * cos(v.Beta()) * sin(v.Alpha()),
                  scalar * sin(v.Beta()));
}

CFlightVisualiser::CFlightVisualiser(QWidget *parent, Point3D target, Point2D centralScreenPoint, Point3D scaleView, Vector3D viewPoint):
    QWidget(parent), _centralScreenPoint(centralScreenPoint), _scale(scaleView), _viewPoint(viewPoint)
{
    _target.push_back(target);
    _chaser.push_back(Point3D(0, 0, 0));
    _densityCordLinesX = 0.1;
    _densityCordLinesY = 0.1;
}

CFlightVisualiser::CFlightVisualiser(QWidget *parent) :
    CFlightVisualiser(parent, Point3D(100, 100, 100), Point2D(100, 250), Point3D(500, 500, 500),  Vector3D(Grad(0), Grad(0)))
{

}

Point2D CFlightVisualiser::getScreenPoint(const Point3D& p, const Rectangle3D& fieldLimit)
{
    std::function<float(float, float)> f = [](float res, float item){ return res + item;};

    Util::Vector<float, 3> ini = {p.X(), p.Y(), p.Z()};
    auto view = _viewPoint;

    float alpha = -view.Alpha();
    float beta = -view.Beta();

    Util::Matrix<float, 3, 3> rotateY = { std::cos(beta), 0, std::sin(beta),
                                          0             , 1, 0,
                                          -std::sin(beta), 0, std::cos(beta)};

    Util::Matrix<float, 3, 3> rotateZ = { std::cos(alpha), std::sin(alpha), 0,
                                          -std::sin(alpha), std::cos(alpha), 0,
                                          0             ,              0, 1};
    ini = rotateY * rotateZ * ini;

    float x = (std::abs(fieldLimit.minX) + ini[0]) / fieldLimit.getDiffX();
    float y = (std::abs(fieldLimit.minY) + ini[1]) / fieldLimit.getDiffY();
    float z = (std::abs(fieldLimit.minZ) + ini[2]) / fieldLimit.getDiffZ();

    y *= (this->width());
    z *= (this->height());

    return Point2D(y, this->height() - z);
}

/*
void CFlightVisualiser::mathModelState(Point3D chaser, Point3D target)
{
    _chaser.push_back(chaser);
    _target.push_back(target);
}
*/

void CFlightVisualiser::resizeEvent(QResizeEvent * event)
{
    if(event->oldSize().width() != -1) // window has been just created
    {
        float dx = event->size().width() - event->oldSize().width();
        float koefX = event->size().width() / (float)event->oldSize().width();
        float dy = event->size().height() - event->oldSize().height();
        float koefY = event->size().height() / (float)event->oldSize().height();

        _centralScreenPoint.X() *= koefX;
        _centralScreenPoint.Y() *= koefY;

        _scale.X() *= koefX;
        _scale.Y() *= koefY;
        _scale.Z() *= std::sqrt(koefY * koefX);
    }
}

void CFlightVisualiser::rotateZ(float rad)
{
    std::cout << "Z on " << rad << std::endl;
    _viewPoint.Alpha() += rad;
}

void CFlightVisualiser::rotateX(float rad)
{
    std::cout << "X on " << rad << std::endl;
    _viewPoint.Beta() += rad;
}

Rectangle3D& CFlightVisualiser::getMaximumRect()
{
    Rectangle3D res;

    for(const auto& p: this->_chaser){res.expandRect(p);}
    for(const auto& p: this->_target){res.expandRect(p);}

    res.expandRect(Point3D(-10, -10, -10));
    res.expandRect(Point3D(10, 10, 10));
    return res;
}

void CFlightVisualiser::drawCords(QPainter& painter, const Rectangle3D& fieldLimit)
{
    //QPen oldPen = painter.pen();
    painter.setPen(Qt::DashLine);

    Point3D zero3D(0, 0, 0), x3D(100, 0, 0), y3D(0, 100, 0), z3D(0, 0, 100);
    Point2D zeroPoint = getScreenPoint(zero3D, fieldLimit);
    Point2D x = getScreenPoint(x3D, fieldLimit);
    Point2D y = getScreenPoint(y3D, fieldLimit);
    Point2D z = getScreenPoint(z3D, fieldLimit);
    painter.setPen(QPen(QColor(), 1));

    painter.drawLine(QPointF(zeroPoint), QPointF(x));
    painter.drawText(QRectF(QPointF(x), QPointF(x.X() + 20, x.Y() + 20)), "X");

    painter.drawLine(QPointF(zeroPoint), QPointF(y));
    painter.drawText(QRectF(QPointF(y), QPointF(y.X() + 20, y.Y() + 20)), "Y");

    painter.drawLine(QPointF(zeroPoint), QPointF(z));
    painter.drawText(QRectF(QPointF(z), QPointF(z.X() + 20, z.Y() + 20)), "Z");

    painter.setPen(Qt::SolidLine);

    //QVector<QPoint> frameCords = {QPoint(0, 0), QPOint(0, this->height()), QPoint(this->width(), this->height()), QPoint(this->width(), 0)};
    const int distance = 1;
    std::vector<QPoint> frameVec = {QPoint(distance, distance), QPoint(distance, this->height() - distance),
                                    QPoint(distance, this->height() - distance), QPoint(this->width() - distance, this->height() - distance),
                                    QPoint(this->width() - distance, this->height() - distance), QPoint(this->width() - distance, distance),
                                    QPoint(this->width() - distance, distance), QPoint(distance, distance)};
    QVector<QPoint> frameCords;
    for(const auto& p: frameVec)
    {
        frameCords.push_back(p);
    }

    painter.drawLines(frameCords);
}

void CFlightVisualiser::drawPathes(QPainter& painter, const Rectangle3D& fieldLimit)
{


    QPainterPath targetPath, chaserPath;
    if(_target.size() == 0 || _chaser.size() == 0)
    {
        std::runtime_error("No path for target and chaser");
    }

    targetPath.moveTo(QPointF(getScreenPoint(_target[0], fieldLimit)));
    chaserPath.moveTo(QPointF(getScreenPoint(_chaser[0], fieldLimit)));

    std::for_each(_target.begin() + 1, _target.end(),
                  [&](Point3D p){
                    targetPath.lineTo(QPointF(getScreenPoint(p, fieldLimit)));
                  }
    );

    std::for_each(_chaser.begin() + 1, _chaser.end(),
                  [&](Point3D p){
                    chaserPath.lineTo(QPointF(getScreenPoint(p, fieldLimit)));
                  }
    );

    painter.drawPath(targetPath);
    painter.drawPath(chaserPath);

    painter.drawEllipse(getScreenPoint(*(_target.end()-1), fieldLimit), 5, 5);
    painter.drawEllipse(getScreenPoint(*(_chaser.end()-1), fieldLimit), 5, 5);
}

void CFlightVisualiser::paintEvent(QPaintEvent * arg)
{
    QPainter painter(this);

    const Rectangle3D maxRect = getMaximumRect();
    drawCords(painter, maxRect);
    drawPathes(painter, maxRect);
}
