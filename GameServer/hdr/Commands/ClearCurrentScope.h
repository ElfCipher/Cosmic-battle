#pragma once

#include "IoC.h"

namespace Server
{

class ClearCurrentScope : public ICommand
{
public:
    ClearCurrentScope() {}
    virtual ~ClearCurrentScope() {}
    virtual void Execute() override
    {
        if(!IoC::currentScope)
            return;
            
        IoC::currentScope->clear();
        IoC::currentScope.reset();
    }
};

} // namespace Server
