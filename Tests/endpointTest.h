#pragma once

#include <gtest/gtest.h>
#include "Endpoint.h"
#include "ManualResetEvent.h"

TEST(ENDPOINT, RABBITMQ_CONNECT)
{
    using namespace Server;

    auto queue = std::make_shared<ConcurrentQueue<PICommand>>();
    Endpoint* endpoint = new Endpoint(queue);
    bool isEndpointStarted = false;
    ManualResetEvent mre;
    
    endpoint->Start([&](std::string result){
        isEndpointStarted = result == "OK";
        if(!isEndpointStarted)
            std::cerr << result << std::endl;
        mre.Set();
    });

    mre.WaitOne();
    EXPECT_TRUE(isEndpointStarted);

    queue->Get()->Execute();
    endpoint->Stop();

    delete endpoint;
}