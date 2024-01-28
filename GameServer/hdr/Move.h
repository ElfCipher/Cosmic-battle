#pragma once

#include "Movable.h"

namespace Server
{

class Move : public IMovable
{
public:
    Move(Vector startPosition, Vector velocity);
    virtual ~Move() {}
    virtual void Execute();
};

} // namespace Server
