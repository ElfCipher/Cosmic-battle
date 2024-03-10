#pragma once

#include "amqpcpp.h"
#include "amqpcpp/linux_tcp.h"
#include "amqpcpp/libevent.h"
#include <thread>
#include <InterpretCommand.h>

namespace Server
{
    
class Endpoint : public AMQP::LibEventHandler
{
public:
    using Callback = std::function<void(std::string)>;
    
    Endpoint(PCQueue<PICommand> queue, uint64_t id = 0);
    virtual ~Endpoint();

    /**
     * @brief start event loop (blocking)
     * @param callback put "OK" if no errors
     */
    void Start(Callback callback);
    /**
     * @brief stop event loop
     */
    void Stop();

    virtual void onConnected(AMQP::TcpConnection *connection) override;
    virtual void onError(AMQP::TcpConnection *connection, const char *message) override {
        std::cerr << message << std::endl;
    }
    virtual void onClosed(AMQP::TcpConnection *connection) override {
        std::cout << "Close connection" << std::endl;
    }
    virtual void onLost(AMQP::TcpConnection *connection) override {
        std::cout << "Lost connection" << std::endl;
    }

private:
    PCQueue<PICommand> queue;
    uint64_t id; // отвечает за id игры
    AMQP::TcpConnection* _connection;
    event_base* evbase;
    AMQP::TcpChannel* channel;
    Callback callback;
    std::thread thread;
};

} // namespace Server
