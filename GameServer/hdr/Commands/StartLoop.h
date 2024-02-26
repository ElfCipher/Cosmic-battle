#pragma once

#include "ICommand.h"
#include "EventLoop.h"

namespace Server
{
    
class StartLoop : public ICommand
{
public:
    StartLoop(EventLoop& loop) :
        loop(loop) {}

    virtual ~StartLoop() {}

    virtual void Execute() override
    {
        if(loop.Start())
            throw Exception("Failed start loop");
    }

protected:
    EventLoop& loop;
};

} // namespace Server
