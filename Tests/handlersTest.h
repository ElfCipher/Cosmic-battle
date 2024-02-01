#pragma once

#include "CommonHandlers.h"
#include <gtest/gtest.h>
#include "testClasses.h"

TEST(COMMON_HANDLERS, addLogCmdInQueue)
{
    
}

TEST(COMMON_HANDLERS, addRepeatCmdInQueue)
{
    
}

TEST(COMMON_HANDLERS, repeateAndLogInCase)
{
    TestExc exc;
    auto cmd = std::make_shared<MockCommand>();
    EXPECT_CALL(*cmd, Execute())
        .WillOnce(testing::Throw<TestExc>(TestExc()));
    Server::repeateAndLogInCase(cmd, exc);
}
