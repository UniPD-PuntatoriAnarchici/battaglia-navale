cmake_minimum_required(VERSION 2.84)
project(battaglia-navale)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin/")
#set(CMAKE_CXX_FLAGS "-O2")

include_directories(include)

add_library(ship src/ship/ship.cpp src/ship/battleship.cpp src/ship/repairship.cpp src/ship/submarine.cpp)
add_library(board src/board/board.cpp src/board/attackboard.cpp src/board/defenseboard.cpp)
add_library(player src/player/player.cpp src/player/cpuplayer.cpp src/player/humanplayer.cpp)
add_library(coordinate src/coordinate/coordinate.cpp)

add_executable(battaglia_navale
        src/battaglia_navale.cpp
        )

add_executable(replay
        src/replay.cpp
        )

target_link_libraries(ship board coordinate)
target_link_libraries(board ship player coordinate)
target_link_libraries(player board ship coordinate)

target_link_libraries(battaglia_navale ship board player coordinate)
target_link_libraries(replay ship board player coordinate)
