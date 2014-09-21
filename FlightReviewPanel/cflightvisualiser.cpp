#include <cmath>
#include <QBitmap>
#include <QPaintDevice>
#include <QPaintEvent>
#include <QPainter>

#include </home/andy/diploma_code_2/diploma/vector.h>
#include </home/andy/diploma_code_2/diploma/matrix.h>
#include </home/andy/diploma_code_2/diploma/DataOperations.h>
#include "cflightvisualiser.h"
#include <sstream>
#include "GeometryStructures.h"

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



Point2D CFlightVisualiser::getScreenPoint(const Point3D& p, const QRect& fieldLimit)
{
    Point2D plain = getPlainCords(p);
    float y = (-fieldLimit.left() + plain.X()) / (fieldLimit.right() - fieldLimit.left());
    float z = (-fieldLimit.bottom() + plain.Y()) / (fieldLimit.top() - fieldLimit.bottom());

    y *= this->width();
    z *= this->height();

    return Point2D(y, /*this->height() -*/ z);
}

Point2D CFlightVisualiser::getPlainCords(const Point3D &p)
{
    Vector3D view = _viewPoint;

    float alpha = -view.Alpha();
    float beta = -view.Beta();

    Point3D res = rotate(p, Vector3D(alpha, beta));
    return Point2D(res.Y(), res.Z());
}

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
    _viewPoint.AddAlpha(rad);
}

void CFlightVisualiser::rotateX(float rad)
{
    _viewPoint.AddBeta(rad);
}

Rectangle3D CFlightVisualiser::getMaximumRect()
{
    Rectangle3D res;

    for(const Point3D& p: this->_chaser){res.expandRect(p);}
    for(const Point3D& p: this->_target){res.expandRect(p);}

    res.expandRect(Point3D(-10, -10, -10));
    res.expandRect(Point3D(10, 10, 10));
    return res;
}

QRect CFlightVisualiser::getMaximumRect2D()
{
    QRect res;

    for(const Point3D& p: this->_chaser){res = ::expandRect(getPlainCords(p), res);}
    for(const Point3D& p: this->_target){res = ::expandRect(getPlainCords(p), res);}

    res = ::expandRect(Point2D(-10, -10), res);
    res = ::expandRect(Point2D(10, 10), res);
    return QRect(res.left() - res.width()/10, res.top() - res.height()/10,
                 res.width() * 1.2, res.height() * 1.2);
}

void CFlightVisualiser::drawCords(QPainter& painter, const QRect& fieldLimit)
{
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

void CFlightVisualiser::drawPathes(QPainter& painter, const QRect &fieldLimit)
{


    QPainterPath targetPath, chaserPath;
    if(_target.size() == 0 || _chaser.size() == 0)
    {
        std::runtime_error("No path for target and chaser");
    }

    QPointF targetStart = QPointF(getScreenPoint(_target[0], fieldLimit));
    targetPath.moveTo(targetStart);
    chaserPath.moveTo(QPointF(getScreenPoint(_chaser[0], fieldLimit)));

    for(auto iter = _target.begin() + 1; iter != _target.end(); ++iter)
    {
          QPointF res = getScreenPoint(*iter, fieldLimit);
          targetPath.lineTo(res);
    }

    for(auto iter = _chaser.begin() + 1; iter != _chaser.end(); ++iter)
    {
          QPointF res = getScreenPoint(*iter, fieldLimit);
          targetPath.lineTo(res);
    }

    painter.drawPath(targetPath);
    painter.drawPath(chaserPath);

    painter.drawEllipse(getScreenPoint(*(_target.end()-1), fieldLimit), 5, 5);
    painter.drawEllipse(getScreenPoint(*(_chaser.end()-1), fieldLimit), 5, 5);

    int x =  (_chaser.end()-1)->X();
    int Y =  (_chaser.end()-1)->Y();
    int Z =  (_chaser.end()-1)->Z();
}

void CFlightVisualiser::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QRect maxRect = getMaximumRect2D();
    drawCords(painter, maxRect);
    drawPathes(painter, maxRect);
}
