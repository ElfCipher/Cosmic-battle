#pragma once

#include <semaphore>

namespace Server
{

class ManualResetEvent
{
public:
    ManualResetEvent(bool initialState = false):
    sem(initialState ? 1 : 0) { }
    void Set() {
        sem.release();
    }
    void WaitOne() {
        sem.acquire();
    }

protected:
    std::binary_semaphore sem;
};

} // namespace Server
