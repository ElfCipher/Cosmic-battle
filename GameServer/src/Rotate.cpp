#include "Rotate.h"

namespace Server
{

Rotate::Rotate(int direction, int angularVelocity) :
    IRotable(angularVelocity)
{
    this->direction = direction;
}

void Rotate::Execute()
{
    setDirection(getDirection() + getAngularVelocity()%getDirectionsNumber());
}

} // namespace Server
