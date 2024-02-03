#pragma once

#include "ExceptionHandler.h"
#include <gmock/gmock.h>

class TestExc : public Server::Exception
{
public:
    TestExc() {
        msg = "Test exception";
    }
    virtual ~TestExc() {}
};

class MockCommand : public Server::ICommand
{
public:
    MOCK_METHOD(void, Execute, (), (override));
};

Server::Handler mock_handler = [](Server::PICommand cmd, const Server::Exception& exc) -> Server::PICommand {
    return cmd;
};
