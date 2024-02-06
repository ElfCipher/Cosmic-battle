#pragma once

#include <string>
#include <iostream>

namespace Server
{

class Logger
{
public:
    static Logger& Locate();
    virtual void Log(const std::string& str);
    virtual ~Logger() {}
    
private:
    Logger();

protected:
    std::ostream s;
};

} // namespace Server
