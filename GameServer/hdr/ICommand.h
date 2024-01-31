#pragma once

#include <memory>

namespace Server
{

class ICommand
{
public:
    virtual void Execute() = 0;
    virtual ~ICommand() { };
};

using PICommand = std::shared_ptr<ICommand>;

} // namespace Server
