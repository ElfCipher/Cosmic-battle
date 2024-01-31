#include "EventLoop.h"
#include <iostream>
#include "Exception.h"

namespace Server
{
    
EventLoop::EventLoop()
{
    isStarted = false;
}

int EventLoop::Start()
{
    if(isStarted)
        return 0;

    auto loop = [this]() {
        this->Exec();
    };

    try
    {
        isStarted = true;
        thread = std::thread(loop);
    }
    catch(const std::exception& e)
    {
        isStarted = false;
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}

void EventLoop::Stop()
{
    isStarted = false;
    sem.release();
    if(thread.joinable())
        thread.join();        
}

void EventLoop::Put(Command cmd)
{
    std::scoped_lock lk(mut);
    queue.emplace(cmd);
    sem.release();
}

EventLoop &EventLoop::Locate()
{
    static EventLoop loop;
    return loop;
}

EventLoop::~EventLoop()
{
}

void EventLoop::Exec()
{
    while(isStarted)
    {
        sem.acquire(); // сработал семафор (положили команду) - начали обрабатывать команды
        while (!queue.empty())
        {
            Command cmd;
            {
                std::lock_guard lk(mut);
                cmd = queue.front();
                queue.pop();
            }

            try
            {
                cmd->Execute();
            }
            catch(const Exception& e)
            {
                handler.Handle(cmd, e)->Execute();
            }
        }
    }
    
}

} // namespace Server

