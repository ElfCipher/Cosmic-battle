#pragma once

#include "ICommand.h"
#include "Objects/IFuelable.h"

namespace Server
{

class BurnFuelCommand : public ICommand
{
public:
    BurnFuelCommand(PIFuelable fuelable);
    virtual ~BurnFuelCommand() { }
    virtual void Execute() override;

protected:
    PIFuelable fuelable;
};
    
} // namespace Server
