#pragma once

#include <gtest/gtest.h>
#include "InitIoC.h"
#include "AdapterIMovable.h"
#include "AdapterIRotable.h"
#include "AdapterIFuelable.h"

TEST(ADAPTERS, EXISTING)
{
    Server::InitIoC init;
    init.Execute();

    auto movable = new Server::AdapterIMovable();
    auto rotable = new Server::AdapterIRotable();
    auto fuelable = new Server::AdapterIFuelable();
}
