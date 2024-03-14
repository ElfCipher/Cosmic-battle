#include "InterpretCommand.h"
#include "IoC.h"
#include "CommandsHolder.h"
#include <jsoncpp/json/json.h>

namespace Server
{
    
InterpretCommand::InterpretCommand(const CommonMessage &msg, PCQueue<PICommand> queue, PUObjects objects) :
    msg(msg),
    queue(queue),
    objects(objects)
{
}

void InterpretCommand::Execute()
{
    auto objectIt = objects->find(msg.objectId);
    if(objectIt == objects->end())
        return;

    auto command = CommandsHolder::Locate().GetDependency(msg.operationId).append("Json");
    if(command == "")
        return;
    
    Json::Value root;
    Json::Reader reader;
    reader.parse(msg.json, root);
    auto args = root["Args"];
    
    queue->Put(IoC::Resolve<ICommand>(command, args, objectIt->second)); // т.е. нужна зависимость, в которой создаётся команда по аргументам из Json для этого объекта
}

} // namespace Server
