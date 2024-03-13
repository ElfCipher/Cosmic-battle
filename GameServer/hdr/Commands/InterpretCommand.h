#pragma once

#include "ICommand.h"
#include "ConcurrentQueue.h"
#include "UObject.h"
#include "MessageFormat.h"

namespace Server
{
    
class InterpretCommand : public ICommand
{
public:
    /**
     * @param msg входящее сообщение от Агента
     * @param queue очередь команд игры
     * @param objects игровые объекты
     */
    InterpretCommand(const CommonMessage& msg, PCQueue<PICommand> queue, PUObjects objects);
    virtual ~InterpretCommand() {}

    virtual void Execute() override;

private:
    CommonMessage msg;
    PCQueue<PICommand> queue;
    PUObjects objects;
};

} // namespace Server
