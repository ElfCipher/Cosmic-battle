#pragma once

#include "amqpcpp.h"
#include "amqpcpp/linux_tcp.h"
#include "amqpcpp/libevent.h"

namespace Server
{
    
class Endpoint : public AMQP::LibEventHandler
{
public:
    using Callback = std::function<void(std::string)>;
    Endpoint(uint32_t id = 0);
    virtual ~Endpoint();

    /**
     * @brief 
     * @param callback put "OK" if no errors
     */
    void Start(Callback callback);
    void Stop();
    virtual void onConnected(AMQP::TcpConnection *connection) override;

private:
    uint32_t id;
    AMQP::TcpConnection* _connection;
    event_base* evbase;
    AMQP::TcpChannel* channel;
    Callback callback;
};

} // namespace Server
