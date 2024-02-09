#include "Rotate.h"

namespace Server
{

Rotate::Rotate(PIRotable r) :
    r(r)
{
}

void Rotate::Execute()
{
    r->setDirection(r->getDirection() + r->getAngularVelocity()%r->getDirectionsNumber());
}

} // namespace Server
