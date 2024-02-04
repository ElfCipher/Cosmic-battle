#pragma once

#include <gtest/gtest.h>
#include "Move.h"
#include "Rotate.h"
#include "EventLoop.h"
#include "LogCommand.h"
#include "testClasses.h"
#include "RepeatCommand.h"
#include "MacroCommand.h"
#include "CheckFuelCommand.h"
#include "BurnFuelCommand.h"
#include "MoveWithBurning.h"
#include "ChangeVelocityCommand.h"
#include "RotateWithVelocity.h"

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


// LogCommand test
TEST(LOG_COMMAND, LOGGING)
{
    TestExc exc;
    Server::LogCommand cmd(exc);
    EXPECT_NO_THROW(cmd.Execute());
}

// RepeatCommand test
TEST(REPEAT_COMMAND, REPEAT)
{
    auto cmd = std::make_shared<MockCommand>();
    EXPECT_CALL(*cmd, Execute());
    Server::RepeatCommand rcmd(cmd);
    rcmd.Execute();
}

TEST(MACRO_COMMAND, CMD_WITH_EXCEPTION)
{
    std::list<Server::PICommand> cmds;
    auto cmd1 = std::make_shared<MockCommand>();
    auto cmd2 = std::make_shared<MockCommand>();
    EXPECT_CALL(*cmd1, Execute());
    EXPECT_CALL(*cmd2, Execute())
        .WillOnce(testing::Throw<TestExc>(TestExc()));
    cmds.push_back(cmd1);
    cmds.push_back(cmd2);
    Server::MacroCommand macro(cmds);
    EXPECT_ANY_THROW(macro.Execute());
}


// Тесты сижагания топлива
TEST(FUEL_OBJECT, INTERFACE_TEST)
{
    Server::Fuelable fuelable(100.0, 2.0);
    EXPECT_DOUBLE_EQ(fuelable.getFuel(), 100.0);
    EXPECT_DOUBLE_EQ(fuelable.getBurningRate(), 2.0);

    fuelable.setFuel(50.0);
    EXPECT_DOUBLE_EQ(fuelable.getFuel(), 50.0);
}

TEST(CHECK_FUEL_COMMAND, CHECKING)
{
    Server::PFuelable fuelable = std::make_shared<Server::Fuelable>(100.0, 2.0);
    Server::CheckFuelCommand cmd(fuelable);
    EXPECT_NO_THROW(cmd.Execute());

    fuelable->setFuel(2.0);
    EXPECT_NO_THROW(cmd.Execute());
    
    fuelable->setFuel(1.0);
    EXPECT_ANY_THROW(cmd.Execute());
}

TEST(BURN_FUEL_COMMAND, BIRNUNG)
{
    auto fuelable = std::make_shared<Server::Fuelable>(100.0, 2.0);
    Server::BurnFuelCommand cmd(fuelable);

    cmd.Execute();
    EXPECT_DOUBLE_EQ(fuelable->getFuel(), 100.0-2.0);
}


// Движение и сжигание топлива
TEST(MOVE_WITH_BURNING_CMD, MOVE_AND_BURN_FUEL)
{
    Server::Vector startPosition(0, 0);
    Server::Vector velocity(2, 2);
    auto movable = std::make_shared<Server::IMovable>(velocity, startPosition);
    auto fuelable = std::make_shared<Server::Fuelable>(100.0, 2.0);

    Server::MoveWithBurning cmd(movable, fuelable);
    cmd.Execute();

    EXPECT_EQ(movable->getPosition(), startPosition + velocity);
    EXPECT_DOUBLE_EQ(fuelable->getFuel(), 100.0 - 2.0);
}


// Изменение вектора скорости
TEST(CHANGE_VELOCITY_COMMAND, RIGHT_ROTATION)
{
    Server::Vector velocity(0, 100); // вектор скорости = 90 гр
    auto movable = std::make_shared<Server::IMovable>(velocity);

    Server::ChangeVelocityCommand cmd(movable, 0.0); // поворот к 0 гр
    cmd.Execute();
    Server::Vector expectedVelocity(100, 0);
    EXPECT_EQ(movable->getVelocity(), expectedVelocity);
}

TEST(CHANGE_VELOCITY_COMMAND, LEFT_ROTATION)
{
    Server::Vector velocity(100, 0); // вектор скорости = 0 гр
    auto movable = std::make_shared<Server::IMovable>(velocity);

    Server::ChangeVelocityCommand cmd(movable, -135.0); // поворот к -135 гр
    cmd.Execute();
    Server::Vector expectedVelocity(-70, -70);
    EXPECT_EQ(movable->getVelocity(), expectedVelocity);
}

TEST(CHANGE_VELOCITY_COMMAND, ZERO_VELOCITY)
{
    auto movable = std::make_shared<Server::IMovable>(); // 0й вектор скорости

    Server::ChangeVelocityCommand cmd(movable, -15.0); // поворот к -15 гр
    cmd.Execute();
    Server::Vector expectedVelocity(0, 0);
    EXPECT_EQ(movable->getVelocity(), expectedVelocity);
}


// Тест поворота с изменением вектора скорости
TEST(ROTATE_WITH_VELOCITY, ROTATE)
{
    Server::Vector velocity(0, 100); // вектор скорости = 90 гр
    auto movable = std::make_shared<Server::IMovable>(velocity);

    int startDirection = 0;
    int angularVelocity = 10;
    auto rotable = std::make_shared<Server::IRotable>(startDirection, angularVelocity);

    Server::RotateWithVelocity cmd(rotable, movable);
    EXPECT_NO_THROW(cmd.Execute());

    int expectedDirection = 10; // 0 + 10
    EXPECT_EQ(expectedDirection, rotable->getDirection());   

    Server::Vector expectedVelocity(-17, 98); // вектор скорости повернулся к 100 градусам (90 + 10)
    EXPECT_EQ(movable->getVelocity(), expectedVelocity);
}
