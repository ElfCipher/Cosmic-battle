#pragma once

#include "ConcurrentQueue.h"
#include <thread>
#include <memory>
#include "ExceptionHandler.h"

namespace Server
{

class EventLoop
{
public:
    EventLoop(PCQueue<PICommand> q);
    ~EventLoop();
    /// sync start (blocking)
    int Start();
    void Stop() {
        isStarted = false;
    }
    bool IsStarted() {
        return isStarted;
    }

    using Action = std::function<void()>;
    void UpdateBehaviour(Action behaviour) {
        this->behaviour = behaviour;
    }

    ExceptionHandler& GetHandler() {
        return handler;
    }

    PCQueue<PICommand> queue;

private:
    void Exec();
    Action behaviour;
    bool isStarted;
    std::thread thread;
    std::binary_semaphore startSem{0};
    ExceptionHandler handler;
};

} // namespace Server
