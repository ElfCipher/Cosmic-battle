#pragma once

#include "ICommand.h"
#include <list>

namespace Server
{

using CommandList = std::list<PICommand>;

class MacroCommand : public ICommand
{
public:
    MacroCommand(const CommandList& cdmList);
    virtual ~MacroCommand() { }
    virtual void Execute() override;

protected:
    CommandList cdmList;
};

} // namespace Server
