#pragma once

#include <gtest/gtest.h>
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

TEST(EVENT_LOOP, CMD_EXECUTING)
{
    Server::EventLoop& loop = Server::EventLoop::Locate();
    loop.Start();

    auto cmd = std::make_shared<MockCommand>();
    EXPECT_CALL(*cmd, Execute());

    loop.Put(cmd);
    loop.Stop();
}

TEST(EVENT_LOOP, CATCHING_EXCEPTION)
{
    Server::EventLoop& loop = Server::EventLoop::Locate();
    loop.Start();

    auto cmd = std::make_shared<MockCommand>();
    EXPECT_CALL(*cmd, Execute())
        .Times(2)   // сначала обычный вызов, а потом повторный вызов из mock_handler
        .WillOnce(testing::Throw<TestExc>(TestExc()))
        .WillOnce(testing::Return());

    loop.GetHandler().RegisterHandler(typeid(MockCommand), typeid(TestExc), mock_handler);

    loop.Put(cmd);
    loop.Stop();
}
