#include "RotateWithVelocity.h"
#include "ChangeVelocityCommand.h"
#include "Rotate.h"

namespace Server
{

RotateWithVelocity::RotateWithVelocity(PIRotable rotable, PIMovable movable) :
    MacroCommand()
{
    cmdList.emplace_back(std::make_shared<Rotate>(rotable));
    if (movable->getVelocity() != Vector(0, 0))
    {
        double newDirection = movable->getVelocity().GetDirection() + rotable->getAngularVelocity();
        cmdList.emplace_back(std::make_shared<ChangeVelocityCommand>(movable, newDirection));
    }
}

} // namespace Server
