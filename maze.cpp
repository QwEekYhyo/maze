#include "maze.hpp"
#include <iostream>

maze::maze(std::size_t size) {
    m_size = size;
    generate();
    m_pos = std::make_pair(0, 0);
}

void maze::generate() {
    //not implemented yet so maze is hard coded
    m_matrix = {
        {1,1,1,1,1,0,0,1,1,1},
        {0,1,1,1,1,1,0,1,0,1},
        {0,0,1,0,1,1,1,0,0,1},
        {1,0,1,1,1,0,1,1,0,1},
        {0,0,0,1,0,0,0,1,0,1},
        {1,0,1,1,1,0,0,1,1,0},
        {0,0,0,0,1,0,0,1,0,1},
        {0,1,1,1,1,1,1,1,0,0},
        {1,1,1,1,1,0,0,1,1,1},
        {0,0,1,0,0,1,1,0,0,1}
    };
    m_size = m_matrix[0].size();
}

std::pair<int, int> maze::get_pos() const {return m_pos;}

void maze::move(const std::pair<int, int>& pos) {
    auto temp = std::make_pair(m_pos.first + pos.first, m_pos.second + pos.second);
    if (m_matrix[temp.first][temp.second]) {
        m_pos = temp;
    }
    else {
        m_message = "Couldn't move";
    }
}
