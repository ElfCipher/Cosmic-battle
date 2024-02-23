#pragma once

#include <stdint.h>
#include <memory>

namespace Server
{

// [[Adaptable]]
class IFuelable
{
public:
    virtual double getFuel() = 0;
    virtual double getBurningRate() = 0;
    virtual void setFuel(double newFuel) = 0;
};
    
using PIFuelable = std::shared_ptr<IFuelable>;

} // namespace Server
