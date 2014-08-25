#include "ccontrolledtarget.h"

void CControlledTarget::timeStep(float dt, KeyDirection accelDirection)
{
    _position = _position + _velocity * dt;
    _velocity = _velocity * (1 + _retardKoef * dt);
    _velocity = _velocity + _accel * dt;
    Vector3D speedDirection = _velocity.direction();

    switch(accelDirection)
    {
        case UP:
            speedDirection.Beta() += Grad(90).GetRad();
            break;
        case DOWN:
            speedDirection.Beta() += Grad(-90).GetRad();
            break;
        case LEFT:
            speedDirection.Alpha() += Grad(-90).GetRad();
            break;
        case RIGHT:
            speedDirection.Alpha() += Grad(-90).GetRad();
            break;
        case FORWARD:
            break;
        default:;
    }
    _accel = speedDirection * _retardKoef;
}
