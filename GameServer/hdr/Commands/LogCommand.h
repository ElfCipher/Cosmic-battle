#pragma once

#include "ICommand.h"
#include "Exception.h"
#include "Logger.h"

namespace Server
{

class LogCommand : public ICommand
{
public:
    LogCommand(const Exception& exc) :
        exc(exc) {}

    virtual ~LogCommand() {}

    virtual void Execute() override
    {
        std::stringstream ss;
        ss << "Exception " << typeid(exc).name() << " has been thrown with message" << std::endl;
        ss << exc.what() << std::endl;
        Logger::Locate().Log(ss.str());
    }

protected:
    const Exception& exc;
};

} // namespace Server
