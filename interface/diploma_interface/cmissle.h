#ifndef CMISSLE_H
#define CMISSLE_H

#include "../FlightReviewPanel/GeometryStructures.h"
#include </home/andy/diploma_code_2/diploma/MathModelBase.h>
#include <memory>

/*
 * - method of proportional guidance
 * - used variables:
 * - distance - distance to target
 * - vTarget - vector of target's speed(2)
 * - missleVector - speed of missle(2)
 *
 * - common amount of arguments = D(1) + vTarget(2) + missleVector(2) = 6
 **/

class MathModel: public IMathModel<5>
{

};


class CMissle
{
private:
    // used to determine itself
    Point3D _position;
    Point3D _velocity;

    std::unique_ptr<IMathModel<5>> _mathModel;
private:
    Point3D Velocity() { return _velocity;} // TODO: formula for its speed changing

public:
    Point3D timeStep(float distance, Vector3D targetSpeed, Vector3D missleSpeed);
    CMissle(Point3D position, Point3D velocity, std::unique_ptr<IMathModel<5>> model):
        _position(position), _velocity(velocity), _mathModel(model){}
};

#endif // CMISSLE_H
