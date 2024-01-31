#include "ExceptionHandler.h"
#include "Exception.h"
#include "ICommand.h"

namespace Server
{

int ExceptionHandler::RegisterHandler(std::type_index cmd, std::type_index exc, Handler handler)
{
    store[cmd][exc] = handler;
    return 0;
}

PICommand ExceptionHandler::Handle(PICommand cmd, const Exception& exc)
{
    auto cmdT = std::type_index(typeid(cmd));
    auto excT = std::type_index(typeid(exc));
    return store[cmdT][excT](cmd, exc);
}

} // namespace Server
