#pragma once

#include <stdint.h>
#include <memory>

namespace Server
{

// [[Adaptable]]
class IRotable
{
public:
    virtual int getDirection() = 0;
    virtual int getAngularVelocity() = 0;
    virtual void setDirection(int newV) = 0;
    virtual int getDirectionsNumber() = 0;
};

using PIRotable = std::shared_ptr<IRotable>;

} // namespace Server
