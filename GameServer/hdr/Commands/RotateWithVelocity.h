#pragma once

#include "Objects/Rotable.h"
#include "Objects/Movable.h"
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
