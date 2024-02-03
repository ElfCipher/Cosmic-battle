#pragma once

#include "ICommand.h"
#include "Movable.h"

namespace Server
{

class ChangeVelocityCommand : public ICommand
{
public:
    ChangeVelocityCommand(PIMovable movable);
    virtual ~ChangeVelocityCommand() { }
    virtual void Execute() override;

protected:
    PIMovable movable;
};
    
} // namespace Server
