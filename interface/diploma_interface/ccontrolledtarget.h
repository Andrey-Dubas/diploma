#ifndef CCONTROLLEDTARGET_H
#define CCONTROLLEDTARGET_H

#include "../FlightReviewPanel/cflightvisualiser.h"

enum KeyDirection
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    FORWARD
};

class CControlledTarget
{
private:
    Point3D _position, _velocity;
    float _retardKoef = 5;
public:
    CControlledTarget(Point3D position, Point3D speed):
        _position(position),
        _velocity(speed)//,
        //_accel(_velocity * _retardKoef)
    {
    }

    Point3D timeStep(float dt, KeyDirection accelDirection);

    CControlledTarget();

    Point3D Position() const{ return _position;}
    Point3D Speed() const { return _velocity; }
    //Point3D Acceleration() const {return _accel; }
};

#endif // CCONTROLLEDTARGET_H
