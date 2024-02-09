#include "BurnFuelCommand.h"

namespace Server
{

BurnFuelCommand::BurnFuelCommand(PFuelable fuelable) :
    fuelable(fuelable)
{
}

void BurnFuelCommand::Execute()
{
    fuelable->setFuel(fuelable->getFuel() - fuelable->getBurningRate());
}

} // namespace Server
