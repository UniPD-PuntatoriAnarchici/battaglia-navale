cmake_minimum_required(VERSION 2.84)
project(battaglia_navale)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin/")

include_directories(include)

#add_library(${PROJECT_NAME} src/isbn.cpp src/date.cpp src/book.cpp)

add_executable(main
        src/main.cpp
        )

#target_link_libraries(main ${PROJECT_NAME})