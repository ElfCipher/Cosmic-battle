#pragma once

#include "MacroCommand.h"
#include "Objects/Movable.h"
#include "Objects/Fuelable.h"

namespace Server
{
    
class MoveWithBurning : public MacroCommand
{
public:
    MoveWithBurning(PIMovable movable, PFuelable fuelable);
    virtual ~MoveWithBurning() { }
};

} // namespace Server
