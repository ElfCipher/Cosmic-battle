#pragma once

#include "Objects/IRotable.h"
#include "Objects/IMovable.h"
#include "MacroCommand.h"

namespace Server
{

class RotateWithVelocity : public MacroCommand
{
public:
    RotateWithVelocity(PIRotable rotable, PIMovable movable);
    virtual ~RotateWithVelocity() { }
};

} // namespace Server
