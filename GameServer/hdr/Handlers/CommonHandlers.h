#pragma once

#include "EventLoop.h"
#include "LogCommand.h"
#include "RepeatCommand.h"
#include "DoubleRepeat.h"

namespace Server
{

Handler repeatAndLogInCase = [](PICommand cmd, const Exception& exc) -> PICommand {
    RepeatCommand rcmd(cmd);
    try
    {
        rcmd.Execute();
    }
    catch(const Exception& e)
    {
        return std::make_shared<LogCommand>(e);
    }
    return makeDummy();
};

Handler repeatTwiceAndLog = [](PICommand cmd, const Exception& exc) -> PICommand {
    DoubleRepeat drCmd(cmd);
    try
    {
        drCmd.Execute(); // первое повторение
    }
    catch(const Exception& e)
    {
        return repeatAndLogInCase(cmd, e); // второе повторение и лог
    }
    
    return makeDummy();
};

} // namespace Server
