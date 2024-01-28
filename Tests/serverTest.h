#pragma once

#include <gtest/gtest.h>
#include "Move.h"
#include "Rotate.h"

// Проверка правильности движения    
TEST(MOVABLE, MOVE_TEST)
{
    Server::Vector startPosition(12, 5);
    Server::Vector velocity(-7, 3);
    Server::Move move(startPosition, velocity);
    move.Execute();
    Server::Vector finishPosition = move.getPosition();
    Server::Vector expectedPosition(5, 8);
    EXPECT_EQ(expectedPosition, finishPosition);
}

// Проверка невозможности прочитать/изменить состояние
TEST(MOVABLE, INTERFACE_TEST)
{
    Server::Vector startPosition(12, 5);
    Server::Vector velocity(-7, 3);
    Server::Move move(startPosition, velocity);

    EXPECT_EQ(startPosition, move.getPosition()); // читаем положение

    EXPECT_EQ(velocity, move.getVelocity()); // читаем скорость

    Server::Vector newPosition(10, 10);
    move.setPosition(newPosition);
    EXPECT_EQ(newPosition, move.getPosition()); // объект меняет положение
}



// Проверка правильности поворота
TEST(ROTABLE, ROTATE_TEST)
{
    int startDirection = 0;
    int angularVelocity = 10;
    Server::Rotate rotate(startDirection, angularVelocity);
    rotate.Execute();
    int finishDirection = rotate.getDirection();
    int expectedDirection = 10;
    EXPECT_EQ(expectedDirection, finishDirection);

}

// Проверка возможности прочитать/изменить состояние
TEST(ROTABLE, INTERFACE_TEST)
{
    int startDirection = 0;
    int angularVelocity = 10;
    Server::Rotate rotate(startDirection, angularVelocity);

    EXPECT_EQ(startDirection, rotate.getDirection()); // читаем направление

    EXPECT_EQ(angularVelocity, rotate.getAngularVelocity()); // читаем угловую скорость
    
    int newDirection = -15;
    rotate.setDirection(newDirection);
    EXPECT_EQ(newDirection, rotate.getDirection());
}
