set(GAME_SERVER_NAME "gameServer")

set(SOURCES
    src/Commands/Move.cpp
    src/Commands/Rotate.cpp
    src/EventLoop.cpp
    src/ExceptionHandler.cpp)

set(HEADERS
    hdr/Commands/ICommand.h
    hdr/Movable.h
    hdr/Rotable.h
    hdr/Commands/Move.h
    hdr/Commands/Rotate.h
    hdr/Commands/LogCommand.h
    hdr/EventLoop.h
    hdr/Exception.h
    hdr/ExceptionHandler.h
    hdr/Handlers/AddLogCmdInQueue.h)

add_library(${GAME_SERVER_NAME} SHARED ${HEADERS} ${SOURCES})
target_include_directories(${GAME_SERVER_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/hdr/
                                               PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/hdr/Commands/
                                               PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/hdr/Handlers/)
