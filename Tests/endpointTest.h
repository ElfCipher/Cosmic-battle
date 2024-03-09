#pragma once

#include <gtest/gtest.h>
#include "Endpoint.h"

TEST(ENDPOINT, RABBITMQ_CONNECT)
{
    
    Server::Endpoint* endpoint = new Server::Endpoint;

    endpoint->Start([=](std::string result){
        endpoint->Stop();
        if(result == "OK")
            SUCCEED();
        else
        {
            std::cerr << result << std::endl;
            FAIL();
        }
    });
}