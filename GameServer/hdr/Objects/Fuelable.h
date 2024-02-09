#pragma once

#include <stdint.h>
#include <memory>

namespace Server
{

class Fuelable
{
public:
    Fuelable(double fuel = 0.0, double burningRate = 0.0) :
        fuel(fuel),
        burningRate(burningRate){ }

    virtual ~Fuelable() { }

    double getFuel() {
        return fuel;
    }

    double getBurningRate() {
        return burningRate;
    }

    void setFuel(double newFuel) {
        this->fuel = newFuel;
    }

protected:
    double fuel; // остаток топлива
    double burningRate; // скорость сжигания топлива при движении/вращении на одну единицу
};
    
using PFuelable = std::shared_ptr<Fuelable>;

} // namespace Server
