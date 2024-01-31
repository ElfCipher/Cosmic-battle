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
    int RegisterHandler(std::type_index cmd, std::type_index exc, Handler handler);
    PICommand Handle(PICommand cmd, const Exception& exc);

private:
    std::map<std::type_index, std::map<std::type_index, Handler>> store;
};

} // namespace Server
