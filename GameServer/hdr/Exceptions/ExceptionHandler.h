#pragma once

#include <map>
#include <functional>
#include <typeindex>
#include "ICommand.h"

namespace Server
{

class Exception;

using Handler = std::function<PICommand(PICommand, const Exception&)>;

class ExceptionHandler
{
public:
    virtual ~ExceptionHandler() {}
    int RegisterHandler(std::type_index cmd, std::type_index exc, Handler handler);
    virtual PICommand Handle(PICommand cmd, const Exception& exc);

private:
    // у каждой команды есть свои исключения, которые обрабатываются свои хэнделором
    std::map<std::type_index, std::map<std::type_index, Handler>> store;
};

} // namespace Server
