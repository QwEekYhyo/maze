#include "maze.hpp"
#include <cstdlib>
#include <ctime>
#include <deque>

maze::maze(std::size_t size) {
    m_size = size;
    generate();
}

void maze::generate() {
    std::srand(time(NULL));
    std::deque<coordinates> stack;

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

    m_matrix = std::vector<std::vector<int>> (m_size, std::vector<int> (m_size, 1));
    for (int i = 0; i < m_size; i++) {
        for (int j = 0; j < m_size; j++) {
            if ((i+j) %2) {
                at({i, j}) = 0;
            }
        }
    }
    int random = 2 * (std::rand() % (m_size/2));
    m_pos = {random, 0};
    coordinates current = m_pos;
    current.visited = true;
}

bool maze::contains(const coordinates& c) {
    return (c.x < m_size && c.x >= 0 && c.y < m_size && c.y >= 0);
}

bool maze::has_neighbor(const coordinates& c) {
    std::vector<coordinates> possible_moves = {
        {2, 0},
        {-2, 0},
        {0, 2},
        {0, -2}
    };
    for (coordinates& c : possible_moves) {
        if (contains(c) && ! c.visited) {
            return true;
        }
    }
    return false;
}

const coordinates& maze::random_neighbor(const coordinates& pos) {
    std::srand(time(NULL));
    std::vector<coordinates> possible_moves = {
        {2, 0},
        {-2, 0},
        {0, 2},
        {0, -2}
    };
    while (true) {
    }
}

const coordinates& maze::get_pos() const {
    return m_pos;
}

void maze::move(const coordinates& pos) {
    coordinates temp = {m_pos.x + pos.x, m_pos.y + pos.y};
    if (contains(temp) && at(temp)) {
        m_pos = temp;
    }
    else {
        m_message = "Couldn't move\n";
    }
    update();
}

int& maze::at(coordinates pos) {
    return m_matrix.at(pos.y).at(pos.x);
}

const int& maze::at(coordinates pos) const {
    return m_matrix.at(pos.y).at(pos.x);
}

int& maze::operator[](coordinates pos) {
    return at(pos);
}

void maze::update() {
    std::cout << (*this) << std::endl;
    m_message = '\n';
}

bool operator==(const coordinates& a, const coordinates& b) {
    return a.x == b.x && a.y == b.y;
}

std::ostream& operator<<(std::ostream& os, const maze& m) {
    for (int i = 0; i < m.m_size; i++) {
        for (int j = 0; j < m.m_size; j++) {
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
