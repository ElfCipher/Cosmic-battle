#pragma once

#include <exception>

namespace Server
{
    
class Exception : public std::exception
{
public:
    Exception() {}
    Exception(const std::string& msg) : 
        msg(msg) {}
    virtual const char* what() const noexcept final {
        return msg.c_str();
    }
    virtual ~Exception() {};
protected:
    std::string msg;
};

} // namespace Server
