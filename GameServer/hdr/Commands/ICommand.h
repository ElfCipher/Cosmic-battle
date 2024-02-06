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

class DummyCommand : public ICommand
{
public:
    virtual void Execute() override { };
    virtual ~DummyCommand() {}
};

static auto makeDummy = []() {
    return std::make_shared<DummyCommand>();
};

} // namespace Server
