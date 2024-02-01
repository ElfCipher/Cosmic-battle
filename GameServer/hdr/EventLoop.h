#pragma once

#include <queue>
#include <mutex>
#include <thread>
#include <memory>
#include <semaphore>
#include "ICommand.h"
#include "ExceptionHandler.h"

namespace Server
{

class EventLoop
{
public:
    int Start();
    void Stop();
    bool IsStarted() {
        return isStarted;
    }

    using Command = std::shared_ptr<ICommand>;
    
    void Put(Command cmd);
    static EventLoop& Locate();
    ExceptionHandler& GetHandler() {
        return handler;
    }
    ~EventLoop();

private:
    EventLoop();
    void Exec();
    
    bool isStarted = false;
    std::thread thread;
    std::mutex mut;
    std::queue<Command> queue;
    std::binary_semaphore sem{0};
    ExceptionHandler handler;
};

} // namespace Server