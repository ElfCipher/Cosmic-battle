#pragma once

#include <gtest/gtest.h>
#include "Endpoint.h"

TEST(ENDPOINT, RABBITMQ_CONNECT)
{
    Server::Endpoint* endpoint = new Server::Endpoint;
    bool isTestPassed = false;
    
    endpoint->Start([&](std::string result){
        endpoint->Stop();
        isTestPassed = result == "OK";
        if(!isTestPassed)
            std::cerr << result << std::endl;
    });

    if(!isTestPassed)
        FAIL();

    delete endpoint;
}