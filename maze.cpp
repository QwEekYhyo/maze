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
    if (at({temp.x, temp.y})) {
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
    return at({pos.x, pos.y});
}

bool operator==(const coordinates& a, const coordinates& b) {
    return a.x == b.x && a.y == b.y;
}

std::ostream& operator<<(std::ostream& os, const maze& m) {
    for (std::size_t i = 0; i < m.m_size; i++) {
        for (std::size_t j = 0; j < m.m_size; j++) {
            coordinates c = {j, i};
            if (m.get_pos() == c) {
                os << '*';
            } else {
                os << m.at(c);
            }
            os << ' ';
        }
        os << '\n';
    }
    os << m.m_message;
    return os;
}
