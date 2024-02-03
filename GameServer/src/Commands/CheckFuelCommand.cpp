#include "CheckFuelCommand.h"

namespace Server
{

CheckFuelCommand::CheckFuelCommand(PFuelable fuelable) :
    fuelable(fuelable)
{
}

void CheckFuelCommand::Execute()
{
    if(fuelable->getFuel() - fuelable->getMoveBurningRate() <= 0.0 ||
       fuelable->getFuel() - fuelable->getRotateBurningRate() <= 0.0)
       throw CheckFuelException(fuelable);
}

} // namespace Server
