#pragma once

#include <stdint.h>

namespace Server
{

struct Vector
{
    int64_t x, y;

    Vector(int64_t x, int64_t y): x(x), y(y) { }
    Vector(): x(0), y(0) { }
    Vector(const Vector& other)
    {
        this->x = other.x;
        this->y = other.y;
    }
    Vector& operator=(const Vector& other)
    {
        this->x = other.x;
        this->y = other.y;
        return *this;
    }
    Vector& operator+(const Vector& other)
    {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }
    friend bool operator==(const Vector& first, const Vector& second)
    {
        return first.x == second.x && first.y == second.y;
    }
    friend bool operator!=(const Vector& first, const Vector& second)
    {
        return first.x != second.x || first.y != second.y;
    }
};

class IMovable
{
public:
    IMovable(Vector velocity, Vector position) :
        velocity(velocity), position(position) {}
    
    virtual ~IMovable() {}

    Vector getPosition() {
        return position;
    }
    Vector getVelocity() {
        return velocity;
    }
    void setPosition(Vector newV) {
        position = newV;
    }
    
protected:
    Vector velocity; // проекции вектора скорости на оси
    Vector position;
};

} // namespace Server
