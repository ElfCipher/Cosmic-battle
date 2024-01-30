cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)

project(CosmicBattle)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_subdirectory(GameServer)
add_subdirectory(Tests)
