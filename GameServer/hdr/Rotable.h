#pragma once

#include <stdint.h>

namespace Server
{

class IRotable
{
public:
    IRotable(int angularVelocity) :
        direction(0),
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

} // namespace Server
