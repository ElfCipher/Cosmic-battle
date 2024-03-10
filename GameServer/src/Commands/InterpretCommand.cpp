#include "InterpretCommand.h"
#include "IoC.h"

namespace Server
{
    
InterpretCommand::InterpretCommand(const CommonMessage &msg, PCQueue<PICommand> queue) :
    msg(msg),
    queue(queue)
{
}

void InterpretCommand::Execute()
{
    queue->Put(IoC::Resolve<ICommand>("")); // TODO: реализовать команду
}

} // namespace Server
