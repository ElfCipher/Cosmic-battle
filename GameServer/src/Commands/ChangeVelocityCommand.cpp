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

    double oldDirection = velocity.GetDirection();

    double angle = (newDirection - oldDirection)/180*M_PI;

    Vector newVelocity;
    // int64_t sign = angle > 0.0 ? sign = 1 : -1;
    newVelocity.x = velocity.x * cos(angle) - velocity.y * sin(angle);
    newVelocity.y = velocity.x * sin(angle) + velocity.y * cos(angle);

    movable->setVelocity(newVelocity);
}

} // namespace Server
