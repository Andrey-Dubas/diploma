#ifndef CMISSLE_H
#define CMISSLE_H

#include <memory>

#include </home/andy/diploma_code_2/diploma/MathModelBase.h>
#include </home/andy/diploma_code_2/diploma/ialgo.h>
#include </home/andy/diploma_code_2/diploma/Kalman.h>
#include <isignalapplier.h>
#include "/home/andy/diploma_code_2/FlightReviewPanel/GeometryStructures.h"

#include "../FlightReviewPanel/GeometryStructures.h"
/*
 * - method of proportional guidance
 * - used variables:
 * - distance - distance to target
 * - targetDir - direction to target(2)
 * - vTarget - scalar of speed of target
 * - moveDirection - direction of speed of target
 *
 * - common amount of arguments = D(1) + vTarget(2) + missleVector(2) = 6
 **/

enum DynanicSystem
{
    DISTANCE = 0,

    DISTANCE_ALPHA,
    DISTANCE_BETA,

    TARGET_SPEED,
    TARGET_SPEED_ALPHA,
    TARGET_SPEED_BETA,

    MISSLE_SPEED,
    MISSLE_SPEED_ALPHA,
    MISSLE_SPEED_BETA,

    ParamAmount
};

enum ControlSignal
{
    SPEED_ALPHA,
    SPEED_BETA,

    SignalAmount
};

class MathModel: public IMathModel<ParamAmount>
{
    using Vector = IMathModel<ParamAmount>::Vector;

    Vector modelStep(const Vector& observedModel, float dt) override
    {
        Vector nextState = observedModel;

        Point3D distance = Vector3D(observedModel[DISTANCE_ALPHA], observedModel[DISTANCE_BETA])
                                  * observedModel[DISTANCE];

        Point3D vMissle = Vector3D(observedModel[MISSLE_SPEED_ALPHA], observedModel[MISSLE_SPEED_BETA])
                                  * observedModel[MISSLE_SPEED];

        Point3D vTarget = Vector3D(observedModel[TARGET_SPEED_ALPHA], observedModel[TARGET_SPEED_BETA])
                                  * observedModel[TARGET_SPEED];

        distance.X() = distance.X() - (vMissle.X() - vTarget.X()) * dt;
        distance.Y() = distance.Y() - (vMissle.Y() - vTarget.Y()) * dt;
        distance.Z() = distance.Z() - (vMissle.Z() - vTarget.Z()) * dt;

        nextState[DISTANCE] = distance.Scalar();

        auto vec = distance.direction();
        nextState[DISTANCE_ALPHA] = vec.Alpha();
        nextState[DISTANCE_BETA] = vec.Beta();

        return nextState;
    }
};


class GuidanceAlgo: public IGuidanceAlgo<ParamAmount, SignalAmount>
{
public:
    virtual SignalVector Perform(const ModelVector& state) override // TODO: FIX: signal should be an angles to add to get right course
                                                                    // Curently that's course itself
    {
        Point3D distance = Vector3D(state[DISTANCE_ALPHA], state[DISTANCE_BETA])
                                  * state[DISTANCE];

        Point3D vMissle = Vector3D(state[MISSLE_SPEED_ALPHA], state[MISSLE_SPEED_BETA])
                                  * state[MISSLE_SPEED];

        Point3D vTarget = Vector3D(state[TARGET_SPEED_ALPHA], state[TARGET_SPEED_BETA])
                                  * state[TARGET_SPEED];

        Point3D dDistance = vMissle - vTarget;

        Point3D dDesired = distance.direction() * dDistance.Scalar();

        Point3D dToOptimal = dDesired - dDistance;

        Point3D desiredSpeed = vMissle + dToOptimal;

        SignalVector result = {desiredSpeed.direction().Alpha() - vMissle.direction().Alpha(),
                               desiredSpeed.direction().Beta() - vMissle.direction().Beta()};
        return result;

    }
};


class SignalApplier: public ISignalApplier<ParamAmount, SignalAmount>
{
public:
    StateVector apply(const StateVector& state, const SignalVector& signal, float dt) override
    {
        static float koef = 0.4;

        StateVector result = state;
        result[MISSLE_SPEED_ALPHA] += signal[SPEED_ALPHA]* koef * dt;
        result[MISSLE_SPEED_BETA] += signal[SPEED_BETA]* koef * dt;

        return result;
    }
};

class CKalman: public IFilter<ParamAmount, SignalAmount>
{
    using IFilter::ModelState;
    ModelState perform(const ModelState& observedState,
                                   std::shared_ptr<IMathModel<ParamAmount>> model,
                                   std::unique_ptr<IGuidanceAlgo<ParamAmount, SignalAmount>> guidanceAlgo,
                                   std::shared_ptr<ISignalApplier<ParamAmount, SignalAmount>> signalApplier,
                                   float dt) override
    {
        return observedState;
    }
};

//template<int ModelSize, int CommandAmount>
class CMissle
{
public:
    using Vector = Util::Vector<float, ParamAmount>;
private:

    Vector _previousModel;

    std::unique_ptr<IMathModel<ParamAmount>> _mathModel;                              // mathematically described evolution of system (calculated step)
    std::unique_ptr<IGuidanceAlgo<ParamAmount, SignalAmount>> _guidanceAlgo;         // generate signals for control (angles of speed direction)
    std::unique_ptr<IFilter<ParamAmount, SignalAmount>> _modelFilter;                // actually filter
    std::unique_ptr<ISignalApplier<ParamAmount, SignalAmount>> _signalApplier;        // to proparate signal over real changing
private:

public:

    Point3D Velocity() {
        Point3D res = polarToDekart(_previousModel[MISSLE_SPEED], Vector3D(_previousModel[MISSLE_SPEED_ALPHA],_previousModel[MISSLE_SPEED_BETA]));
         return res;
    }

    Vector CurrentModel() { return _previousModel;}

    Point3D RelativePosition()
    {
        Point3D result = polarToDekart(_previousModel[DISTANCE], Vector3D(_previousModel[DISTANCE_ALPHA], _previousModel[DISTANCE_BETA]));
        return result;
    }

    void timeStep(const Vector& observedModel, float dt);
    CMissle(Point3D targetVelocity, Point3D missleVelocity,
            Point3D distanceToTarget,
            IMathModel<ParamAmount>* model,
            IGuidanceAlgo<ParamAmount, SignalAmount>* guidanceAlgo,
            IFilter<ParamAmount, SignalAmount>* modelFilter,
            ISignalApplier<ParamAmount, SignalAmount>* signalApplier
            )
    {
        std::pair<float, Vector3D> distance = dekartToPolar(distanceToTarget);
        std::pair<float, Vector3D> targetV = dekartToPolar(targetVelocity);
        std::pair<float, Vector3D> chaserV = dekartToPolar(missleVelocity);

        _previousModel = {
            distance.first, distance.second.Alpha(), distance.second.Beta(),
            targetV.first, targetV.second.Alpha(), targetV.second.Beta(),
            chaserV.first, chaserV.second.Alpha(), chaserV.second.Beta()
         };

        _mathModel.reset(model);
        _guidanceAlgo.reset(guidanceAlgo);
        _modelFilter.reset(modelFilter);
        _signalApplier.reset(signalApplier);
    }
};

#endif // CMISSLE_H
