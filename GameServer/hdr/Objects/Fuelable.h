#pragma once

#include <stdint.h>
#include <memory>

namespace Server
{

class Fuelable
{
public:
    Fuelable(double fuel = 0.0, double moveBurningRate = 0.0, double rotateBurningRate = 0.0) :
        fuel(fuel),
        moveBurningRate(moveBurningRate),
        rotateBurningRate(rotateBurningRate) { }

    virtual ~Fuelable() { }

    double getFuel() {
        return fuel;
    }

    double getMoveBurningRate() {
        return moveBurningRate;
    }

    double getRotateBurningRate() {
        return rotateBurningRate;
    }

    void setFuel(double newFuel) {
        this->fuel = newFuel;
    }

protected:
    double fuel; // остаток топлива
    double moveBurningRate; // скорость сжигания топлива при движении на одну единицу
    double rotateBurningRate; //  скорость сжигания топлива при повороте на один сектор
};
    
using PFuelable = std::shared_ptr<Fuelable>;

} // namespace Server
