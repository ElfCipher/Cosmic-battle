#include "MoveWithBurning.h"
#include "CheckFuelCommand.h"
#include "BurnFuelCommand.h"
#include "Move.h"

namespace Server
{

MoveWithBurning::MoveWithBurning(PIMovable movable, PIFuelable fuelable) :
    MacroCommand()
{
    cmdList.emplace_back(std::make_shared<CheckFuelCommand>(fuelable));
    cmdList.emplace_back(std::make_shared<Move>(movable));
    cmdList.emplace_back(std::make_shared<BurnFuelCommand>(fuelable));
}

} // namespace Server
