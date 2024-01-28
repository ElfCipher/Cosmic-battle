#pragma once

#include "Rotable.h"

namespace Server
{

class Rotate : public IRotable
{
public:
    Rotate(int direction, int angularVelocity);
    virtual ~Rotate() {}
    virtual void Execute();
};

} // namespace Server
