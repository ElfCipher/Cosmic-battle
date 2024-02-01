#pragma once

#include "EventLoop.h"
#include "LogCommand.h"
#include "RepeatCommand.h"

namespace Server
{

Handler addLogCmdInQueue = [](PICommand cmd, const Exception& exc) -> PICommand {
    std::stringstream ss; // TODO: logger
    EventLoop::Locate().Put(std::make_shared<LogCommand>(ss, exc));
    return std::make_shared<DummyCommand>();
};

Handler addRepeatCmdInQueue = [](PICommand cmd, const Exception& exc) -> PICommand {
    EventLoop::Locate().Put(std::make_shared<RepeateCommand>(cmd));
    return std::make_shared<DummyCommand>();
};

Handler repeateAndLogInCase = [](PICommand cmd, const Exception& exc) -> PICommand {
    RepeateCommand rcmd(cmd);
    try
    {
        rcmd.Execute();
    }
    catch(const Exception& e)
    {
        std::stringstream ss; // TODO: logger
        LogCommand lcmd(ss, e);
        lcmd.Execute();
    }
    return std::make_shared<DummyCommand>();
};

} // namespace Server
