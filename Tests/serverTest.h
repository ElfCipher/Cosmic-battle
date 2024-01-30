#pragma once

#include <gtest/gtest.h>
#include "Move.h"
#include "Rotate.h"
#include "EventLoop.h"
#include "Exception.h"

// Проверка правильности движения    
TEST(MOVABLE, MOVE_TEST)
{
    Server::Vector startPosition(12, 5);
    Server::Vector velocity(-7, 3);
    auto movable = std::make_shared<Server::IMovable>(startPosition, velocity);
    Server::Move move(movable);
    move.Execute();
    Server::Vector finishPosition = movable->getPosition();
    Server::Vector expectedPosition(5, 8);
    EXPECT_EQ(expectedPosition, finishPosition);
}

// Проверка невозможности прочитать/изменить состояние
TEST(MOVABLE, INTERFACE_TEST)
{
    Server::Vector startPosition(12, 5);
    Server::Vector velocity(-7, 3);
    auto movable = std::make_shared<Server::IMovable>(velocity, startPosition);

    EXPECT_EQ(startPosition, movable->getPosition()); // читаем положение

    EXPECT_EQ(velocity, movable->getVelocity()); // читаем скорость

    Server::Vector newPosition(10, 10);
    movable->setPosition(newPosition);
    EXPECT_EQ(newPosition, movable->getPosition()); // объект меняет положение
}



// Проверка правильности поворота
TEST(ROTABLE, ROTATE_TEST)
{
    int startDirection = 0;
    int angularVelocity = 10;
    auto rotable = std::make_shared<Server::IRotable>(startDirection, angularVelocity);
    Server::Rotate rotate(rotable);
    rotate.Execute();
    int finishDirection = rotable->getDirection();
    int expectedDirection = 10;
    EXPECT_EQ(expectedDirection, finishDirection);

}

// Проверка возможности прочитать/изменить состояние
TEST(ROTABLE, INTERFACE_TEST)
{
    int startDirection = 0;
    int angularVelocity = 10;
    auto rotable = std::make_shared<Server::IRotable>(startDirection, angularVelocity);

    EXPECT_EQ(startDirection, rotable->getDirection()); // читаем направление

    EXPECT_EQ(angularVelocity, rotable->getAngularVelocity()); // читаем угловую скорость
    
    int newDirection = -15;
    rotable->setDirection(newDirection);
    EXPECT_EQ(newDirection, rotable->getDirection());
}


class TestExc : public Server::Exception
{
    std::string msg = "Test exception";
public:
    virtual const char* what() const noexcept override {
        return msg.c_str();
    }
};

class TestCmd : public Server::ICommand
{
    virtual void Execute()
    {
        throw TestExc();
    }
};

TEST(EVENT_LOOP, LOOP_LIFE)
{
    Server::EventLoop& loop = Server::EventLoop::Locate();
    loop.Start();
    EXPECT_TRUE(loop.IsStarted());

    loop.Put(std::make_shared<TestCmd>()); // TODO: check catching exception
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    loop.Stop();
    EXPECT_FALSE(loop.IsStarted());
}