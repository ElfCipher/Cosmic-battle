#pragma once

#include <gtest/gtest.h>
#include "Endpoint.h"
#include "ManualResetEvent.h"
#include "CommandsHolder.h"
#include <jsoncpp/json/json.h>
#include "AdapterIMovable.h"
#include "SetPositionCommand.h"

void RegisterDependency()
{
    using namespace Server;
    // регистрация зависимости на создание команды Move через json аргументы
    std::make_shared<InitIoC>()->Execute();
    IoC::Generator<ICommand, Json::Value, PUObject> createMove = [](Json::Value args, PUObject obj) {
        (void)args;
        return std::make_shared<Move>(std::make_shared<AdapterIMovable>(obj));
    };
    IoC::Resolve<ICommand, std::string, std::any>("IoC.Register", "MoveJson", createMove)->Execute();

    // регистрация зависимости создания команды установки позиции в obj
    IoC::Generator<ICommand, PUObject, Vector> setPosition = [](PUObject obj, Vector pos) {
        return std::make_shared<SetPositionCommand>(obj, pos);
    };
    IoC::Resolve<ICommand, std::string, std::any>("IoC.Register", "Server.IMovable.setPosition", setPosition)->Execute(); 
   
    // регистрация зависимости получения позиции из obj
    IoC::Generator<Vector, PUObject> getPosition = [](PUObject obj) {
        if(obj->find("Position") == obj->end())
            throw Exception("No such property");

        return std::make_shared<Vector>(std::any_cast<Vector>(obj->at("Position")));
    };
    IoC::Resolve<ICommand, std::string, std::any>("IoC.Register", "Server.IMovable.getPosition", getPosition)->Execute(); 
    
    // регистрация зависимости получения скорости из obj
    IoC::Generator<Vector, PUObject> getVelocity = [](PUObject obj) {
        if(obj->find("Velocity") == obj->end())
            throw Exception("No such property");

        return std::make_shared<Vector>(std::any_cast<Vector>(obj->at("Velocity")));
    };
    IoC::Resolve<ICommand, std::string, std::any>("IoC.Register", "Server.IMovable.getVelocity", getVelocity)->Execute(); 
}

TEST(ENDPOINT, RABBITMQ_CONNECT)
{
    using namespace Server;
    RegisterDependency();

    auto queue = std::make_shared<ConcurrentQueue<PICommand>>(); // очередь команд
    uint64_t operationId = 1, objectId = 1, gameId = 1; // набор данных для сообщения
    CommandsHolder::Locate().Register(operationId, "Move"); // Агент присылает 1 - это движение объекта по прямой

    // создание объекта
    auto objects = std::make_shared<UObjects>();
    auto object = std::make_shared<UObject>();
    // позиция 0,0 скорость 0,10 - установка properties у объекта
    object->emplace("Position", Vector());
    object->emplace("Velocity", Vector(0, 10));
    objects->emplace(1, object); // добавляем в список объектов

    // создание endpoint
    Endpoint* endpoint = new Endpoint(queue, objects, 1);
    bool isEndpointStarted = false;
    ManualResetEvent mre;
    // начало работы endpoint
    endpoint->Start([&](std::string result){
        isEndpointStarted = result == "OK";
        if(!isEndpointStarted)
            std::cerr << result << std::endl;
        mre.Set();
    });

    mre.WaitOne();
    EXPECT_TRUE(isEndpointStarted); // успешно подключился к брокеру

    // создаём сообщение и отправляем его самим себе для теста
    std::string json = "{}"; // для команды Move не нужны аргументы
    CommonMessage msg {.gameId = gameId, .objectId = objectId, .operationId = operationId, .json = json};
    endpoint->SendMessage(std::string("game-exchange-").append(std::to_string(gameId)),
                          std::string("routing-key-").append(std::to_string(gameId)),
                          msg);

    auto cmd = queue->Get(); // если успешно получили сообщение, то в очереди лежит команда
    EXPECT_TRUE(typeid(*cmd.get()) == typeid(InterpretCommand)); // соответственно это должна быть InterpretCommand
    cmd->Execute();

    // в итоге должна придти команда нужного типа - Move
    cmd = queue->Get();
    EXPECT_TRUE(typeid(*cmd.get()) == typeid(Move));

    // после выполнения команды позиция меняется на 0,10 - изначально выставляли 0,0
    cmd->Execute();
    Vector newPosition = std::any_cast<Vector>(object->at("Position"));
    EXPECT_EQ(newPosition, Vector(0, 10));

    endpoint->Stop();
    delete endpoint;
}