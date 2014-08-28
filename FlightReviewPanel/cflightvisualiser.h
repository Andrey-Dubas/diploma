#ifndef CFLIGHTVISUALISER_H
#define CFLIGHTVISUALISER_H

#include <QWidget>
#include <QPoint>
#include <QVector3D>
#include <array>

static float pi = 3.14159265;


class Grad
{
    float _grad;
public:
    explicit Grad(float grad):_grad(grad)
    {
    }
    float GetRad(){return _grad * pi / 180;}
};

struct Vector3D
{
    float _alpha, _beta;
public:
    Vector3D(float alpha, float beta): _alpha(alpha), _beta(beta)
    {
    }

    Vector3D(Grad alpha, Grad beta): _alpha(alpha.GetRad()), _beta(beta.GetRad())
    {
    }
    float Alpha() const { return _alpha;}
    float Beta()  const { return _beta;}

    void AddAlpha(float alpha);
    void AddAlpha(Grad alpha) { AddAlpha(alpha.GetRad());}

    void AddBeta(float beta);
    void AddBeta(Grad beta) { AddBeta(beta.GetRad());}
};

Vector3D operator+(const Vector3D& lhs, const Vector3D& rhs);
Vector3D operator-(const Vector3D& lhs, const Vector3D& rhs);


struct Point3D
{
    float _x, _y, _z;
public:
    float& X() {return _x;}
    float& Y() {return _y;}
    float& Z() {return _z;}

    const float& X() const {return _x;}
    const float& Y() const {return _y;}
    const float& Z() const {return _z;}

    Point3D rotate(Vector3D v)
    {

    }

    Vector3D direction() const
    {
        // if direction is along axisY - then angles are zeros
        if(X() == 0)
        {
            return Vector3D(0, 0);
        }

        float xyDiag = std::sqrt(X() * X() + Y() * Y());
        float spaceDiag = std::sqrt(X() * X() + Y() * Y() + Z() * Z());

        float alpha = std::asin(X() / xyDiag);
        float beta = std::asin(Z() / spaceDiag);
        return Vector3D(alpha, beta);
    }

    Point3D UnoPoint()
    {
        float len = Scalar();
        if(len == 0)
        {
            throw std::logic_error("zero Point");
        }
        return Point3D(X()/len, Y()/len, Z()/len);
    }

    Point3D(float x, float y, float z): _x(x), _y(y), _z(z)
    {
    }

    float Scalar() const {return std::sqrt(X() * X() + Y() * Y() + Z() * Z());}

    std::string toString() const;
};

Point3D operator-(const Point3D& lhs, const Point3D rhs);

std::ostream& operator<<(std::ostream& os, const Point3D p);

struct Point2D
{
    float _x, _y;
public:
    float& X() {return _x;}
    float& Y() {return _y;}
    Point2D(float x, float y): _x(x), _y(y)
    {
    }
    operator QPointF()
    {
        return QPointF(_x, _y);
    }
};

struct Rectangle3D
{
    float minX, minY, minZ;
    float maxX, maxY, maxZ;

    Rectangle3D():
        minX(0), minY(0), minZ(0),
        maxX(0), maxY(0), maxZ(0){}

    float getDiffX() const
    {
        return maxX - minX;
    }

    float getDiffY() const
    {
        return maxY - minY;
    }

    float getDiffZ() const
    {
        return maxZ - minZ;
    }

    Rectangle3D(const Point3D& min, const Point3D& max):
        minX(min.X()), minY(min.Y()), minZ(min.Z()),
        maxX(max.X()), maxY(max.Y()), maxZ(max.Z()){}

    void expandRect(const Point3D& p)
    {
        auto expandMax = [](float outPoint, float& expandedSide){if(outPoint > expandedSide) expandedSide = outPoint * 1.2;};
        auto expandMin = [](float outPoint, float& expandedSide){if(outPoint < expandedSide) expandedSide = outPoint * 1.2;};
        expandMax(p.X(), maxX);
        expandMax(p.Y(), maxY);
        expandMax(p.Z(), maxZ);

        expandMin(p.X(), minX);
        expandMin(p.Y(), minY);
        expandMin(p.Z(), minZ);
    }
};


Point3D operator*(const Point3D& p, float dt);
Point3D operator+(const Point3D& p1, const Point3D& p2);
Point3D operator*(Vector3D v, float scalar);

Point3D rotate(const Point3D& p, const Vector3D& v);

class CFlightVisualiser : public QWidget
{
    Q_OBJECT
public:
    explicit CFlightVisualiser(QWidget *parent = 0);
    explicit CFlightVisualiser(QWidget *parent, Point3D target, Point2D centralScreenPoint, Point3D scaleView, Vector3D viewPoint);
    void setTargetPosition(Point3D target){_target.push_back(target);}
    void setChaserPosition(Point3D chaser){_chaser.push_back(chaser);}
    //void mathModelState(Point3D chaser, Point3D targets);

    void rotateZ(float rad);
    void rotateZ(Grad grad){rotateZ(grad.GetRad());}

    void rotateX(float rad);
    void rotateX(Grad grad){rotateX(grad.GetRad());}
    void drawPathes(QPainter &painter, const Rectangle3D &fieldLimit);
private:
    virtual void paintEvent(QPaintEvent * arg);
    Point2D getScreenPoint(const Point3D &p, const Rectangle3D &fieldLimit);
    void drawCords(QPainter &painter, const Rectangle3D &fieldLimit);
    
public slots:
    void rotateUp() {rotateX(Grad(15));}
    void rotateDown() {rotateX(Grad(-15));}

    void rotateLeft() {rotateZ(Grad(-15));}
    void rotateRight() {rotateZ(Grad(15));}

protected:
    void resizeEvent(QResizeEvent *event);
    Rectangle3D& getMaximumRect();
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
