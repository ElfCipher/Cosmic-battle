#include "EventLoop.h"
#include <iostream>
#include "Exception.h"
#include "HardStopLoop.h"

namespace Server
{
    
EventLoop::EventLoop(PCQueue<Server::PICommand> q) :
    queue(q)
{
    isStarted = false;
}

int EventLoop::Start()
{
    if(isStarted)
        return 0;

    UpdateBehaviour([this](){
        PICommand cmd = queue->Get();
        try {
            cmd->Execute();
        }
        catch(const Exception& e) {
            handler.Handle(cmd, e)->Execute();
        }
    });

    try
    {
        isStarted = true;
        thread = std::thread([this]() {
            Exec();
        });
    }
    catch(const std::exception& e)
    {
        isStarted = false;
        std::cerr << e.what() << std::endl;
        return -1;
    }

    startSem.acquire();
    
    return 0;
}

EventLoop::~EventLoop()
{
    if(IsStarted())
        queue->Put(std::make_shared<HardStopLoop>(*this)); // кладём команду в очередь, иначе зависнем в queue->Get
        
    if(thread.joinable())
            thread.join();
}

void EventLoop::Exec()
{
    startSem.release();
    while(isStarted)
        behaviour();
}

} // namespace Server

