#include "maze.hpp"
#include <iostream>

maze::maze(size_t size) {
    m_size = size;
    generate();
}

maze::generate() {
    std::cout << m_size << std::endl;
}
