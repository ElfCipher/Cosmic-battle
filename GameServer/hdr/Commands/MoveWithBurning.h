#pragma once

#include "MacroCommand.h"
#include "Objects/IMovable.h"
#include "Objects/IFuelable.h"

namespace Server
{
    
class MoveWithBurning : public MacroCommand
{
public:
    MoveWithBurning(PIMovable movable, PIFuelable fuelable);
    virtual ~MoveWithBurning() { }
};

} // namespace Server
