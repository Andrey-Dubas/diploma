#ifndef ISIGNALAPPLIER_H
#define ISIGNALAPPLIER_H
#include </home/andy/diploma_code_2/diploma/vector.h>
#include </home/andy/diploma_code_2/diploma/matrix.h>

template<int MISSLE_STATE, int CONTROL_SIGNAL>
class ISignalApplier
{
protected:
    using StateVector = Util::Vector<float, MISSLE_STATE>;
    using SignalVector = Util::Vector<float, CONTROL_SIGNAL>;

public:
    virtual StateVector apply(const StateVector& state, const SignalVector& signal, float dt) = 0;
    StateVector operator()(const StateVector& state, const SignalVector& signal, float dt)
    {
        return apply(state, signal, dt);
    }
public:
    ISignalApplier(){}
};

#endif // ISIGNALAPPLIER_H
