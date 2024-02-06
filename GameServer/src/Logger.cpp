#include "Logger.h"

namespace Server
{

Logger &Logger::Locate()
{
    static Logger logger;
    return logger;
}

Logger::Logger() :
    s(std::cout.rdbuf())
{
    // можно считать конфиг и узнать, куда логгировать
}

void Logger::Log(const std::string &str)
{
    s << str << std::endl;
}

} // namespace Server
