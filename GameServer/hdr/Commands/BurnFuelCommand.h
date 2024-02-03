#pragma once

#include "ICommand.h"
#include "Objects/Fuelable.h"

namespace Server
{

class BurnFuelCommand : public ICommand
{
public:
    BurnFuelCommand(PFuelable fuelable);
    virtual ~BurnFuelCommand() { }
    virtual void Execute() override;

protected:
    PFuelable fuelable;
};
    
} // namespace Server
