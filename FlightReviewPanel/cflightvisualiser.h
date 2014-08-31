#ifndef CFLIGHTVISUALISER_H
#define CFLIGHTVISUALISER_H
#include "GeometryStructures.h"

class CFlightVisualiser : public QWidget
{
    Q_OBJECT
public:
    explicit CFlightVisualiser(QWidget *parent = 0);
    explicit CFlightVisualiser(QWidget *parent, Point3D target, Point2D centralScreenPoint, Point3D scaleView, Vector3D viewPoint);
    void setTargetPosition(Point3D target){_target.push_back(target);}
    void setChaserPosition(Point3D chaser){_chaser.push_back(chaser);}

    void rotateZ(float rad);
    void rotateZ(Grad grad){rotateZ(grad.GetRad());}

    void rotateX(float rad);
    void rotateX(Grad grad){rotateX(grad.GetRad());}
private:
    virtual void paintEvent(QPaintEvent *);
    Point2D getScreenPoint(const Point3D &p, const QRect& fieldLimit);
    Point2D getPlainCords(const Point3D &p);

    void drawCords(QPainter &painter, const QRect& fieldLimit);
    void drawPathes(QPainter &painter, const QRect& fieldLimit);
    
public slots:
    void rotateUp() {rotateX(Grad(15));}
    void rotateDown() {rotateX(Grad(-15));}

    void rotateLeft() {rotateZ(Grad(-15));}
    void rotateRight() {rotateZ(Grad(15));}

protected:
    void resizeEvent(QResizeEvent *event);
    Rectangle3D getMaximumRect();
    QRect getMaximumRect2D();
    void expandRect(Point3D p);

private:
    Point3D _scale;       // what part of "virtual" scale represents on widget
    Vector3D _viewPoint;
    std::vector<Point3D> _chaser;
    std::vector<Point3D> _target;
    float _densityCordLinesX;
    float _densityCordLinesY;
    Point2D _centralScreenPoint;
};

#endif // CFLIGHTVISUALISER_H
