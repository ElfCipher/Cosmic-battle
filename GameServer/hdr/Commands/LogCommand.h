#pragma once

#include "ICommand.h"
#include "Exception.h"
#include <iostream>

namespace Server
{

class LogCommand : public ICommand
{
public:
    LogCommand(const Exception& exc) 
        : exc(exc) {}

    virtual ~LogCommand() {}

    virtual void Execute() override
    {
        std::cout << "Exception " << typeid(exc).name() << " has been thrown" << std::endl;
    }

protected:
    const Exception& exc;
};

} // namespace Server
