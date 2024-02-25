#pragma once

#include <gtest/gtest.h>
#include "EventLoop.h"
#include "testClasses.h"
#include "StartLoop.h"
#include "HardStopLoop.h"
#include "SoftStopLoop.h"
#include "ManualResetEvent.h"

TEST(EVENT_LOOP, START)
{
    Server::PCQueue<Server::PICommand> queue = std::make_shared<Server::ConcurrentQueue<Server::PICommand>>();
    Server::EventLoop loop(queue);
    Server::StartLoop start(loop);
    
    start.Execute();

    EXPECT_TRUE(loop.IsStarted());
}

// создаём мок-команды. часть добавляем до старта потока, часть после
TEST(EVENT_LOOP, CMD_EXECUTING)
{
    Server::PCQueue<Server::PICommand> queue = std::make_shared<Server::ConcurrentQueue<Server::PICommand>>();
    Server::EventLoop loop(queue);

    std::map<int, Server::PICommand> cmds;
    for(int i = 0; i < 10; ++i)
    {
        auto cmd = std::make_shared<MockCommand>();
        EXPECT_CALL(*cmd, Execute());
        cmds[i] = cmd;
    }

    for(int i = 0; i < 5; ++i)
        queue->Put(cmds[i]);

    loop.Start();
    EXPECT_TRUE(loop.IsStarted());

    for(int i = 5; i < 10; ++i)
        queue->Put(cmds[i]);
}

TEST(EVENT_LOOP, CATCHING_EXCEPTION)
{
    Server::PCQueue<Server::PICommand> queue = std::make_shared<Server::ConcurrentQueue<Server::PICommand>>();
    Server::EventLoop loop(queue);
    loop.Start();

    auto cmd = std::make_shared<MockCommand>();
    EXPECT_CALL(*cmd, Execute())
        .Times(2)   // сначала обычный вызов, а потом повторный вызов из mock_handler
        .WillOnce(testing::Throw<TestExc>(TestExc()))
        .WillOnce(testing::Return());

    loop.GetHandler().RegisterHandler(typeid(MockCommand), typeid(TestExc), mock_handler);

    queue->Put(cmd);
}


// первая половина команда должна выполниться, а вторая (после команды остановки потока) - нет
TEST(EVENT_LOOP, HARD_STOP)
{
    Server::PCQueue<Server::PICommand> queue = std::make_shared<Server::ConcurrentQueue<Server::PICommand>>();
    Server::EventLoop loop(queue);

    for(int i = 0; i < 5; ++i)
    {
        auto cmd = std::make_shared<MockCommand>();
        EXPECT_CALL(*cmd, Execute());
        queue->Put(cmd);
    }
    
    Server::ManualResetEvent mre;
    auto hsCmd = std::make_shared<Server::HardStopLoop>(loop, [&mre](){
        mre.Set();
    });
    queue->Put(hsCmd);

    for(int i = 0; i < 5; ++i)
    {
        auto cmd = std::make_shared<MockCommand>();
        EXPECT_CALL(*cmd, Execute())
            .Times(0);
        queue->Put(cmd);
    }

    loop.Start();
    mre.WaitOne();
    EXPECT_FALSE(loop.IsStarted());
}

TEST(EVENT_LOOP, SOFT_STOP)
{
    Server::PCQueue<Server::PICommand> queue = std::make_shared<Server::ConcurrentQueue<Server::PICommand>>();
    Server::EventLoop loop(queue);
    Server::ManualResetEvent mre;

    for(int i = 0; i < 10; ++i)
    {
        if(i == 5)
        {
            auto cmd = std::make_shared<Server::SoftStopLoop>(loop, [&mre](){
                mre.Set();
            });    
            queue->Put(cmd);
            continue;
        }

        auto cmd = std::make_shared<MockCommand>();
        EXPECT_CALL(*cmd, Execute());
        queue->Put(cmd);
    }

    loop.Start();
    mre.WaitOne();
    EXPECT_FALSE(loop.IsStarted());
    EXPECT_EQ(queue->GetSize(), 0);
}
