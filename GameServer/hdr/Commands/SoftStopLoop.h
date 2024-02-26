#pragma once

#include "EventLoop.h"
#include "Exception.h"
#include "ICommand.h"

namespace Server
{
    
class SoftStopLoop : public ICommand
{
public:
    /** 
     * @param loop поток для остановки
     * @param callback функция, которая будет вызвана после остановки loop
     */
    SoftStopLoop(EventLoop& loop, EventLoop::Action callback = [](){}) :
        loop(loop),
        callback(callback) {}

    virtual ~SoftStopLoop() {}

    virtual void Execute() override
    {
        EventLoop::Action newBehaviour = [&](){
            if(loop.queue->GetSize() == 0)
            {
                loop.Stop();
                callback();
                return;
            }
            
            PICommand cmd = loop.queue->Get();
            try {
                cmd->Execute();
            }
            catch(const Exception& e) {
                loop.GetHandler().Handle(cmd, e)->Execute();
            }
        };

        loop.UpdateBehaviour(newBehaviour);
    }

protected:
    EventLoop& loop;
    EventLoop::Action callback;
};

} // namespace Server
