#pragma once

namespace Server
{

class ICommand
{
public:
    virtual void Execute() = 0;
};

} // namespace Server
