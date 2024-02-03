#pragma once

#include "ICommand.h"
#include "Fuelable.h"

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
