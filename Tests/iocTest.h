#pragma once

#include <gtest/gtest.h>
#include "InitIoC.h"
#include <future>

TEST(IOC, INITIALIZATION)
{
    Server::InitIoC init;
    init.Execute();
}

TEST(IOC, THROW_EXCEPTION)
{
    Server::IoC ioc;
    EXPECT_THROW(ioc.Resolve<int>("int"), Server::ArgumentException);
}

TEST(IOC, REGISTER_DIFFERENT_DEPENDENCIES)
{
    Server::InitIoC init;
    init.Execute();

    Server::IoC ioc;

    Server::IoC::Generator<int> foo = []() -> std::shared_ptr<int> {
        return std::make_shared<int>(5);
    };
    ioc.Resolve<Server::ICommand, std::string, std::any>("IoC.Register", "int", foo)->Execute();

    Server::IoC::Generator<int, int> foo1 = [](int a) -> std::shared_ptr<int> {
        return std::make_shared<int>(a);
    };
    ioc.Resolve<Server::ICommand, std::string, std::any>("IoC.Register", "int1", foo1)->Execute();

    Server::IoC::Generator<double> foo2 = []() {
        return std::make_shared<double>(7.0);
    };
    ioc.Resolve<Server::ICommand, std::string, std::any>("IoC.Register", "double", foo2)->Execute();

    EXPECT_EQ(*ioc.Resolve<int>("int"), 5);
    EXPECT_EQ(*ioc.Resolve<int>("int1", 6), 6);
    EXPECT_DOUBLE_EQ(*ioc.Resolve<double>("double"), 7.0);
}

TEST(IOC, CREATE_SCOPE)
{
    Server::InitIoC init;
    init.Execute();

    Server::IoC ioc;
    auto scope1 = ioc.Resolve<Server::IoC::Scope, Server::IoC::PScope>("IoC.Scope.New", nullptr);
    auto scope2 = ioc.Resolve<Server::IoC::Scope, Server::IoC::PScope>("IoC.Scope.New", scope1);
    EXPECT_EQ(typeid(scope1), typeid(Server::IoC::PScope));
    EXPECT_THROW(ioc.Resolve<Server::IoC::Scope>("IoC.Scope.Parent"), Server::Exception);

    ioc.Resolve<Server::ICommand, Server::IoC::PScope>("IoC.Scope.Current.Set", scope2)->Execute();
    auto parent = ioc.Resolve<Server::IoC::Scope>("IoC.Scope.Parent");
    EXPECT_TRUE(parent == scope1);
}


// в разных потоках текущие скоупы будут разные
TEST(IOC, DIFFERENT_THREAD)
{
    Server::InitIoC init;
    init.Execute();
    Server::IoC ioc;

    auto scope1 = ioc.Resolve<Server::IoC::Scope, Server::IoC::PScope>("IoC.Scope.New", nullptr);
    ioc.Resolve<Server::ICommand, Server::IoC::PScope>("IoC.Scope.Current.Set", scope1)->Execute();

    auto foo = [&ioc]() -> size_t {
        auto current2 = ioc.Resolve<Server::IoC::Scope>("IoC.Scope.Current");
        return reinterpret_cast<size_t>(current2.get());
    };

    auto fid = std::async(std::launch::async, foo);
    fid.wait();
    auto current1 = ioc.Resolve<Server::IoC::Scope>("IoC.Scope.Current");
    auto id1 = reinterpret_cast<size_t>(current1.get());
    auto id2 = fid.get();

    EXPECT_NE(id1, id2);
    EXPECT_EQ(current1, scope1);
    EXPECT_EQ(id2, reinterpret_cast<size_t>(Server::IoC::rootScope.get()));
}
