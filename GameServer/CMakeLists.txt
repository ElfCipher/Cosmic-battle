set(GAME_SERVER_NAME "gameServer")

set(SOURCES
    src/Commands/Move.cpp
    src/Commands/Rotate.cpp
    src/EventLoop.cpp
    src/ExceptionHandler.cpp
    src/Logger.cpp)

set(HEADERS
    hdr/Movable.h
    hdr/Rotable.h
    hdr/Commands/ICommand.h
    hdr/Commands/Move.h
    hdr/Commands/Rotate.h
    hdr/Commands/LogCommand.h
    hdr/Commands/RepeatCommand.h
    hdr/Commands/DoubleRepeat.h
    hdr/EventLoop.h
    hdr/Exception.h
    hdr/ExceptionHandler.h
    hdr/Handlers/CommonHandlers.h
    hdr/Logger.h)

add_library(${GAME_SERVER_NAME} SHARED ${HEADERS} ${SOURCES})
target_include_directories(${GAME_SERVER_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/hdr/
                                               PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/hdr/Commands/
                                               PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/hdr/Handlers/)
