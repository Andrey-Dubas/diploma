#include "cmissle.h"

using Vector = Util::Vector<float, ParamAmount>;

/*
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
 **/


void CMissle::timeStep(const Vector &observedModel, float dt)
{
    Util::Vector<float, 2> signal = _guidanceAlgo->Perform(observedModel);

    Vector chaserMove = _signalApplier->apply(observedModel, signal, dt);

    Vector calculatedModel = (*_mathModel)(chaserMove, dt); // TODO: substitute with guidanceModel

    _previousModel = calculatedModel;

}
