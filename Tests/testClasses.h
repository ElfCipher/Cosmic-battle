#pragma once

#include "ExceptionHandler.h"
#include <Objects/IMovable.h>
#include <Objects/IRotable.h>
#include <Objects/IFuelable.h>
#include <gmock/gmock.h>

class TestMovable : public Server::IMovable
{
public:
    TestMovable(Server::Vector velocity = Server::Vector(), Server::Vector position = Server::Vector()) :
        velocity(velocity), position(position) {}
    
    virtual ~TestMovable() {}

    Server::Vector getPosition() override {
        return position;
    }
    Server::Vector getVelocity() override {
        return velocity;
    }
    void setPosition(Server::Vector newV) override {
        position = newV;
    }
    void setVelocity(Server::Vector newV) override {
        velocity = newV;
    }
    
protected:
    Server::Vector velocity; // проекции вектора скорости на оси
    Server::Vector position;
};

class TestRotable : public Server::IRotable
{
public:
    TestRotable(int direction = 0, int angularVelocity = 0) :
        direction(direction),
        angularVelocity(angularVelocity),
        directionsNumber(360) {}
    
    virtual ~TestRotable() {}

    virtual int getDirection() override {
        return direction;
    }
    virtual int getAngularVelocity() override {
        return angularVelocity;
    }
    virtual void setDirection(int newV) override {
        direction = newV;
    }
    virtual int getDirectionsNumber() override {
        return directionsNumber;
    }
    
protected:
    int direction,
    angularVelocity,
    directionsNumber;
};

class TestFuelable : public Server::IFuelable
{
public:
    TestFuelable(double fuel = 0.0, double burningRate = 0.0) :
        fuel(fuel),
        burningRate(burningRate){ }

    virtual ~TestFuelable() { }

    virtual double getFuel() override {
        return fuel;
    }

    virtual double getBurningRate() override {
        return burningRate;
    }

    virtual void setFuel(double newFuel) override {
        this->fuel = newFuel;
    }

protected:
    double fuel; // остаток топлива
    double burningRate; // скорость сжигания топлива при движении/вращении на одну единицу
};

class TestExc : public Server::Exception
{
public:
    TestExc() {
        msg = "Test exception";
    }
    virtual ~TestExc() {}
};

class MockCommand : public Server::ICommand
{
public:
    MOCK_METHOD(void, Execute, (), (override));
};

Server::Handler mock_handler = [](Server::PICommand cmd, const Server::Exception& exc) -> Server::PICommand {
    return cmd;
};
