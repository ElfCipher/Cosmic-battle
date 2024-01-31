#pragma once

#include "Exception.h"

class TestExc : public Server::Exception
{
    std::string msg = "Test exception";
public:
    virtual const char* what() const noexcept override {
        return msg.c_str();
    }
};