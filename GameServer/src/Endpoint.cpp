#include "Endpoint.h"
#include "Exception.h"
#include "InitIoC.h"

namespace Server
{

Endpoint::Endpoint(PCQueue<PICommand> queue, uint64_t id):
    AMQP::LibEventHandler(evbase = event_base_new()),
    queue(queue),
    id(id),
    callback([](std::string str){})
{
    AMQP::Address address("amqp://rmuser:rmpassword@localhost:5672");
    _connection = new AMQP::TcpConnection(this, address);
    channel = new AMQP::TcpChannel(_connection);
}

Endpoint::~Endpoint()
{
    Stop();
    event_base_free(evbase);
    delete _connection;
    delete channel;
}

void Endpoint::Start(Callback callback)
{
    this->callback = callback;
    thread = std::thread([&](){
        
        std::make_shared<InitIoC>()->Execute();
        IoC::Generator<ICommand, CommonMessage, PCQueue<PICommand>> interpretGen = [](CommonMessage msg, PCQueue<PICommand> queue) {
            return std::make_shared<InterpretCommand>(msg, queue);
        };

        IoC::Resolve<ICommand, std::string, std::any>("IoC.Register", "InterpretCommand", interpretGen)->Execute();
        event_base_dispatch(evbase);
    });
}

void Endpoint::Stop()
{
    event_base_loopbreak(evbase);
    evbase = nullptr;
    if(thread.joinable())
        thread.join();
}

void Endpoint::onConnected(AMQP::TcpConnection *connection)
{
    auto exchangeName = std::string("game-exchange-").append(std::to_string(id));
    auto queueName = std::string("game-queue-").append(std::to_string(id));
    auto key = std::string("routing-key-").append(std::to_string(id));
    
    // объявляем очереди и точки обмена на случай, если они не созданы
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

    // готовность принимать сообщения
    channel->consume(queueName, AMQP::noack).onReceived([&](const AMQP::Message &message, uint64_t deliveryTag, bool redelivered){
        CommonMessage msg {};
        msg.gameId = uint64_t(message.headers().get("gameId"));
        if(msg.gameId != id)
            return;

        msg.objectId = uint64_t(message.headers().get("objectId"));
        msg.operationId = uint64_t(message.headers().get("operationId"));
        msg.json = std::string(message.body(), message.bodySize());
        
        queue->Put(IoC::Resolve<ICommand, CommonMessage, PCQueue<PICommand>>("InterpretCommand", msg, queue));
    });
}

} // namespace Server
