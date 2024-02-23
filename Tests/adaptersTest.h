#pragma once

#include <gtest/gtest.h>
#include "InitIoC.h"
#include "AdapterIMovable.h"
#include "AdapterIRotable.h"
#include "AdapterIFuelable.h"

TEST(ADAPTERS, EXISTING)
{
    Server::PUObject obj;
    auto movable = new Server::AdapterIMovable(obj);
    auto rotable = new Server::AdapterIRotable(obj);
    auto fuelable = new Server::AdapterIFuelable(obj);
}

TEST(ADAPTERS, IOC_RESOLVE)
{
    Server::PUObject obj = std::make_shared<Server::UObject>();
    Server::Vector position(13, 24);
    obj->emplace("Position", position);
    Server::InitIoC init;
    init.Execute();
    Server::IoC ioc;

    // регистрация зависимости создания адаптера
    Server::IoC::Generator<Server::IMovable, Server::PUObject> makeAdapter = [](Server::PUObject obj) {
        return std::make_shared<Server::AdapterIMovable>(obj);
    };
    ioc.Resolve<Server::ICommand, std::string, std::any>("IoC.Register", typeid(Server::IMovable).name(), makeAdapter)->Execute();

    // регистрация зависимости получения позиции из obj
    Server::IoC::Generator<Server::Vector, Server::PUObject> getPosition = [](Server::PUObject obj) {
        if(obj->find("Position") == obj->end())
            throw Server::Exception("No such property");

        return std::make_shared<Server::Vector>(std::any_cast<Server::Vector>(obj->at("Position")));
    };
    ioc.Resolve<Server::ICommand, std::string, std::any>("IoC.Register", "Server.IMovable.getPosition", getPosition)->Execute(); 

    // создание адаптера, проверка правильности работы его метода
    auto adapter = ioc.Resolve<Server::IMovable>(typeid(Server::IMovable).name(), obj);
    EXPECT_EQ(position, adapter->getPosition());
}
