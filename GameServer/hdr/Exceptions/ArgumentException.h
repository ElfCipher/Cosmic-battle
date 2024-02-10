#pragma once

#include "Exception.h"

namespace Server
{

class ArgumentException : public Exception
{
public:
    ArgumentException(const std::string& dependency)
    {
        msg = std::string("Dependency ").append(dependency).append(" is not found.");
    }
    virtual ~ArgumentException() {}
};

} // namespace Server
