#pragma once

#include "Movable.h"
#include "ICommand.h"
#include <memory>

namespace Server
{

class Move : public ICommand
{
public:
    Move(std::shared_ptr<IMovable> m);
    virtual ~Move() {}
    virtual void Execute() override;

    std::shared_ptr<IMovable> m;
};

} // namespace Server
