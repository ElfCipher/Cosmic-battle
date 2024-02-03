#include "ChangeVelocityCommand.h"
#include <math.h>

namespace Server
{

ChangeVelocityCommand::ChangeVelocityCommand(PIMovable movable, double newDirection) :
    movable(movable),
    newDirection(newDirection)
{
}

void ChangeVelocityCommand::Execute()
{
    auto velocity = movable->getVelocity();
    if(velocity == Vector(0,0))
        return;

    double oldDirection; 
    if(velocity.y != 0)
        atan(velocity.x / velocity.y);
    else
        oldDirection = velocity.x > 0 ? 90.0 : -90.0;

    double angle = newDirection - oldDirection;
    angle *= M_PI / 180.0;

    Vector newVelocity;
    newVelocity.x = velocity.x * cos(angle) + velocity.y * sin(angle);
    newVelocity.y = velocity.x * sin(angle) - velocity.y * cos(angle);

    movable->setVelocity(newVelocity);
}

} // namespace Server
