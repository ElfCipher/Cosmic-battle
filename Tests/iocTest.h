#pragma once

#include <gtest/gtest.h>
#include "IoC.h"

TEST(IOC, THROW_EXCEPTION)
{
    Server::IoC ioc;
    EXPECT_THROW(ioc.Resolve<int>("int"), Server::ArgumentException);

    auto foo = [ioc](){ // отдельная функция, чтобы макрос сработал
        ioc.Resolve<Server::ICommand, std::string, Server::IoC::Generator<int>>("IoC.Register", "int", []() {
            return std::make_shared<int>(5);
        })->Execute();
    };

    EXPECT_THROW(foo(), Server::ArgumentException);
}

TEST(IOC, REGISTER_DEPENDENCY)
{
    Server::InitCmd<int> initInt;
    Server::InitCmd<double> initDouble;
    initInt.Execute();
    initDouble.Execute();

    Server::IoC ioc;
    ioc.Resolve<Server::ICommand, std::string, Server::IoC::Generator<int>>("IoC.Register", "int", []() {
        return std::make_shared<int>(5);
    })->Execute();

    ioc.Resolve<Server::ICommand, std::string, Server::IoC::Generator<double>>("IoC.Register", "double", []() {
        return std::make_shared<double>(7.0);
    })->Execute();

    EXPECT_EQ(*ioc.Resolve<int>("int"), 5);
    EXPECT_DOUBLE_EQ(*ioc.Resolve<double>("double"), 7.0);
}

TEST(IOC, CREATE_SCOPE)
{
    Server::InitCmd<int> initInt;
    initInt.Execute();

    Server::IoC ioc;
    auto ret = ioc.Resolve<Server::IoC::Map>("IoC.Scope.New");
    
    EXPECT_EQ(typeid(ret), typeid(Server::IoC::PMap));
    EXPECT_TRUE(ret->empty());
}
