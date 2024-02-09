#include "CheckFuelCommand.h"

namespace Server
{

CheckFuelCommand::CheckFuelCommand(PFuelable fuelable) :
    fuelable(fuelable)
{
}

void CheckFuelCommand::Execute()
{
    if(fuelable->getFuel() - fuelable->getBurningRate() < 0.0)
       throw CheckFuelException(fuelable);
}

} // namespace Server
