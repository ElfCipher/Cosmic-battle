#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "EventLoop.h"
#include "testClasses.h"

TEST(EVENT_LOOP, LOOP_LIFE)
{
    Server::EventLoop& loop = Server::EventLoop::Locate();
    loop.Start();
    EXPECT_TRUE(loop.IsStarted());
    loop.Stop();
    EXPECT_FALSE(loop.IsStarted());
}

class MockCommand : public Server::ICommand
{
public:
    MOCK_METHOD(void, Execute, (), (override));
};

TEST(EVENT_LOOP, CMD_EXECUTING)
{
    Server::EventLoop& loop = Server::EventLoop::Locate();
    loop.Start();

    auto cmd = std::make_shared<MockCommand>();
    EXPECT_CALL(*cmd, Execute())
        .WillOnce(testing::Throw<TestExc>(TestExc()));

    loop.Put(cmd);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    loop.Stop();
}
