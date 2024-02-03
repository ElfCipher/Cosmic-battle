#include "MoveWithBurning.h"

namespace Server
{

MoveWithBurning::MoveWithBurning(PIMovable movable, PFuelable fuelable)
{
    CommandList list;
    list.emplace_back(std::make_shared<CheckFuelCommand>(fuelable));
    list.emplace_back(std::make_shared<Move>(movable));
    list.emplace_back(std::make_shared<BurnFuelCommand>(fuelable));
    macro = std::make_unique<MacroCommand>(list);
}

void MoveWithBurning::Execute()
{
    macro->Execute();
}

} // namespace Server
