#pragma once

#include "ICommand.h"

namespace Server
{

/**
 * @brief Повторяет команду
 */
class RepeateCommand : public ICommand
{
public:
    RepeateCommand(PICommand cmd) :
        cmd(cmd) { }
    virtual ~RepeateCommand() {}

    virtual void Execute() override {
        cmd->Execute();
    }

protected:
    PICommand cmd;
};

} // namespace Server
