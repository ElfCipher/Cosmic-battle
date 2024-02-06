enable_testing()
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

set(SOURCES
    main.cpp)

set(HEADERS
    testClasses.h
    commandsTest.h
    eventLoopTest.h
    handlersTest.h)

add_executable(${PROJECT_NAME}_test ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME}_test 
    gameServer 
    gtest
    gmock
    gtest_main)

gtest_discover_tests(${PROJECT_NAME}_test)