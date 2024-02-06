#pragma once

#include "CommonHandlers.h"
#include <gtest/gtest.h>
#include "testClasses.h"

TEST(COMMON_HANDLERS, addLogCmdInQueue)
{
    Server::EventLoop& loop = Server::EventLoop::Locate();
    TestExc exc;
    auto cmd = std::make_shared<MockCommand>();    
    Server::addLogCmdInQueue(cmd, exc);
    EXPECT_EQ(loop.GetCommandsNum(), 1u);
    loop.Start();
    loop.Stop();
}

TEST(COMMON_HANDLERS, addRepeatCmdInQueue)
{
    Server::EventLoop& loop = Server::EventLoop::Locate();
    TestExc exc;
    auto cmd = std::make_shared<MockCommand>();
    EXPECT_CALL(*cmd, Execute());
    Server::addRepeatCmdInQueue(cmd, exc);
    EXPECT_EQ(loop.GetCommandsNum(), 1u);
    loop.Start();
    loop.Stop();
}

TEST(COMMON_HANDLERS, repeatAndLogInCase)
{
    TestExc exc;
    auto cmd = std::make_shared<MockCommand>();
    EXPECT_CALL(*cmd, Execute())
        .WillOnce(testing::Throw<TestExc>(TestExc()));
    auto ret = Server::repeatAndLogInCase(cmd, exc);
    EXPECT_EQ(typeid(*ret), typeid(Server::LogCommand));
}

TEST(COMMON_HANDLERS, repeatTwiceAndLog)
{
    TestExc exc;
    auto cmd = std::make_shared<MockCommand>();
    EXPECT_CALL(*cmd, Execute())
        .Times(2)
        .WillRepeatedly(testing::Throw<TestExc>(TestExc()));
    auto ret = Server::repeatTwiceAndLog(cmd, exc);
    EXPECT_EQ(typeid(*ret), typeid(Server::LogCommand));
}
