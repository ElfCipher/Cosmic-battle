#pragma once

#include <exception>

namespace Server
{
    
class Exception : public std::exception
{
public:
    Exception() {};
    virtual ~Exception() {};
};

} // namespace Server
