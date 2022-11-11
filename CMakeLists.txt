cmake_minimum_required(VERSION 3.10)
project(maze)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES1 src/maze.cpp src/graphical_main.cpp)
file(GLOB_RECURSE SOURCES2 src/maze.cpp src/main.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

include_directories(include)

add_executable(graphical_maze ${SOURCES1} ${HEADERS})
target_link_libraries(graphical_maze sfml-graphics)
add_executable(maze ${SOURCES2} ${HEADERS})
target_link_libraries(maze sfml-graphics)
