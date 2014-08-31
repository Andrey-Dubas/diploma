#ifndef CCONTROLLEDTARGET_H
#define CCONTROLLEDTARGET_H

#include "../FlightReviewPanel/cflightvisualiser.h"
#include </home/andy/diploma_code_2/diploma/vector.h>
#include </home/andy/diploma_code_2/diploma/DataOperations.h>

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
    Util::Vector<float, 3> _orientation;
    Point3D _position, _velocity;
    float _retardKoef = 1;
public:
    CControlledTarget(Point3D position, Point3D speed, Point3D orientation):
        _position(position)
        , _velocity(speed)
    {
        orientation = orientation.UnoPoint() * _velocity.Scalar();
        _orientation = {orientation.X(), orientation.Y(), orientation.Z()}; // to do the orientation vector
                                                                      // the same length as _velocity
    }

    Point3D timeStep(float dt, KeyDirection accelDirection);

    Point3D Position() const{ return _position;}
    Point3D Speed() const { return _velocity; }
    Point3D Orientation() const { return Point3D(_orientation[0], _orientation[1], _orientation[2]); }
    //Point3D Acceleration() const {return _accel; }
};

#endif // CCONTROLLEDTARGET_H
