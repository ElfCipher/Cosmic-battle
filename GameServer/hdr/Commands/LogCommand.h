#pragma once

#include "ICommand.h"
#include "Exception.h"
#include <iostream>

namespace Server
{

class LogCommand : public ICommand
{
public:
    LogCommand(std::stringstream& ss, const Exception& exc) 
        : ss(ss), exc(exc) {}

    virtual ~LogCommand() {}

    virtual void Execute() override
    {
        ss << "Exception " << typeid(exc).name() << " has been thrown" << std::endl;
    }

protected:
    std::ostream& ss;
    const Exception& exc;
};

} // namespace Server
