#pragma once

#include "Objects/Movable.h"
#include "ICommand.h"

namespace Server
{

class Move : public ICommand
{
public:
    Move(PIMovable m);
    virtual ~Move() {}
    virtual void Execute() override;

    PIMovable m;
};

} // namespace Server
