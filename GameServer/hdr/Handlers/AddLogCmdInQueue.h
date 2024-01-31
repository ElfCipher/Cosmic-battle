#pragma once

#include "EventLoop.h"
#include "LogCommand.h"

namespace Server
{

using Handler = std::function<PICommand(PICommand, const Exception&)>;

Handler addLogCmdInQueue = [](PICommand cmd, const Exception& exc) -> PICommand {
    EventLoop::Locate().Put(std::make_shared<LogCommand>(exc));
};

} // namespace Server
