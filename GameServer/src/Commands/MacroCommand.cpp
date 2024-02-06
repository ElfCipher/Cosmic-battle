#include "MacroCommand.h"

namespace Server
{

MacroCommand::MacroCommand(const CommandList& cmdList) :
    cmdList(cmdList)
{
}

void MacroCommand::Execute()
{
    for (auto &&cmd : cmdList)
        cmd->Execute();
}

} // namespace Server
