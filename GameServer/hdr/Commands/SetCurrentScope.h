#pragma once

#include "IoC.h"

namespace Server
{

class SetCurrentScope : public ICommand
{
    IoC::PScope newScope;
public:
    SetCurrentScope(IoC::PScope newScope) : newScope(newScope) 
    {}
    virtual ~SetCurrentScope() {}
    virtual void Execute() override
    {
        IoC::currentScope = newScope;
    }
};

} // namespace Server
