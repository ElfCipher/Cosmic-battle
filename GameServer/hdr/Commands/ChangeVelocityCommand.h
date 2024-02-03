#pragma once

#include "ICommand.h"
#include "Objects/Movable.h"

namespace Server
{

class ChangeVelocityCommand : public ICommand
{
public:
    ChangeVelocityCommand(PIMovable movable, double newDirection);
    virtual ~ChangeVelocityCommand() { }
    virtual void Execute() override;

protected:
    PIMovable movable;
    double newDirection;
};
    
} // namespace Server
