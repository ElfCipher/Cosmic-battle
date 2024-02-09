#pragma once

#include <stdint.h>
#include <memory>

namespace Server
{

class IRotable
{
public:
    IRotable(int direction = 0, int angularVelocity = 0) :
        direction(direction),
        angularVelocity(angularVelocity),
        directionsNumber(360) {}
    
    virtual ~IRotable() {}

    int getDirection() {
        return direction;
    }
    int getAngularVelocity() {
        return angularVelocity;
    }
    void setDirection(int newV) {
        direction = newV;
    }
    int getDirectionsNumber() {
        return directionsNumber;
    }
    
protected:
    int direction,
    angularVelocity,
    directionsNumber;
};

using PIRotable = std::shared_ptr<IRotable>;

} // namespace Server
