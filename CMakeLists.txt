cmake_minimum_required(VERSION 2.84)
project(battaglia-navale)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin/")

include_directories(include)

add_library(${PROJECT_NAME} src/ship.cpp)

add_executable(battaglia_navale
        src/main.cpp
        )
add_executable(replay
        src/replay.cpp
        )

target_link_libraries(battaglia_navale ${PROJECT_NAME})
target_link_libraries(replay ${PROJECT_NAME})