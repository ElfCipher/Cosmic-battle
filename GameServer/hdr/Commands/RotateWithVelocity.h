#pragma once

#include "Rotate.h"
#include "ChangeVelocityCommand.h"
#include "MacroCommand.h"

namespace Server
{

class RotateWithVelocity : public ICommand
{
public:
    RotateWithVelocity(PIRotable rotable, PIMovable movable);
    virtual ~RotateWithVelocity() { }
    virtual void Execute() override;

protected:
    std::unique_ptr<MacroCommand> macro;
};

} // namespace Server
