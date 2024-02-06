#pragma once

#include "RepeatCommand.h"

namespace Server
{

class DoubleRepeat : public RepeatCommand
{
public:
    DoubleRepeat(PICommand cmd) :
        RepeatCommand(cmd) { }
    virtual ~DoubleRepeat() {}
};

} // namespace Server
