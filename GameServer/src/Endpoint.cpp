#include "Endpoint.h"
#include "Exception.h"

namespace Server
{

Endpoint::Endpoint(uint32_t id):
    AMQP::LibEventHandler(evbase = event_base_new()),
    id(id),
    callback([](std::string str){})
{
    AMQP::Address address("amqp://rmuser:rmpassword@localhost:5672");
    _connection = new AMQP::TcpConnection(this, address);
    channel = new AMQP::TcpChannel(_connection);
}

Endpoint::~Endpoint()
{
    event_base_free(evbase);
    delete _connection;
}

void Endpoint::Start(Callback callback)
{
    this->callback = callback;
    event_base_dispatch(evbase);
}

void Endpoint::Stop()
{
    event_base_loopbreak(evbase);
    evbase = nullptr;
}

void Endpoint::onConnected(AMQP::TcpConnection *connection)
{
    auto exchangeName = std::string("game-exchange-").append(std::to_string(id));
    auto queueName = std::string("game-queue-").append(std::to_string(id));
    auto key = std::string("routing-key-").append(std::to_string(id));

    channel->declareExchange(exchangeName, AMQP::direct).onError([&](const char* msg){
        std::string error = "Failed declare exchange: ";
        error.append(msg);
        callback(error);
    });

    channel->declareQueue(queueName).onError([&](const char* msg){
        std::string error = "Failed declare queue: ";
        error.append(msg);
        callback(error);
    });

    channel->bindQueue(exchangeName, queueName, key).onSuccess([&](){
        callback("OK");
    }).onError([&](const char* msg){
        std::string error = "Failed bind queue with exchange: ";
        error.append(msg);
        callback(error);
    });
}

void Endpoint::onError(AMQP::TcpConnection *connection, const char *message)
{
    std::cerr << message << std::endl;
}

} // namespace Server
