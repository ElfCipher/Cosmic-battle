#include <gtest/gtest.h>
#include "commandsTest.h"
#include "eventLoopTest.h"
#include "handlersTest.h"
#include "iocTest.h"
#include "adaptersTest.h"
#include "endpointTest.h"
#include "corTest.h"

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}