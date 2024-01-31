#include "Rotate.h"

namespace Server
{

Rotate::Rotate(std::shared_ptr<IRotable> r) :
    r(r)
{
}

void Rotate::Execute()
{
    r->setDirection(r->getDirection() + r->getAngularVelocity()%r->getDirectionsNumber());
}

} // namespace Server
