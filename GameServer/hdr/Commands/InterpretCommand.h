#pragma once

#include "ICommand.h"
#include "ConcurrentQueue.h"

namespace Server
{

struct CommonMessage
{
    uint64_t gameId;
    uint64_t objectId;
    uint64_t operationId;
    std::string json;
};

    
class InterpretCommand : public ICommand
{
public:
    InterpretCommand(const CommonMessage& msg, PCQueue<PICommand> queue);
    virtual ~InterpretCommand() {}

    virtual void Execute() override;

private:
    CommonMessage msg;
    PCQueue<PICommand> queue;
};

} // namespace Server
