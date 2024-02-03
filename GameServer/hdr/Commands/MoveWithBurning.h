#pragma once

#include "MacroCommand.h"
#include "CheckFuelCommand.h"
#include "BurnFuelCommand.h"
#include "Move.h"

namespace Server
{
    
class MoveWithBurning : public ICommand
{
public:
    MoveWithBurning(PIMovable movable, PFuelable fuelable);
    virtual ~MoveWithBurning() { }
    virtual void Execute() override;

protected:
    std::unique_ptr<MacroCommand> macro;
};

} // namespace Server
