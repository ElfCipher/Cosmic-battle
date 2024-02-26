#pragma once

#include "CommonHandlers.h"
#include <gtest/gtest.h>
#include "testClasses.h"

TEST(COMMON_HANDLERS, addLogCmdInQueue)
{
    Server::PCQueue<Server::PICommand> queue = std::make_shared<Server::ConcurrentQueue<Server::PICommand>>();
    TestExc exc;
    auto cmd = std::make_shared<MockCommand>();    
    Server::Handler addLogCmdInQueue = [queue](Server::PICommand cmd, const Server::Exception& exc) -> Server::PICommand {
        queue->Put(std::make_shared<Server::LogCommand>(exc));
        return Server::makeDummy();
    };
    addLogCmdInQueue(cmd, exc);
    EXPECT_EQ(queue->GetSize(), 1u);
}

TEST(COMMON_HANDLERS, addRepeatCmdInQueue)
{
    Server::PCQueue<Server::PICommand> queue = std::make_shared<Server::ConcurrentQueue<Server::PICommand>>();
    TestExc exc;
    auto cmd = std::make_shared<MockCommand>();
    EXPECT_CALL(*cmd, Execute());
    Server::Handler addRepeatCmdInQueue = [queue](Server::PICommand cmd, const Server::Exception& exc) -> Server::PICommand {
        queue->Put(std::make_shared<Server::RepeatCommand>(cmd));
        return Server::makeDummy();
    };
    addRepeatCmdInQueue(cmd, exc);
    EXPECT_EQ(queue->GetSize(), 1u);
    queue->Get()->Execute();
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
