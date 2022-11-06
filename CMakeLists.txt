cmake_minimum_required(VERSION 3.13)

project(maze)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

include_directories(include)

add_executable(maze ${SOURCES} ${HEADERS})
target_link_libraries(maze sfml-graphics)