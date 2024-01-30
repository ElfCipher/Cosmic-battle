set(GAME_SERVER_NAME "gameServer")

set(SOURCES
    src/Move.cpp
    src/Rotate.cpp
    src/EventLoop.cpp)

set(HEADERS
    hdr/ICommand.h
    hdr/Movable.h
    hdr/Rotable.h
    hdr/Move.h
    hdr/Rotate.h
    hdr/EventLoop.h
    hdr/Exception.h)

add_library(${GAME_SERVER_NAME} SHARED ${HEADERS} ${SOURCES})
target_include_directories(${GAME_SERVER_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/hdr/)
