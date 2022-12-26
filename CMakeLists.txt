cmake_minimum_required(VERSION 2.84)
project(battaglia-navale)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin/")

include_directories(include)

add_library(ship src/ship/ship.cpp src/ship/battleship.cpp)
add_library(board src/board/board.cpp src/board/attackboard.cpp src/board/defenseboard.cpp)
add_library(coordinate src/coordinate.cpp)

add_executable(battaglia_navale
        src/main.cpp
        )

add_executable(replay
        src/replay.cpp
        )

target_link_libraries(battaglia_navale ship board coordinate)
target_link_libraries(replay ship board coordinate)