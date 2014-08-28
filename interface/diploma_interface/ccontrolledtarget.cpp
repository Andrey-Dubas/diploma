#include "ccontrolledtarget.h"
#include <iostream>

Point3D CControlledTarget::timeStep(float dt, KeyDirection accelDirection)
{
    _position = _position + _velocity * dt;

    float speedScalar = _velocity.Scalar();
    Point3D speedUno = _velocity.UnoPoint();
    Point3D accelUno = speedUno;

    const float angleDiff = 90;
    switch(accelDirection)
    {
        case UP:
            accelUno = rotate(accelUno, Vector3D(Grad(0), Grad(angleDiff)));
            break;
        case DOWN:
            accelUno = rotate(accelUno, Vector3D(Grad(0), Grad(-angleDiff)));
            break;
        case LEFT:
            accelUno = rotate(accelUno, Vector3D(Grad(-angleDiff), Grad(0)));
            break;
        case RIGHT:
            accelUno = rotate(accelUno, Vector3D(Grad(angleDiff), Grad(0)));
            break;
        case FORWARD:
            break;
        default:;
    }

    Point3D summaryAccel = accelUno - speedUno;
    _velocity = _velocity + summaryAccel * (_retardKoef * dt);
    _velocity = _velocity.UnoPoint() * speedScalar;
    return _position;
}
