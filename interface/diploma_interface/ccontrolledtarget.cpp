#include "ccontrolledtarget.h"
#include <iostream>

Point3D CControlledTarget::timeStep(float dt, KeyDirection accelDirection)
{
    _position = _position + _velocity * dt;

    float speedScalar = _velocity.Scalar();

    Util::Vector<float, 3> speedVec = {_velocity.X(), _velocity.Y(), _velocity.Z() };
    Util::Vector<float, 3> accelVec;
    switch(accelDirection)
    {
        case UP:
            accelVec = vectorMul(_orientation, speedVec);
            break;
        case DOWN:
            accelVec = vectorMul(speedVec, _orientation);
            break;
        case LEFT:
            accelVec = {-_orientation[0], -_orientation[1], -_orientation[2]};
            break;
        case RIGHT:
            accelVec = _orientation;
            break;
        case FORWARD:
            accelVec = {_velocity.X(), _velocity.Y(), _velocity.Z()};
            break;
        default:;
    }

    try
    {
        Point3D summaryAccel = Point3D(accelVec[0], accelVec[1], accelVec[2]).UnoPoint();
        Point3D newVelocity = _velocity + summaryAccel * (_retardKoef);// * dt);
        //if(accelDirection == LEFT || accelDirection == RIGHT)
        //{
        Point3D orientationPoint(_orientation[0], _orientation[1], _orientation[2]);
        float alpha = newVelocity.direction().Alpha() - _velocity.direction().Alpha();
        _orientation[0] =   orientationPoint.X() * std::cos(alpha) + orientationPoint.Y() * std::sin(alpha);
        _orientation[1] = - orientationPoint.X() * std::sin(alpha) + orientationPoint.Y() * std::cos(alpha);
        //}


        if(_velocity.X() * newVelocity.X() < 0
                && _velocity.Y() * newVelocity.Y() < 0
                ) // FIX
        {
            std::cout << "orientation reverse" << std::endl;
            _orientation = { -_orientation[0], -_orientation[1], _orientation[2]};
        }

        _velocity = newVelocity.direction() * _velocity.Scalar();

    }
    catch(std::logic_error)
    {

    }
    return _position;
}
