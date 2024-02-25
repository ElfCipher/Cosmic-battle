#pragma once

#include "ICommand.h"
#include "EventLoop.h"

namespace Server
{
    
class HardStopLoop : public ICommand
{
public:
    /** 
     * @param loop поток для остановки
     * @param callback функция, которая будет вызвана после остановки loop
     */
    HardStopLoop(EventLoop& loop, EventLoop::Action callback = [](){}) :
        loop(loop),
        callback(callback) {}

    virtual ~HardStopLoop() {}

    virtual void Execute() override
    {
        loop.Stop();
        callback();
    }

protected:
    EventLoop& loop;
    EventLoop::Action callback;
};

} // namespace Server
