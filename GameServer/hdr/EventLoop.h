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
    // sync start (blocking)
    int Start();
    void Stop();
    bool IsStarted() {
        return isStarted;
    }
    
    void Put(PICommand cmd);
    static EventLoop& Locate();

    ExceptionHandler& GetHandler() {
        return handler;
    }

    size_t GetCommandsNum() {
        std::scoped_lock lk(mut);
        return queue.size();
    }

    ~EventLoop();

private:
    EventLoop();
    void Exec();
    
    bool isStarted = false;
    std::thread thread;
    std::mutex mut;
    std::queue<PICommand> queue;
    std::binary_semaphore qSem{0};
    std::binary_semaphore startSem{0};
    ExceptionHandler handler;
};

} // namespace Server
