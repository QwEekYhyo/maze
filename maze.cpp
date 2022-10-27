#include "maze.hpp"

maze::maze(std::size_t size) {
    m_size = size;
    generate();
    m_pos = {0, 0};
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

const coordinates& maze::get_pos() const {
    return m_pos;
}

void maze::move(const coordinates& pos) {
    coordinates temp = {m_pos.x + pos.x, m_pos.y + pos.y};
    if (m_matrix[temp.y][temp.x]) {
        m_pos = temp;
    }
    else {
        m_message = "Couldn't move";
    }
}

int& maze::at(coordinates pos) {
    return m_matrix.at(pos.y).at(pos.x);
}

const int& maze::at(coordinates pos) const {
    return m_matrix.at(pos.y).at(pos.x);
}

int& maze::operator[](coordinates pos) {
    return m_matrix[pos.y][pos.x];
}

std::ostream& operator<<(std::ostream& os, const maze& m) {
    for (int i = 0; i < m.m_size; i++) {
        for (int j = 0; j < m.m_size; j++) {
            os << m.m_matrix[i][j];
            os << ' ';
        }
        os << '\n';
    }
    os << m.m_message;
    return os;
}
