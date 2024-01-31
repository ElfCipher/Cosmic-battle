#pragma once

#include <exception>

namespace Server
{
    
class Exception : public std::exception
{
public:
    virtual const char* what() const noexcept = 0;
    virtual ~Exception() {};
};

} // namespace Server
