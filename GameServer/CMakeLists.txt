set(GAME_SERVER_NAME "gameServer")

set(SOURCES
    src/Commands/Move.cpp
    src/Commands/Rotate.cpp
    src/Commands/CheckFuelCommand.cpp
    src/Commands/BurnFuelCommand.cpp
    src/Commands/MacroCommand.cpp
    src/Commands/ChangeVelocityCommand.cpp
    src/Commands/MoveWithBurning.cpp
    src/Commands/RotateWithVelocity.cpp
    src/Commands/InitIoC.cpp
    src/EventLoop.cpp
    src/Exceptions/ExceptionHandler.cpp
    src/Logger.cpp
    src/IoC.cpp
)

set(HEADERS
    hdr/Objects/IMovable.h
    hdr/Objects/IRotable.h
    hdr/Objects/IFuelable.h
    hdr/Objects/UObject.h
    hdr/Commands/ICommand.h
    hdr/Commands/Move.h
    hdr/Commands/Rotate.h
    hdr/Commands/LogCommand.h
    hdr/Commands/RepeatCommand.h
    hdr/Commands/DoubleRepeat.h
    hdr/Commands/CheckFuelCommand.h
    hdr/Commands/BurnFuelCommand.h
    hdr/Commands/MacroCommand.h
    hdr/Commands/ChangeVelocityCommand.h
    hdr/Commands/MoveWithBurning.h
    hdr/Commands/RotateWithVelocity.h
    hdr/Commands/Register.h
    hdr/Commands/InitIoC.h
    hdr/Commands/SetCurrentScope.h
    hdr/Commands/ClearCurrentScope.h
    hdr/Commands/StartLoop.h
    hdr/Commands/SoftStopLoop.h
    hdr/Commands/HardStopLoop.h
    hdr/EventLoop.h
    hdr/Exceptions/Exception.h
    hdr/Exceptions/ExceptionHandler.h
    hdr/Exceptions/ArgumentException.h
    hdr/Handlers/CommonHandlers.h
    hdr/Logger.h
    hdr/IoC.h
    hdr/ConcurrentQueue.h
    hdr/ManualResetEvent.h
)

add_subdirectory(auto_adapters)
add_library(${GAME_SERVER_NAME} SHARED ${HEADERS} ${SOURCES})
target_include_directories(${GAME_SERVER_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/hdr/
                                               PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/hdr/Commands/
                                               PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/hdr/Handlers/
                                               PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/hdr/Objects/
                                               PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/hdr/Exceptions/
                                               PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/auto_adapters
)

target_link_libraries(${GAME_SERVER_NAME} adapters)