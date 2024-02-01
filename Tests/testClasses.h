#pragma once

#include "Exception.h"
#include "ICommand.h"
#include <gmock/gmock.h>

class TestExc : public Server::Exception
{
    std::string msg = "Test exception";
public:
    virtual const char* what() const noexcept override {
        return msg.c_str();
    }
};

class MockCommand : public Server::ICommand
{
public:
    MOCK_METHOD(void, Execute, (), (override));
};