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
    Point3D _position, _velocity, _accel;
    float _retardKoef = 0.1;
public:

    CControlledTarget(Point3D position, Point3D speed):
        _position(position),
        _velocity(speed),
        _accel(_velocity * _retardKoef)
    {
    }

    void timeStep(float dt, KeyDirection accelDirection);

    CControlledTarget();
};

#endif // CCONTROLLEDTARGET_H
