#include <maze.hpp>
#include <random>
#include <deque>

int rand_int(int a, int b) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(a,b);

    return dist6(rng);
}

std::size_t coordinates::HashFunction::operator()(const coordinates& c) const noexcept {
    size_t xHash = std::hash<int>()(c.x);
    size_t yHash = std::hash<int>()(c.y) << 1;
    return xHash ^ yHash;
}

maze::maze(std::size_t size) {
    m_size = (2 * size) + 1;
    generate();
}

void maze::generate() {
    std::deque<coordinates> stack;
    coordinates current;
    coordinates next;
    coordinates wall;

    m_matrix = std::vector<std::vector<int>> (m_size, std::vector<int> (m_size, 0));

    int random = 2 * rand_int(0, m_size/2);
    m_pos = {random, 0};

    m_visited_cells.insert(m_pos);
    stack.push_back(m_pos);
    while (! stack.empty()) {
        current = stack.back();
        stack.pop_back();
        if (!at(current)) {
            at(current) = 1;
        }
        if (has_neighbor(current)) {
            stack.push_back(current);
            next = random_neighbor(current);
            wall = next + current;
            wall = {wall.x / 2, wall.y / 2};
            at(wall) = 1;
            m_visited_cells.insert(next);
            stack.push_back(next);
        }
    }
}

bool maze::contains(const coordinates& c) {
    return (c.x < m_size && c.x >= 0 && c.y < m_size && c.y >= 0);
}

bool maze::has_neighbor(const coordinates& pos) {
    std::vector<coordinates> possible_moves = {
        {2, 0},
        {-2, 0},
        {0, 2},
        {0, -2}
    };
    coordinates temp;

    for (coordinates& c : possible_moves) {
        temp = c + pos;
        if (contains(temp) && ! m_visited_cells.contains(temp)) {
            return true;
        }
    }
    return false;
}

const coordinates maze::random_neighbor(const coordinates& pos) {
    int random;
    std::vector<coordinates> valid_neighbors;
    std::vector<coordinates> possible_moves = {
        {2, 0},
        {-2, 0},
        {0, 2},
        {0, -2}
    };
    for (coordinates c : possible_moves) {
        c = c + pos;
        if (contains(c) && ! m_visited_cells.contains(c)) {
            valid_neighbors.push_back(c);
        }
    }

    random = rand_int(0, valid_neighbors.size() - 1);
    return valid_neighbors.at(random);
}

const coordinates& maze::get_pos() const {
    return m_pos;
}

const std::size_t& maze::size() const {
    return m_size;
}

void maze::move(const coordinates& pos) {
    coordinates temp = pos + m_pos;
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

coordinates operator+(const coordinates& a, const coordinates& b) {
    return {a.x + b.x, a.y + b.y};
}

void maze::draw_on_window(sf::RenderWindow& window) {
    float cell_size = window.getSize().y/m_size;
    std::vector<sf::RectangleShape> cells;
    std::size_t cell_count = 0;
    float x;
    float y;

    for (int i = 0; i < m_size; i++) {
        for (int j = 0; j < m_size; j++) {
            coordinates c = {j, i};
            if (at(c)) {
                x = j * cell_size;
                y = i * cell_size;
                cells.push_back(sf::RectangleShape(sf::Vector2f(cell_size, cell_size)));
                if (get_pos() == c) {
                    cells.at(cell_count).setFillColor(sf::Color::Green);
                } else {
                    cells.at(cell_count).setFillColor(sf::Color::Blue);
                }
                cells.at(cell_count).setPosition(sf::Vector2f(x, y));
                window.draw(cells.at(cell_count));
            }
        }
    }
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
