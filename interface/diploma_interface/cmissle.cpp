#include "cmissle.h"

using Vector = Util::Vector<float, 5>;

Point3D CMissle::timeStep(float distance, Vector3D targetSpeed, Vector3D missleSpeed)
{
    Vector observedModel = {distance,
                            targetSpeed.Alpha(), targetSpeed.Beta(),
                            missleSpeed.Alpha(), missleSpeed.Beta()};

    Vector processedModel = this->_mathModel->modelStep(distance,
                                targetSpeed.Alpha(), targetSpeed.Beta(),
                                missleSpeed.Alpha(), missleSpeed.Beta());
    distance = processedModel[0];

}
