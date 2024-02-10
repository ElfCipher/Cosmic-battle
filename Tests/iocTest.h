#pragma once

#include <gtest/gtest.h>
#include "IoC.h"

TEST(IOC, THROW_EXCEPTION)
{
    Server::IoC ioc;
    EXPECT_ANY_THROW(ioc.Resolve<int>("int"));
}

TEST(IOC, REGISTER_DEPENDENCY)
{
    Server::InitCmd<int> cmd;
    cmd.Execute();

    Server::IoC ioc;
    ioc.Resolve<Server::ICommand, std::string, Server::IoC::Generator<int>>("Register", "int", []() -> std::shared_ptr<int> {
        return std::make_shared<int>(5);
    })->Execute();

    EXPECT_EQ(*ioc.Resolve<int>("int"), 5);
}