#include "RotateWithVelocity.h"

namespace Server
{

RotateWithVelocity::RotateWithVelocity(PIRotable rotable, PIMovable movable)
{
    CommandList list;
    list.emplace_back(std::make_shared<Rotate>(rotable));
    if (movable->getVelocity() != Vector(0, 0))
    {
        double newDirection = movable->getVelocity().GetDirection() + rotable->getAngularVelocity();
        list.emplace_back(std::make_shared<ChangeVelocityCommand>(movable, newDirection));
    }
    
    macro = std::make_unique<MacroCommand>(list);
}

void RotateWithVelocity::Execute()
{
    macro->Execute();
}

} // namespace Server
