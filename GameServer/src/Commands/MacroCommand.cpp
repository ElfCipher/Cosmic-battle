#include "MacroCommand.h"

namespace Server
{

MacroCommand::MacroCommand(const CommandList& cdmList) :
    cdmList(cdmList)
{
}

void MacroCommand::Execute()
{
    for (auto &&cmd : cdmList)
        cmd->Execute();
}

} // namespace Server
