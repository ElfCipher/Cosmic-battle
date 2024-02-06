#pragma once

#include "ICommand.h"
#include <list>

namespace Server
{

using CommandList = std::list<PICommand>;

class MacroCommand : public ICommand
{
public:
    MacroCommand(const CommandList& cmdList);
    virtual ~MacroCommand() { }
    virtual void Execute() override;

protected:
    MacroCommand() { }
    CommandList cmdList;
};

} // namespace Server
