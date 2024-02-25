#pragma once

#include <queue>
#include <mutex>
#include <semaphore>
#include <memory>

namespace Server
{

template<class T>
class ConcurrentQueue
{
public:
    void Put(T t)
    {
        {
            std::scoped_lock lk(mut);
            queue.emplace(t);
        }
        qSem.release();
    }
    /**
     * @brief блокирующая функция. не вернёт команду до тех пор, пока очередь будет пуста
     * @return T 
     */
    T Get()
    {
        if(queue.empty())
            qSem.acquire();

        std::scoped_lock lk(mut);
        auto t = queue.front();
        queue.pop();
        return t;
    }

    uint32_t GetSize()
    {
        std::scoped_lock lk(mut);
        return queue.size();
    }

protected:
    std::queue<T> queue;
    std::mutex mut;
    std::binary_semaphore qSem{0};
};

template<class T>
using PCQueue = std::shared_ptr<ConcurrentQueue<T>>;

} // namespace Server
