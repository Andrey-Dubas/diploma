
#include </home/andy/diploma_code_2/diploma/vector.h>
#include </home/andy/diploma_code_2/diploma/matrix.h>
#include </home/andy/diploma_code_2/diploma/DataOperations.h>
#include "cflightvisualiser.h"
#include <sstream>
#include <math.h>

void Vector3D::AddAlpha(float alpha)
{
    _alpha += alpha;
    if(_alpha > pi)
    {
        _alpha -= 2 * pi;
    }

    if (_alpha < -pi)
    {
        _alpha += 2 * pi;
    }
}

void Vector3D::AddBeta(float beta)
{
    _beta += beta;
    if(_beta > pi)
    {
        _beta -= 2 * pi;
    }

    if (_beta < -pi)
    {
        _beta += 2*pi;
    }
}

Vector3D operator+(const Vector3D& lhs, const Vector3D& rhs)
{
    return Vector3D(lhs.Alpha() + rhs.Alpha(), lhs.Beta() + rhs.Beta());
}

Vector3D operator-(const Vector3D& lhs, const Vector3D& rhs)
{
    return Vector3D(lhs.Alpha() - rhs.Alpha(), lhs.Beta() - rhs.Beta());
}



Point3D operator*(const Point3D& p, float dt)
{
    return Point3D(p.X() * dt, p.Y() * dt, p.Z() * dt );
}

Point3D operator+(const Point3D& p1, const Point3D& p2)
{
    return Point3D(p1.X() + p2.X(), p1.Y() + p2.Y(), p1.Z() + p2.Z() );
}

Point3D operator-(const Point3D& lhs, const Point3D rhs)
{
    return Point3D(lhs.X() - rhs.X(), lhs.Y() - rhs.Y(), lhs.Z() - rhs.Z() );
}

Point3D operator*(Vector3D v, float scalar)
{
    float x = scalar * cos(v.Beta()) * sin(v.Alpha());
    float y = scalar * cos(v.Beta()) * cos(v.Alpha());
    float z = scalar * sin(v.Beta());
    return Point3D(x, y, z);
}

QRect expandRect(const Point2D &p, QRect rect)
{
    auto expandMax = [](float outPoint, float expandedSide){return outPoint > expandedSide ? outPoint : expandedSide;};
    auto expandMin = [](float outPoint, float expandedSide){return outPoint < expandedSide ? outPoint : expandedSide;};
    rect.setRight(expandMax(p.X(), rect.right()));
    rect.setLeft(expandMin(p.X(), rect.left()));

    rect.setBottom(expandMax(p.Y(), rect.bottom()));
    rect.setTop(expandMin(p.Y(), rect.top()));
    return rect;
}

std::string Point3D::toString() const
{
    std::stringstream stream;
    stream << "X: "<< X() << ", Y: " << Y() << ", Z: " << Z();
    return stream.str();
}

std::ostream& operator<<(std::ostream& os, const Point3D p)
{
    os << p.toString() << std::endl;
    return os;
}

Point3D rotate(const Point3D& p, const Vector3D &v)
{
    Util::Vector<float, 3> ini = {p.X(), p.Y(), p.Z()};
    float alpha = v.Alpha();
    float beta = v.Beta();

    Util::Matrix<float, 3, 3> rotateY = { std::cos(beta), 0, std::sin(beta),
                                          0             , 1, 0,
                                          -std::sin(beta), 0, std::cos(beta)};

    Util::Matrix<float, 3, 3> rotateZ = { std::cos(alpha), std::sin(alpha), 0,
                                          -std::sin(alpha), std::cos(alpha), 0,
                                          0             ,              0, 1};
    auto rotateMatrix = rotateY * rotateZ;

    auto res = rotateMatrix * ini;
    return Point3D(res[0], res[1], res[2]);
}

/*
class Qaternion
{
    Util::Vector<float, 3> _vector;
    float _scalar;
public:
    enum Axis{
        X = 0,
        Y,
        Z
    };

    Qaternion(float w, float x, float y, float z)
    {
        _scalar = w;
        _vector = {x, y, z};
    }

    Qaternion(float angle, Axis axis)
    {
        _scalar = std::cos(angle);
        _vector = {0, 0, 0};
        _vector = std::sin(angle);
    }

    float module() const
    {
        return std::sqrt(_scalar * _scalar +
                _vector[0] * _vector[0] +
                _vector[1] * _vector[1] +
                _vector[2] * _vector[2] );
    }

    void reverse()
    {
        float quadModule = module() * module();
        return Quaternion(_scalar * quadModule,
                          -_vector[0] * quadModule,
                          -_vector[1] * quadModule,
                -_vector[2] * quadModule);
    }

};
*/
Point3D rotateX(const Point3D& p, float angle)
{

    Util::Vector<float, 3> ini = {p.X(), p.Y(), p.Z()};

    Util::Matrix<float, 3, 3> rotate = { 1             ,  0              , 0              ,
                                          0             ,  std::cos(angle), std::sin(angle),
                                          0             , -std::sin(angle), std::cos(angle)};

    auto rotateMatrix = rotate;

    auto res = rotateMatrix * ini;
    return Point3D(res[0], res[1], res[2]);

}

Point3D rotateY(const Point3D& p, float angle)
{
    return p;
}

Point3D rotateZ(const Point3D& p, float angle)
{
    return p;
}

Point3D polarToDekart(float vector, Vector3D orientation)
{
    Point3D result(
                vector * std::cos(orientation.Beta()) * cos(orientation.Alpha()),
                vector * std::cos(orientation.Beta()) * sin(orientation.Alpha()),
                vector * std::sin(orientation.Beta()));
    return result;
}

std::pair<float, Vector3D> dekartToPolar(Point3D point)
{
    using RetType = std::pair<float, Vector3D>;
    float scalar = std::sqrt(point.X()*point.X() + point.Y()*point.Y() + point.Z()*point.Z());
    if (scalar == 0)
    {
        return RetType(0, Vector3D(0, 0));
    }
    float beta = std::asin(point.Z() / scalar);
    if (point.X() == 0)
    {
        return RetType(scalar, Vector3D(beta, pi/2));
    }
    float alpha = std::atan(point.Y() / point.X());
    return RetType(scalar, Vector3D(alpha, beta));
}
