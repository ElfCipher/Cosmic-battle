#include "CheckFuelCommand.h"

namespace Server
{

CheckFuelCommand::CheckFuelCommand(PIFuelable fuelable) :
    fuelable(fuelable)
{
}

void CheckFuelCommand::Execute()
{
    if(fuelable->getFuel() - fuelable->getBurningRate() < 0.0)
       throw CheckFuelException(fuelable);
}

} // namespace Server
