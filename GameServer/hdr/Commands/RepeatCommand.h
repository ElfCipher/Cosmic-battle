#pragma once

#include "ICommand.h"

namespace Server
{

/**
 * @brief Повторяет команду
 */
class RepeatCommand : public ICommand
{
public:
    RepeatCommand(PICommand cmd) :
        cmd(cmd) { }
    virtual ~RepeatCommand() {}

    virtual void Execute() override {
        cmd->Execute();
    }

protected:
    PICommand cmd;
};

} // namespace Server
