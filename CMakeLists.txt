cmake_minimum_required(VERSION 3.10)
project(maze)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)

include_directories(include)

add_executable(maze ${SOURCES} ${HEADERS})
